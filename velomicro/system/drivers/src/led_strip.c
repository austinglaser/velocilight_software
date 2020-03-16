/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   LedStrip Source
///
/// @addtogroup LED_STRIP
/// @{
///
/// @defgroup LED_STRIP_PRIVATE LedStrip Private Members
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// This module
#include "led_strip.h"

// Third-party headers
#include "app_error.h"

// Supporting modules
#include "util.h"

// Standard headers
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //

/// Value for start/stop frames.
static const led_strip_frame_t _start_stop_frame = { .packed = 0 };

/// Frame to write for black frames.
static const led_strip_frame_t _black_frame = { .bytes = {
    .global = 0xFF,
    .red = 0,
    .green = 0,
    .blue = 0,
}};

/// Number of bytes to write at a time when showing a frame.
#define _LED_STRIP_CHUNK_SIZE       128

// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //

/// Generate an @p frame for the provided @p color.
///
/// @param[in] ls       Strip to generate frame for. Provides values for global
///                     brightness and color correction.
/// @param[in] color    Color to generate
/// @param[out] frame   Corresponding LED frame. Incorporates global
///                     brightness, color correction, and gamma correction.
static err_t _led_strip_frame(
    led_strip_t const * ls,
    color_t color,
    led_strip_frame_t * frame
);

/// Compute a global-byte value based on a level.
///
/// @param[in] level    Brightness to use. Must be in the range [0.0, 1.0]
///
/// @return     An appropriate value for the global field in a frame (including
///             start bits)
uint8_t _led_strip_global(float level);

// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

err_t led_strip_init(
    led_strip_t * ls,
    nrf_drv_spi_t const * spi,
    led_strip_config_t const * config
) {
    if (ls == NULL || spi == NULL || config == NULL) {
        return ERROR_PARAM;
    }

    if (LED_STRIP_FRAME_COUNT(config->led_count) != config->frame_buffer_len) {
        return ERROR_PARAM;
    }

    ls->led_count = config->led_count;
    ls->frame_buffer = config->frame_buffer;
    ls->frame_buffer_len = config->frame_buffer_len;
    ls->spi = spi;
    ls->r_correction = 1.0;
    ls->g_correction = 1.0;
    ls->b_correction = 1.0;
    ls->start_global = _led_strip_global(1.0);

    ls->spi_config = (nrf_drv_spi_config_t) NRF_DRV_SPI_DEFAULT_CONFIG;
    ls->spi_config.frequency = NRF_DRV_SPI_FREQ_1M;
    ls->spi_config.mode = NRF_DRV_SPI_MODE_3;
    ls->spi_config.bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST;
    ls->spi_config.sck_pin = config->sck_pin;
    ls->spi_config.mosi_pin = config->mosi_pin;

    ret_code_t err_code;
    err_code = nrf_drv_spi_init(ls->spi, &ls->spi_config, NULL, NULL);
    if (err_code != NRF_SUCCESS) {
        return ERROR_COMM;
    }

    size_t strip_data_start = LED_STRIP_START_COUNT;
    size_t strip_data_end = LED_STRIP_START_COUNT + ls->led_count;
    for (size_t i = 0; i < config->frame_buffer_len; i++) {
        if (strip_data_start <= i && i < strip_data_end) {
            ls->frame_buffer[i] = _black_frame;
        } else {
            ls->frame_buffer[i] = _start_stop_frame;
        }
    }

    return led_strip_show(ls);
}

err_t led_strip_set_brightness(led_strip_t * ls, float global) {
    if (ls == NULL || global < 0.0 || global > 1.0) {
        return ERROR_PARAM;
    }

    ls->start_global = _led_strip_global(global);

    for (size_t i = 0; i < ls->led_count; i++) {
        size_t index = LED_STRIP_START_COUNT + i;
        ls->frame_buffer[index].bytes.global = ls->start_global;
    }

    return ERROR_NONE;
}

err_t led_strip_set_correction(led_strip_t * ls, float r, float g, float b) {
    if (ls == NULL) {
        return ERROR_PARAM;
    }

    if (!(0.0 <= r && r <= 1.0)) {
        return ERROR_PARAM;
    }

    if (!(0.0 <= g && g <= 1.0)) {
        return ERROR_PARAM;
    }

    if (!(0.0 <= b && b <= 1.0)) {
        return ERROR_PARAM;
    }

    ls->r_correction = r;
    ls->g_correction = g;
    ls->b_correction = b;

    return ERROR_NONE;
}

size_t led_strip_length(led_strip_t const * ls) {
    if (ls == NULL) {
        return 0;
    }

    return ls->led_count;
}

err_t led_strip_write(led_strip_t * ls, size_t led, color_t color) {
    if (led >= ls->led_count) {
        return ERROR_PARAM;
    }

    led_strip_frame_t * frame = &ls->frame_buffer[LED_STRIP_START_COUNT + led];

    return _led_strip_frame(ls, color, frame);
}

err_t led_strip_write_all(led_strip_t * ls, color_t color) {
    led_strip_frame_t frame;
    err_t err = _led_strip_frame(ls, color, &frame);
    if (err != ERROR_NONE) {
        return err;
    }

    for (size_t i = 0; i < ls->led_count; i++) {
        ls->frame_buffer[LED_STRIP_START_COUNT + i] = frame;
    }

    return ERROR_NONE;
}

err_t led_strip_show(led_strip_t const * ls) {
    uint8_t const * data = (uint8_t const *) ls->frame_buffer;
    size_t to_write = ls->frame_buffer_len * sizeof(*ls->frame_buffer);

    for (size_t offset = 0; offset < to_write; offset += _LED_STRIP_CHUNK_SIZE) {
        size_t bytes_left = to_write - offset;
        size_t chunk_bytes = bytes_left > _LED_STRIP_CHUNK_SIZE
            ? _LED_STRIP_CHUNK_SIZE
            : bytes_left;

        ret_code_t err_code = nrf_drv_spi_transfer(
            ls->spi,
            data + offset,
            chunk_bytes,
            NULL,
            0
        );

        if (err_code != NRF_SUCCESS) {
            return ERROR_COMM;
        }
    }

    return ERROR_NONE;
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

static err_t _led_strip_frame(
    led_strip_t const * ls,
    color_t color,
    led_strip_frame_t * frame
) {
    color_err_t err = color_convert(&color, COLOR_TYPE_RGB);
    if (err != COLOR_SUCCESS) {
        return ERROR_PARAM;
    }

    float r_raw = color.r * color.r * 255.0;
    float g_raw = color.g * color.g * 255.0;
    float b_raw = color.b * color.b * 255.0;

    float r = r_raw * ls->r_correction;
    float g = g_raw * ls->g_correction;
    float b = b_raw * ls->b_correction;

    // It's possible for the uneven color correction to disable a channel (by
    // kicking it below the rounding threshold) when the others are active.
    // This is suboptimal primarily in the situation where the pixel is
    // intended to be white (even brightness on all channels) but becomes
    // colored due to one or more channels being disabled.
    //
    // Because this is only a problem at very low brightnesses, we can simply
    // detect the situation and disable *all* channels.
    bool scaled_off = (r_raw > 0.5 && r < 0.5)
        || (g_raw > 0.5 && g < 0.5)
        || (b_raw > 0.5 && b < 0.5);
    if (scaled_off) {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }

    frame->bytes.global = ls->start_global;
    frame->bytes.red = (uint8_t) roundf(r);
    frame->bytes.green = (uint8_t) roundf(g);
    frame->bytes.blue = (uint8_t) roundf(b);

    return ERROR_NONE;
}

uint8_t _led_strip_global(float level)
{
    static const uint8_t start_bits = 0xE0;

    uint8_t global = (uint8_t) roundf(0x1F * level);

    return start_bits | global;
}

/// @} defgroup LED_STRIP_PRIVATE
/// @} addtogroup LED_STRIP
