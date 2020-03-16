/**@file    led_internal.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LedInternal Interface
 */

#ifndef LED_INTERNAL_H
#define LED_INTERNAL_H

/**@defgroup LED_INTERNAL LedInternal
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */
#include "led.h"

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Writes a single line to the FPGA
 *
 * Assumes @p line is a pointer to an array of length N_STRIPS.
 *
 * Not intended for use by external modules
 */
void led_internal_write_line(led_t * led, uint16_t const * line);

/** @} defgroup LED_INTERNAL */

#endif /* ifndef LED_INTERNAL_H */
