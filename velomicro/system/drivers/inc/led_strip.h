/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   LedStrip Interface

#ifndef LED_STRIP_H
#define LED_STRIP_H

/// @defgroup LED_STRIP LedStrip
/// @{
///
/// @brief

// --- PUBLIC DEPENDENCIES ------------------------------------------------- //

// Third-party headers
#include "app_util.h"
#include "nrf_drv_spi.h"

// Supporting modules
#include "color.h"
#include "error.h"
#include "util.h"

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PUBLIC CONSTANTS ---------------------------------------------------- //
// --- PUBLIC DATATYPES ---------------------------------------------------- //

/// A single LED frame
typedef union {
    /// All 32 packed bits
    uint32_t packed;

    /// Individual frame elements.
    struct {
        /// Global brightness, plus leading ones.
        uint8_t global;

        /// Blue channel brightness.
        uint8_t blue;

        /// Green channel brightness.
        uint8_t green;

        /// Red channel brightness.
        uint8_t red;
    } bytes;
} led_strip_frame_t;

/// Configuration for an LED strip.
typedef struct {
    /// Number of LEDs to be addressed.
    size_t led_count;

    /// Frame buffer area.
    led_strip_frame_t * frame_buffer;

    /// Elements in the @ref frame_buffer array.
    ///
    /// Should be calculated as `ARRAY_ELEMENTS(frame_buffer)` to avoid errors.
    size_t frame_buffer_len;

    /// Clock pin.
    uint8_t sck_pin;

    /// Data pin.
    uint8_t mosi_pin;
} led_strip_config_t;

/// Handle for a single strip of LEDs.
typedef struct {
    /// Number of LEDs to be addressed.
    size_t led_count;

    /// Elements in frame buffer.
    size_t frame_buffer_len;

    /// Frame buffer area.
    led_strip_frame_t * frame_buffer;

    /// SPI driver instance.
    nrf_drv_spi_t const * spi;

    /// Configuration for the SPI driver.
    nrf_drv_spi_config_t spi_config;

    /// Color correction for red channel.
    float r_correction;

    /// Color correction for green channel.
    float g_correction;

    /// Color correction for blue channel.
    float b_correction;

    /// First byte of LED frames.
    ///
    /// Contains three start bits and a global brightness value.
    uint8_t start_global;
} led_strip_t;

// --- PUBLIC MACROS ------------------------------------------------------- //

/// Number of start frames per strip.
///
/// Should almost always be 1.
#define LED_STRIP_START_COUNT 1

/// Number of total frames to allocate in a frame buffer of length @p leds.
#define LED_STRIP_FRAME_COUNT(leds) (                                        \
    LED_STRIP_START_COUNT + leds + CEIL_DIV(leds, 64)                        \
)

// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

/// Initialize an LED strip.
///
/// To some extent, @p frame_buffer_size and @p led_count provide redundant
/// information. However, it's worth taking both to allow the driver to catch
/// possible configuration errors.
///
/// After this function is initialized, the frame buffer will be cleared to all
/// black, and the external strip will be updated *once* to this value. Any
/// further updates have to occur manually.
///
/// This sets the strip's global brightness to 1.0 by default -- to change it,
/// use @ref led_strip_set_brightness.
///
/// @param[out] ls          Strip to initialize.
/// @param[in] led_count    Number of LEDs addressed by the strip.
/// @param[in] frame_buffer Data region to store strip data. The driver takes
///                         ownership of this buffer -- it shouldn't be used
///                         after this function.
/// @param[in] frame_buffer_len Elements available in the buffer. Should be
///                         calculated as `ARRAY_ELEMENTS(frame_buffer)` to
///                         avoid errors.
err_t led_strip_init(
    led_strip_t * ls,
    nrf_drv_spi_t const * spi,
    led_strip_config_t const * config
);

/// Set the overall brightness of a strip.
///
/// Implemented using the actual global brightness setting available in the LED
/// frame.
///
/// When this function is called, it will have two effects:
///
/// 1. Applying the supplied global brightness to all values currently stored
///     in the frame buffer.
/// 2. Causing the same global brightness to be applied to all *future* values.
///
/// @note   The APA102 displays this by overlaying a lower-frequency PWM signal
///         over the main per-channel dimming. This will cause a visual
///         flickering effect for high-speed (e.g. persistence-of-vision)
///         applications, which is often undesirable.
///
/// @note   Though @p global is supplied as a `float` to this function, the
///         actual global brightness only has 5 bits of resolution. @p global
///         is scaled and rounded to match this range.
///
/// @param[in,out] ls       Will have output values scaled by the brightness.
/// @param[in] global       The brightness value, in the range [0.0, 1.0]
err_t led_strip_set_brightness(led_strip_t * ls, float global);

/// Set the strip's color-correction value.
///
/// This is a set of scalars applied to every *new* color written to the strip.
///
/// @note   Values already in the strip's frame buffer are not affected by this
///         function! Only newly written values take it into account.
///
/// @param[in,out] ls       Will have color values corrected by the factors.
/// @param[in] r            Red correction factor. In the range [0.0, 1.0].
/// @param[in] g            Green correction factor. In the range [0.0, 1.0].
/// @param[in] b            Blue correction factor. In the range [0.0, 1.0].
err_t led_strip_set_correction(led_strip_t * ls, float r, float g, float b);

/// Determine the number of LEDs configured for a strip.
///
/// @return The number of LEDs in a strip, or 0 if @p ls is NULL or
///         unconfigured.
size_t led_strip_length(led_strip_t const * ls);

/// Write a single LED to a color
///
/// Only updates the in-memory frame buffer, not the physical LEDs. To write
/// memory to the LEDs, call @ref led_strip_update().
///
/// @param[in,out] ls       Strip to write.
/// @param[in] led          Zero-based index of LED to write. Must be <
///                         ls->led_count.
/// @param[in] color        Color to write. Will be converted to RGB.
err_t led_strip_write(led_strip_t * ls, size_t led, color_t color);

/// Write all LEDs to a single color
///
/// Only updates the in-memory frame buffer, not the physical LEDs. To write
/// memory to the LEDs, call @ref led_strip_update().
///
/// @param[in,out] ls        Strip to write.
/// @param[in] color         Color to write. Will be converted to RGB.
err_t led_strip_write_all(led_strip_t * ls, color_t color);

/// Send the frame buffer to the physical LEDs
///
/// @param[in] ls            Strip to update.
err_t led_strip_show(led_strip_t const * ls);

/// @} defgroup LED_STRIP

#endif // ifndef LED_STRIP_H
