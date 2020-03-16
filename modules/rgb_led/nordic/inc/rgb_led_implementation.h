/**@file    rgb_led_implementation.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Nordic RGB_LED Interface
 */

#ifndef RGB_LED_IMPLEMENTATION_H
#define RGB_LED_IMPLEMENTATION_H

/**@defgroup RGB_LED_IMPLEMENTATION RgbLedImplementation
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** RGB LED Configuration */
typedef struct {
    uint32_t r_pin_number;  /**< Pin used for red channel */
    uint32_t g_pin_number;  /**< Pin used for green channel */
    uint32_t b_pin_number;  /**< Pin used for blue channel */
} rgb_led_config_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Initialize the pins specified in the config to be outputs
 *
 * @param[in] config:       LED configuration
 */
void rgb_led_implementation_pin_init(rgb_led_config_t const * config);

/** Update the actual pin output state based on the [rgb]_on fields
 *
 * @param[in] config:       LED configuration
 * @param[in] r_on:         Whether to turn on the red channel
 * @param[in] g_on:         Whether to turn on the green channel
 * @param[in] b_on:         Whether to turn on the blue channel
 */
void rgb_led_implementation_update(rgb_led_config_t const * config,
                                   bool r_on,
                                   bool g_on,
                                   bool b_on);

/** @} defgroup RGB_LED_IMPLEMENTATION */

#endif /* ifndef RGB_LED_IMPLEMENTATION_H */
