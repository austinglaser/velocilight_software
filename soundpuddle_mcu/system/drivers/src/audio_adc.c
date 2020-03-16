/**@file    audio_adc.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   AudioAdc Source
 *
 * @addtogroup AUDIO_ADC
 * @{
 *
 * @defgroup AUDIO_ADC_PRIVATE AudioAdc Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "audio.h"

/* Supporting modules */
#include "ensure.h"
#include "util.h"

/* Third-party headers */
#include "hal.h"

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */

#define AUDIO_BUFFER_LEN        512
#define AUDIO_BUFFER_NUM        17

/* --- PRIVATE DATATYPES --------------------------------------------------- */

typedef struct {
    binary_semaphore_t done;
    size_t buf_idx;
    uint16_t buf[AUDIO_BUFFER_NUM][AUDIO_BUFFER_LEN];
} audio_adc_t;

/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */

static void _audio_adc_end(ADCDriver * adcp, adcsample_t * buffer, size_t n);

static void _audio_adc_error(ADCDriver * adcp, adcerror_t err);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

static const ADCConversionGroup _audio_adc_grp = {
    .circular     = false,
    .num_channels = 1,
    .end_cb       = _audio_adc_end,
    .error_cb     = _audio_adc_error,
    .cr1          = 0,
    .cr2          = ADC_CR2_SWSTART,
    .smpr1        = ADC_SMPR1_SMP_AN11(7), /* 480 + 12 cycles */
    .smpr2        = 0,
    .sqr1         = ADC_SQR1_NUM_CH(1),
    .sqr2         = 0,
    .sqr3         = ADC_SQR3_SQ1_N(11),
};

static audio_adc_t audio;

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void audio_init(void)
{
    chBSemObjectInit(&audio.done, true);

    audio.buf_idx = 0;
    memset(audio.buf, 0, sizeof(audio.buf));

    adcStart(&ADCD1, NULL);
    adcStartConversion(&ADCD1,
                       &_audio_adc_grp,
                       audio.buf[audio.buf_idx],
                       AUDIO_BUFFER_LEN);
}

void audio_get(uint16_t * samples, size_t n)
{
    UNUSED_PARAMETER(samples);

    ensure(0 < n && n <= (AUDIO_BUFFER_NUM - 1)*AUDIO_BUFFER_LEN);
    ensure(n % AUDIO_BUFFER_LEN == 0);

    chBSemReset(&audio.done, true);

    chBSemWait(&audio.done);

    chSysLock();

    size_t copy_count = n / AUDIO_BUFFER_LEN;
    size_t buf_cpy = audio.buf_idx + AUDIO_BUFFER_NUM - copy_count;
    if (buf_cpy >= AUDIO_BUFFER_NUM) {
        buf_cpy -= AUDIO_BUFFER_NUM;
    }

    size_t copied = 0;

    do {
        memcpy(&samples[copied],
               audio.buf[buf_cpy],
               AUDIO_BUFFER_LEN*sizeof(uint16_t));
        copied += AUDIO_BUFFER_LEN;

        buf_cpy++;
        if (buf_cpy >= AUDIO_BUFFER_NUM) {
            buf_cpy = 0;
        }
    } while(copied < n);

    chSysUnlock();
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _audio_adc_end(ADCDriver * adcp, adcsample_t * buffer, size_t n)
{
    chSysLockFromISR();

    ensure(adcp == &ADCD1);
    ensure(buffer == audio.buf[audio.buf_idx]);
    ensure(n == AUDIO_BUFFER_LEN);

    audio.buf_idx++;
    if (audio.buf_idx >= AUDIO_BUFFER_NUM) {
        audio.buf_idx = 0;
    }

    chBSemSignalI(&audio.done);

    adcStartConversionI(&ADCD1,
                        &_audio_adc_grp,
                        audio.buf[audio.buf_idx],
                        AUDIO_BUFFER_LEN);

    chSysUnlockFromISR();
}

static void _audio_adc_error(ADCDriver * adcp, adcerror_t err)
{
    UNUSED_PARAMETER(adcp);
    UNUSED_PARAMETER(err);

    chSysLockFromISR();

    while (true);
}

/** @} defgroup AUDIO_ADC_PRIVATE */
/** @} addtogroup AUDIO_ADC */
