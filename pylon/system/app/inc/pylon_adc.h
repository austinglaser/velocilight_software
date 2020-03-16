/**@file    pylon_adc.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   PylonAdc Interface
 */

#ifndef PYLON_ADC_H
#define PYLON_ADC_H

/**@defgroup PYLON_ADC PylonAdc
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */

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

void pylon_adc_init(void);

uint16_t pylon_adc_get(uint8_t channel);

/** @} defgroup PYLON_ADC */

#endif /* ifndef PYLON_ADC_H */
