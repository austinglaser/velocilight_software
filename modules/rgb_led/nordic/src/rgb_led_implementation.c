/**@file    rgb_led_implementation.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Nordic RGB_LED Source
 *
 * @addtogroup RGB_LED_IMPLEMENTATION
 * @{
 *
 * @defgroup RGB_LED_IMPLEMENTATION_PRIVATE RgbLedImplementation Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "rgb_led_implementation.h"

#include "nrf_gpio.h"

#include "ensure.h"
#include "util.h"

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

void rgb_led_implementation_pin_init(rgb_led_config_t const * config)
{
    ensure(config != NULL);

    nrf_gpio_cfg_output(config->r_pin_number);
    nrf_gpio_cfg_output(config->g_pin_number);
    nrf_gpio_cfg_output(config->b_pin_number);
}

void rgb_led_implementation_update(rgb_led_config_t const * config,
                                   bool r_on,
                                   bool g_on,
                                   bool b_on)
{
    ensure(config != NULL);

    nrf_gpio_pin_write(config->r_pin_number, r_on);
    nrf_gpio_pin_write(config->g_pin_number, g_on);
    nrf_gpio_pin_write(config->b_pin_number, b_on);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} defgroup RGB_LED_IMPLEMENTATION_PRIVATE */
/** @} addtogroup RGB_LED_IMPLEMENTATION */
