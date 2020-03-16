/// @file    main.c
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   Application Entry Point
///
/// @defgroup MAIN Main
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// Supporting modules
#include "array.h"
#include "array_cart_snake.h"
#include "led_strip.h"
#include "mpu9250.h"
#include "perlin.h"

// Third-party modules
#include "nrf_delay.h"
#include "nrf_gpio.h"

// Standard
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //

/// Set up the VeloOpto daughterboard
static array_t * _veloopto_setup(void);

/// Set up the external led strip driver
static array_t * _external_strip_setup(void);

/// Set up the IMU
static mpu9250_t * _mpu9250_setup(void);

/// Initialize a perlin noise generator
static perlin_t const * _perlin_init(void);

// --- PRIVATE CONSTANTS --------------------------------------------------- //

/// Number of LEDs in the X direction of the veloopto backpack
///
/// X axis parallel to strip layout
#define VELOOPTO_LED_X       9

/// Number of LEDs in the Y direction of the veloopto backpack
///
/// Y axis perpendicular to strip layout
#define VELOOPTO_LED_Y       2

/// Number of LEDs on the veloopto backpack
#define VELOOPTO_LED_COUNT (VELOOPTO_LED_X * VELOOPTO_LED_Y)

/// Number of LEDs in the X direction of the veloopto backpack
///
/// X axis parallel to strip layout
#define EXTERNAL_LED_X       16

/// Number of LEDs in the Y direction of the veloopto backpack
///
/// Y axis perpendicular to strip layout
#define EXTERNAL_LED_Y       16

/// Number of LEDs in the external strip
#define EXTERNAL_LED_COUNT (EXTERNAL_LED_X * EXTERNAL_LED_Y)

// --- PRIVATE MACROS ------------------------------------------------------ //

/// Get the absolute value of a number.
#define ABS(value) ({                                                         \
    typeof(value) abs_value__ = (value);                                      \
    (abs_value__ < 0) ? -abs_value__ : abs_value__;                           \
})

// Nordic provides definitions of MIN and MAX that are subject to
// multiple-evaluation bugs (for instance, MIN(a++, b++) would have
// interestingly bad behavior), and are not type-safe.
//
// So, get rid of them and provide our own functionally identical but more
// robust versions. Note that these rely on GCC compiler extensions.
#undef MIN
#undef MAX

/// Get the minimum value of two numbers.
#define MIN(a, b) ({                                                          \
    static_assert(                                                            \
        __builtin_types_compatible_p(typeof(a), typeof(b)),                   \
        "type mismatch"                                                       \
    );                                                                        \
    typeof(a) min_a__ = (a);                                                  \
    typeof(b) min_b__ = (b);                                                  \
    min_a__ < min_b__ ? min_a__ : min_b__;                                    \
})

/// Get the maximum value of two numbers.
#define MAX(a, b) ({                                                          \
    static_assert(                                                            \
        __builtin_types_compatible_p(typeof(a), typeof(b)),                   \
        "type mismatch"                                                       \
    );                                                                        \
    typeof(a) max_a__ = (a);                                                  \
    typeof(b) max_b__ = (b);                                                  \
    max_a__ > max_b__ ? max_a__ : max_b__;                                    \
})

// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

/// Application Entry Point.
int main(void)
{
    float brightness = 0.1;
    const color_t black = COLOR_RGB_INIT(0.0, 0.0, 0.0);
    const color_t red = COLOR_RGB_INIT(brightness, 0.0, 0.0);
    const color_t green = COLOR_RGB_INIT(0.0, brightness, 0.0);

    // Initialization
    array_t * veloopto = _veloopto_setup();
    if (veloopto == NULL) {
        while (true);
    }

    array_t * external = _external_strip_setup();
    if (external == NULL) {
        array_write(veloopto, 0, 0, red);
        array_show(veloopto);
        while (true);
    } else {
        array_write(veloopto, 0, 0, green);
    }

    mpu9250_t * imu = _mpu9250_setup();
    if (imu == NULL) {
        array_write(veloopto, 0, 1, red);
        array_show(veloopto);
        while (true);
    }

    perlin_t const * perlin = _perlin_init();

    array_write_all(external, black);
    float time = 0.0;
    float hue = 0.0;

    // Main loop
    while (true) {
        for (size_t x = 0; x < EXTERNAL_LED_X; x++) {
            for (size_t y = 0; y < EXTERNAL_LED_Y; y++) {
                float noise = perlin_noise_octaves(
                    perlin,
                    x,
                    y,
                    time,
                    1.0 / (float) MIN(EXTERNAL_LED_X, EXTERNAL_LED_Y),
                    2,
                    0.5
                );

                color_t color = COLOR_HSV_INIT(
                    hue,
                    sqrtf(sqrtf(noise)),
                    sqrtf(noise)
                );

                array_write(external, x, y, color);
            }
        }
        time += 0.04;
        hue += 0.001;
        while (hue > 1.0) {
            hue -= 1.0;
        }

        mpu9250_sample_t sample;
        if (mpu9250_read(imu, &sample) != ERROR_NONE) {
            array_write_all(veloopto, black);
            array_write(veloopto, 0, 0, red);
        } else {
            mpu9250_convert(imu, &sample);

            color_t color = COLOR_RGB_INIT(0., 0., 0.);
            color.r = ABS(((float) sample.accel.x) / 2000.0);
            color.g = ABS(((float) sample.accel.y) / 2000.0);
            color.b = ABS(((float) sample.accel.z) / 2000.0);

            array_write_all(veloopto, color);
        }

        array_show(external);
        array_show(veloopto);
        nrf_delay_ms(20);
    }
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

static array_t * _veloopto_setup(void) {
    static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(2);

    static led_strip_frame_t frame_buffer[
        LED_STRIP_FRAME_COUNT(VELOOPTO_LED_COUNT)
    ];

    static const led_strip_config_t config = {
        .led_count = VELOOPTO_LED_COUNT,
        .frame_buffer = frame_buffer,
        .frame_buffer_len = ARRAY_ELEMENTS(frame_buffer),
        .sck_pin = 8,
        .mosi_pin = 7,
    };

    nrf_gpio_cfg_output(20);
    nrf_gpio_pin_set(20);

    static led_strip_t led_strip;
    if (led_strip_init(&led_strip, &spi, &config) != ERROR_NONE) {
        return NULL;
    }

    if (led_strip_set_brightness(&led_strip, 0.1) != ERROR_NONE) {
        return NULL;
    }

    if (led_strip_set_correction(&led_strip, 1.0, 0.8, 1.0) != ERROR_NONE) {
        return NULL;
    }

    static color_t buffer[VELOOPTO_LED_COUNT];

    static array_cart_snake_t array;
    err_t err = array_cart_snake_init(
        &array,
        &led_strip,
        VELOOPTO_LED_X,
        VELOOPTO_LED_Y,
        buffer
    );

    if (err != ERROR_NONE) {
        return NULL;
    } else {
        return (array_t *) &array;
    }
}

static array_t * _external_strip_setup(void) {
    static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(0);

    static led_strip_frame_t frame_buffer[
        LED_STRIP_FRAME_COUNT(EXTERNAL_LED_COUNT)
    ];

    static const led_strip_config_t config = {
        .led_count = EXTERNAL_LED_COUNT,
        .frame_buffer = frame_buffer,
        .frame_buffer_len = ARRAY_ELEMENTS(frame_buffer),
        .sck_pin = 10,
        .mosi_pin = 9,
    };

    static led_strip_t led_strip;
    if (led_strip_init(&led_strip, &spi, &config) != ERROR_NONE) {
        return NULL;
    }

    if (led_strip_set_brightness(&led_strip, 0.1) != ERROR_NONE) {
        return NULL;
    }

    if (led_strip_set_correction(&led_strip, 1.0, 0.8, 1.0) != ERROR_NONE) {
        return NULL;
    }

    static color_t buffer[EXTERNAL_LED_COUNT];

    static array_cart_snake_t array;
    err_t err = array_cart_snake_init(
        &array,
        &led_strip,
        EXTERNAL_LED_X,
        EXTERNAL_LED_Y,
        buffer
    );

    if (err != ERROR_NONE) {
        return NULL;
    } else {
        return (array_t *) &array;
    }
}

static mpu9250_t * _mpu9250_setup(void)
{
    static const nrf_drv_twi_t twi = NRF_DRV_TWI_INSTANCE(1);
    static const nrf_drv_twi_config_t twi_config = {
        .scl = 25,
        .sda = 26,
        .frequency = NRF_TWI_FREQ_250K,
        .interrupt_priority = TWI_DEFAULT_CONFIG_IRQ_PRIORITY,
        .clear_bus_init = true,
        .hold_bus_uninit = false,
    };

    static mpu9250_t imu;
    static const mpu9250_config_t config = {
        .accel_fs = MPU9250_ACCEL_FS_2,
        .accel_samplerate = MPU9250_ACCEL_SAMPLERATE_1k_460Hz,

        .gyro_fs = MPU9250_GYRO_FS_250,
        .gyro_samplerate = MPU9250_GYRO_SAMPLERATE_1k_184Hz,

        .port_config = {
            .twi = &twi,
            .ad0 = true,
        },
    };

    ret_code_t twi_err =  nrf_drv_twi_init(&twi, &twi_config, NULL, NULL);
    if (twi_err != NRF_SUCCESS) {
        return NULL;
    }

    nrf_drv_twi_enable(&twi);

    // After a power cycle, the MPU9250 needs some time to start up. The value
    // here excessive, but startup time is not an issue for most of our
    // applications.
    nrf_delay_ms(100);

    err_t err = mpu9250_init(&imu, &config);
    if (err != ERROR_NONE) {
        return NULL;
    }

    return &imu;
}

static perlin_t const * _perlin_init(void)
{
    return perlin_reference();
}

/// @} defgroup MAIN
