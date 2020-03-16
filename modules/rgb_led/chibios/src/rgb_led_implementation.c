/**
 * @file    rgb_led_implementation.c
 * @author  Krithik Chandrashekar <krithik@boulderes.com>
 * @brief   Generic RGB Led Interface Source
 *
 * @addtogroup RGB_LED
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "rgb_led_implementation.h"

#include "ensure.h"

#include "ch.h"
#include "hal.h"

#include <stdbool.h>
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

    palSetLineMode(config->r_line, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(config->g_line, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(config->b_line, PAL_MODE_OUTPUT_PUSHPULL);
}

void rgb_led_implementation_update(rgb_led_config_t const * config,
                                   bool r_on,
                                   bool g_on,
                                   bool b_on)
{
    ensure(config != NULL);

    palWriteLine(config->r_line, r_on);
    palWriteLine(config->g_line, g_on);
    palWriteLine(config->b_line, b_on);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup RGB_LED */