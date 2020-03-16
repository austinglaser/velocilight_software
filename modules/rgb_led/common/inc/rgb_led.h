/**@file    rgb_led.h
 * @author  Krithik Chandrashekar <krithik@boulderes.com>
 * @brief   RGB_LED Interface
 */

#ifndef RGB_LED_H
#define RGB_LED_H

/**@defgroup RGB_LED
 * @{
 *
 * Generic RGB LED interface
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "rgb_led_implementation.h"

#include <stdbool.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/** @defgroup RGB_LED_COLORS Led Colors
 * @{
 */

/** Red color */
#define RGB_LED_COLOR_RED       0x01

/** Green color */
#define RGB_LED_COLOR_GREEN     0x02

/** Blue color */
#define RGB_LED_COLOR_BLUE      0x04

/** Yellow color */
#define RGB_LED_COLOR_YELLOW    (RGB_LED_COLOR_RED | \
                                 RGB_LED_COLOR_GREEN)

/** Violet color */
#define RGB_LED_COLOR_VIOLET    (RGB_LED_COLOR_RED | \
                                 RGB_LED_COLOR_BLUE)

/** Violet color */
#define RGB_LED_COLOR_CYAN      (RGB_LED_COLOR_GREEN | \
                                 RGB_LED_COLOR_BLUE)

/** Violet color */
#define RGB_LED_COLOR_WHITE     (RGB_LED_COLOR_RED   | \
                                 RGB_LED_COLOR_GREEN | \
                                 RGB_LED_COLOR_BLUE)

/** Led off */
#define RGB_LED_COLOR_BLACK     0x00

/** @} defgroup RGB_LED_COLORS */

/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** An RGB_LED instance */
typedef struct {
    rgb_led_config_t const * config;    /**< Instance configuration */
} rgb_led_t;

/** All valid RGB_LED colors */
typedef uint8_t rgb_led_color_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Initialize an RGB_LED interface
 *
 * @param[out] rgb_led:     The rgb_led descriptor to initialize
 * @param[in] config:       The rgb_led configuration
 */
void rgb_led_init(rgb_led_t * rgb_led, rgb_led_config_t const * config);

/** Set the RGB_LED to the specified color
 *
 * @param[in,out] rgb_led: The RGB_LED instance
 * @param[in] color:       The specified color
 */
void rgb_led_set(rgb_led_t * rgb_led, rgb_led_color_t color);

/** @} defgroup RGB_LED */

#endif /* ifndef RGB_LED_H */
