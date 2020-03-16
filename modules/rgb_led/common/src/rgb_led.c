/**@file    rgb_led.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   RgbLed Source
 *
 * @addtogroup RGB_LED
 * @{
 *
 * @defgroup RGB_LED_PRIVATE RgbLed Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "rgb_led.h"
#include "rgb_led_implementation.h"

#include "ensure.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void rgb_led_init(rgb_led_t * rgb_led, rgb_led_config_t const * config)
{
    ensure(rgb_led != NULL);

    rgb_led->config = config;

    rgb_led_implementation_pin_init(rgb_led->config);
    rgb_led_implementation_update(rgb_led->config, false, false, false);
}

void rgb_led_set(rgb_led_t * rgb_led, rgb_led_color_t color)
{
    ensure(rgb_led != NULL);

    bool r_on = color & RGB_LED_COLOR_RED;
    bool g_on = color & RGB_LED_COLOR_GREEN;
    bool b_on = color & RGB_LED_COLOR_BLUE;

    rgb_led_implementation_update(rgb_led->config, r_on, g_on, b_on);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} defgroup RGB_LED_PRIVATE */
/** @} addtogroup RGB_LED */
