/**
 * @file    main.c
 * @author  Austin Glaser <austin.glaser@gmail.com>
 * @brief   Application Entry Point
 *
 * @defgroup MAIN Main
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

// Standard
#include <stdint.h>
#include <stdbool.h>

// Modules
#include "audio.h"
#include "array.h"
#include "color.h"
#include "ensure.h"
#include "error.h"
#include "fft.h"
#include "fpga.h"
#include "framebuffer.h"
#include "led_colors.h"
#include "rgb_led.h"
#include "strip_map_octave_len4096.h"
#include "util.h"

// Chibios
#include "ch.h"
#include "hal.h"

// App
#include "soundpuddle.h"

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

static const rgb_led_config_t dial_led_config = {
    .r_line = LINE_LED_R,
    .g_line = LINE_LED_G,
    .b_line = LINE_LED_B,
};

/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

static THD_FUNCTION(audio_thread, arg);

static THD_FUNCTION(heartbeat_thread, arg);

/** Handle a function return code
 *
 * If @p err is not ERROR_NONE, records the error message, makes the LED red,
 * and halts the system
 */
static void handle_error(err_t err, char const * msg);

/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

/** LED in the encoder dial */
static rgb_led_t dial_led;

/** Error code causing system halt */
static err_t fail_error = ERROR_NONE;

/** Message describing reason for system halt */
static char const * fail_msg = NULL;

static THD_WORKING_AREA(audio_wa, 1024);

static THD_WORKING_AREA(heartbeat_wa, 128);

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/**
 * @brief   Application entry point
 */
int main(void)
{
    err_t err;

    // Chibios init
    halInit();
    chSysInit();

    // Driver init
    rgb_led_init(&dial_led, &dial_led_config);
    audio_init();

    err = fpga_init();
    handle_error(err, "FPGA configuration failed");

    chThdSleepMilliseconds(1);

    // Application init
    chThdCreateStatic(audio_wa, sizeof(audio_wa),
                      NORMALPRIO - 1,
                      audio_thread, NULL);

    chThdCreateStatic(heartbeat_wa, sizeof(heartbeat_wa),
                      HIGHPRIO,
                      heartbeat_thread, &dial_led);

    fft_init();
    led_colors_init();
    music_map_initialize();
    framebuffer_init();
    array_init();

    palClearLine(LINE_OUT0_ENABLE);
    palClearLine(LINE_OUT1_ENABLE);
    palClearLine(LINE_OUT2_ENABLE);
    palClearLine(LINE_OUT3_ENABLE);

    chThdSleepMilliseconds(100);

    time_measurement_t tm_frame;
    chTMObjectInit(&tm_frame);

    array_clear();

    // Main loop

    while (true) {
        chTMStartMeasurementX(&tm_frame);

        while (framebuffer_power() >= 712000) {
            framebuffer_backoff();
        }

        array_write();

        chTMStopMeasurementX(&tm_frame);
    }
}

/* --- HANDLERS ------------------------------------------------------------- */

void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
{
    /* These are volatile to try and prevent the compiler/linker optimising
     * them away as the variables never actually get used.  If the debugger
     * won't show the values of the variables, make them global my moving their
     * declaration outside of this function. */
    volatile uint32_t r0;
    volatile uint32_t r1;
    volatile uint32_t r2;
    volatile uint32_t r3;
    volatile uint32_t r12;
    volatile uint32_t lr; /* Link register. */
    volatile uint32_t pc; /* Program counter. */
    volatile uint32_t psr;/* Program status register. */

    r0 = pulFaultStackAddress[ 0 ];
    r1 = pulFaultStackAddress[ 1 ];
    r2 = pulFaultStackAddress[ 2 ];
    r3 = pulFaultStackAddress[ 3 ];

    r12 = pulFaultStackAddress[ 4 ];
    lr = pulFaultStackAddress[ 5 ];
    pc = pulFaultStackAddress[ 6 ];
    psr = pulFaultStackAddress[ 7 ];

    UNUSED_VARIABLE(r0);
    UNUSED_VARIABLE(r1);
    UNUSED_VARIABLE(r2);
    UNUSED_VARIABLE(r3);
    UNUSED_VARIABLE(r12);
    UNUSED_VARIABLE(lr);
    UNUSED_VARIABLE(pc);
    UNUSED_VARIABLE(psr);

    /* When the following line is hit, the variables contain the register values. */
    for( ;; );
}

void __attribute__((naked)) HardFault_Handler(void)
{
    __asm volatile
        (
         " tst lr, #4                                                \n"
         " ite eq                                                    \n"
         " mrseq r0, msp                                             \n"
         " mrsne r0, psp                                             \n"
         " ldr r1, [r0, #24]                                         \n"
         " ldr r2, handler2_address_const                            \n"
         " bx r2                                                     \n"
         " handler2_address_const: .word prvGetRegistersFromStack    \n"
        );
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static THD_FUNCTION(audio_thread, arg)
{
    UNUSED_PARAMETER(arg);

    static uint16_t audio_data[FFT_SAMPLE_SIZE];
    static float32_t fft_mag[FFT_SAMPLE_SIZE/2];
    static float32_t strip_mag[FB_STRIP_NUM];

    static sp_rgb_u next_row[FB_STRIP_NUM] = {
        [0 ... FB_STRIP_NUM - 1] = {
            .unpacked = {
                .control = RGB_CONTROL_BYTE,
            },
        },
    };

    while (true) {
        audio_get(audio_data, ARRAY_ELEMENTS(audio_data));

        fft_execute_16(audio_data, fft_mag);

        static const uint32_t max_bins = ARRAY_ELEMENTS(strip_map_octave_len4096[0]);
        for (uint32_t strip = 0; strip < FB_STRIP_NUM; strip++) {
            strip_mag[strip] = 0.0;
            uint32_t nbins = 0;
            for (uint32_t i = 0; i < max_bins; i++) {
                uint16_t bin = strip_map_octave_len4096[strip][i];
                if (bin == 0) {
                    break;
                }
                strip_mag[strip] += fft_mag[bin];
                nbins++;
            }
            strip_mag[strip] /= 50000.0*nbins; // this is the "soundpuddle classic" mapping 2017-08-05
//             strip_mag[strip] /= 50000.0*max_bins; // this was used for Mark's video 2017-08-05

            if (strip_mag[strip] > 1.0) {
                strip_mag[strip] = 1.0;
            }
        }

        for (uint32_t i = 0; i < FB_STRIP_NUM; i++) {
            color_t color;
            color.type = COLOR_TYPE_HSV;
            //color.h = 2.0/3.0 + 10.73 - strip_mag[i] * 1.0;
            // color.h = strip_mag[i] * 1.125; // this was the mapping for Mark's video 2017-08-05
            color.h = 2.0/3.0 + 10.2 - strip_mag[i] * 6.0; // this is a nice "soundpuddle classic" type mapping. The 10.2 is goofy should be refined
            color.s = 1.0;
            if (strip_mag[i] < 0.025) {
                color.l = 0.0;
            } else {
                color.l = strip_mag[i]*0.7;
            }

            while (color.h > 1.0) {
                color.h -= 1.0;
            }

            color_convert(&color, COLOR_TYPE_RGB);
            next_row[i].unpacked.r = (uint8_t) (color.r * 255.0);
            next_row[i].unpacked.g = (uint8_t) (color.g * 255.0);
            next_row[i].unpacked.b = (uint8_t) (color.b * 255.0);
        }

        framebuffer_modes[FB_MODE_OUT].insert_values((uint32_t *) next_row);
    }
}

static THD_FUNCTION(heartbeat_thread, _heartbeat_led)
{
    rgb_led_t * heartbeat_led = _heartbeat_led;

    while (true) {
        if (fail_error == ERROR_NONE) {
            rgb_led_set(heartbeat_led, RGB_LED_COLOR_GREEN);
        } else {
            rgb_led_set(heartbeat_led, RGB_LED_COLOR_RED);
        }
        chThdSleepMilliseconds(500);

        rgb_led_set(heartbeat_led, RGB_LED_COLOR_BLACK);
        chThdSleepMilliseconds(500);
    }
}

static void handle_error(err_t err, char const * msg)
{
    if (err != ERROR_NONE) {
        /* Save these so they can be read with a debugger */
        fail_error = err;
        fail_msg = msg;

        while (true);
    }
}

/** @} defgroup MAIN */
