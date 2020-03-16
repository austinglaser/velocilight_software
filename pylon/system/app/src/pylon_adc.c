/**@file    pylon_adc.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   PylonAdc Source
 *
 * @addtogroup PYLON_ADC
 * @{
 *
 * @defgroup PYLON_ADC_PRIVATE PylonAdc Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "pylon_adc.h"

/* Supporting modules */
#include "ensure.h"

/* Third-party headers */
#include "hal.h"/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

static ADCConversionGroup _pylon_adc_grp = {
    .circular     = false,
    .num_channels = 1,
    .end_cb       = NULL,
    .error_cb     = NULL,
    .cr1          = 0,
    .cr2          = ADC_CR2_SWSTART,
    .smpr1        = 0,
    .smpr2        = 0,
    .sqr1         = ADC_SQR1_NUM_CH(1),
    .sqr2         = 0,
    .sqr3         = 0,
};

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void pylon_adc_init(void)
{
    adcStart(&ADCD1, NULL);
}

uint16_t pylon_adc_get(uint8_t channel)
{
    ensure(channel < 16);

    _pylon_adc_grp.sqr3 = ADC_SQR3_SQ1_N(channel);

    uint16_t sample;
    adcConvert(&ADCD1, &_pylon_adc_grp, &sample, 1);

    return sample;
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup PYLON_ADC_PRIVATE */
/** @} addtogroup PYLON_ADC */
