/**
 * @file    main.c
 * @author  John English <johnisenglish@gmail.com>
 * @brief   Application Entry Point
 *
 * @defgroup MAIN Main
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

// Standard
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// Modules
#include "audio.h"
#include "color.h"
#include "error.h"
#include "fft.h"
#include "pylon_adc.h"
#include "pylon_color.h"
#include "util.h"

// Chibios
#include "ch.h"
#include "hal.h"

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

uint16_t mic_window_power(uint16_t n);
uint16_t mic_window_max(uint16_t n);
void led_pixel_random(uint16_t n, uint16_t amplitude);
void mic_capture_window(uint8_t);
void shift_buffers(void);
void shift_buffers_backwards(void);

/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

#define MIC_WINDOW_SIZE 8

/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static uint16_t mic_window[MIC_WINDOW_SIZE];

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/**
 * @brief   Application entry point
 */
int main(void)
{
    // Chibios init
    halInit();
    chSysInit();

    palToggleLine(LINE_LOAD_EN);
    palSetLine(LINE_LOAD_EN);

    audio_init();

    pylon_spi_init();

    srand(0);

    // Application init

    for (uint32_t i = 0; i < N_LEDS; i++) {
        led_frame_reds[i]   = 0;
        led_frame_greens[i] = 0;
        led_frame_blues[i]  = 0;
    }
    led_frame_write();

    // Main loop
    while (true) {

        static uint16_t audio_data[FFT_SAMPLE_SIZE];
        static float32_t fft_mag[FFT_SAMPLE_SIZE/2];
        static float32_t brightness[N_LEDS];

        audio_get(audio_data, ARRAY_ELEMENTS(audio_data));
        chSysLock();
        fft_execute_16(audio_data, fft_mag);
        chSysUnlock();

        for (uint32_t i = 0; i < N_LEDS; i++) {
            static const float32_t beta = 0.1;
            brightness[i] *= 1 - beta;
            brightness[i] += beta * fft_mag[i + 16] / 35000.0;
            if (brightness[i] > 1.0) {
                brightness[i] = 1.0;
            }

            color_t color = COLOR_HSV_INIT(0.0, 0.0, brightness[i]);
            color_convert(&color, COLOR_TYPE_RGB);

            led_frame_reds[N_LEDS - i] = color.r * 255;
            led_frame_greens[N_LEDS - i] = color.g * 255;
            led_frame_blues[N_LEDS - i] = color.b * 255;
        }

        palToggleLine(LINE_STATUS_LED);

        led_frame_write();
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

void shift_buffers(void)
{
    int i;
    for (i = N_LEDS - 1; i > 0; i--) {
       led_frame_reds[i] = led_frame_reds[i-1];
        led_frame_greens[i] = led_frame_greens[i-1];
        led_frame_blues[i] = led_frame_blues[i-1];
    }
}

void shift_buffers_backwards(void)
{
    int i;
    for (i = 0; i < N_LEDS; i++) {
        led_frame_reds[i] = led_frame_reds[1 + i];
        led_frame_greens[i] = led_frame_greens[1 + i];
        led_frame_blues[i] = led_frame_blues[1 + i];
    }
}

void led_pixel_random(uint16_t n, uint16_t amplitude)
{
    uint8_t rand_temp_modulus = amplitude;
    uint8_t led_random_value = rand()%rand_temp_modulus;
    led_frame_reds[n] = (uint8_t)(led_random_value);
    led_random_value = rand()%rand_temp_modulus;
    led_frame_greens[n] = (uint8_t)(led_random_value);
    led_random_value = rand()%rand_temp_modulus;
    led_frame_blues[n] = (uint8_t)(led_random_value);
}


void mic_capture_window(uint8_t mic_n)
{
    for (int i = 0; i < mic_n; i++) {
        uint16_t mic_val = (pylon_adc_get(6));
        mic_window[mic_n] = mic_val;
    }
}

uint16_t mic_window_power(uint16_t n)
{
    uint16_t mic_power_window[n];
    uint16_t mic_window_sum = 0;
    uint16_t mic_window_average = 0;
    for (int i = 0; i < n; i++) {
        if (mic_window[n] > 2048) {mic_power_window[n] = mic_window[n] - 2048;}
        else {mic_power_window[n] = 0;}
        mic_window_sum = mic_window_sum + mic_power_window[n];
    }
    mic_window_average = mic_window_sum / n;
    return(mic_window_average);
}

uint16_t mic_window_max(uint16_t n)
{
    uint16_t mic_window_max_val = 0;
    for (int i = 0; i < n; i++) {
        if (mic_window[n] > mic_window_max_val) {
            mic_window_max_val = mic_window[n];
        }
    }
    return(mic_window_max_val);
}

/** @} defgroup MAIN */
