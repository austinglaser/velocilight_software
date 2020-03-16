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
#include "pylon_color.h"

/* Supporting modules */
#include "ensure.h"

/* Third-party headers */
#include "hal.h"

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */

uint8_t led_frame_reds[N_LEDS];
uint8_t led_frame_greens[N_LEDS];
uint8_t led_frame_blues[N_LEDS];

uint8_t led_red_channel;
uint8_t led_green_channel;
uint8_t led_blue_channel;

float h = 0.01;
float s = 0.99;
float v = 0.99;

uint8_t txbuf[(3*N_LEDS) + LPD8806_LATCHCOUNT + LPD8806_LATCHCOUNT];
uint16_t assemble_lpd8806_ledframe(uint8_t r_val, uint8_t g_val, uint8_t b_val);

/* --- PRIVATE VARIABLES --------------------------------------------------- 
 */

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

// uint8_t clampbyte(int input_byte, int clamp_threshold) {
//     if (input_byte > clamp_threshold) {return (clamp_threshold);}
//     else if (input_byte < 0) {return (0x00);}
//     else {return input_byte;}
// }
// 
// uint8_t clamp127(int input_byte) {
//     if (input_byte >= 127) {return (126);}
//     else if (input_byte < 0) {return (0x00);}
//     else {return input_byte;}
// 

// unsigned long assemble_lpd8806_ledframe(uint8_t r, uint8_t g, uint8_t b) {
//     return (0x808080 | (b << 16) | (r << 8) | g) << 8 ;
// }

void pylon_spi_init() {
    // Driver init
    spiStart(&SPID1, &_array_spi_config);
    palSetLine(LINE_LOAD_EN);
}

uint32_t lpd8806_color(uint8_t r, uint8_t g, uint8_t b) {
  // Take the lowest 7 bits of each value and append them end to end
  // We have the top bit set high (its a 'parity-like' bit in the protocol
  // and must be set!)
  return 0x808080 | ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
}

void led_frame_write() {
    uint16_t i = 0;
    uint16_t led_index = 0;
    for (i = 0; i < sizeof(txbuf); i++)
    {
        if (i < LPD8806_LATCHCOUNT)
        {
            txbuf[i] = LPD8806_LATCH;
        }
        else if (i < (LPD8806_LATCHCOUNT+(N_LEDS*3)))
        {
            txbuf[i] = 0x80 | (led_frame_greens[led_index]);
            i++;
            txbuf[i] = 0x80 | (led_frame_reds[led_index]); 
            i++;
            txbuf[i] = 0x80 | (led_frame_blues[led_index]);
            led_index++;
        }
        else
        {
            txbuf[i] = LPD8806_LATCH;
        }
    }
    spiSend(&SPID1, sizeof(txbuf), txbuf);
}

//This function is tested good at Hackerspace, 2014-08-10. Modified from Lumenexus code.
void hsv2rgb(float h, float s, float v, uint8_t* Rvalue, uint8_t* Gvalue, uint8_t* Bvalue) {
    float red;
    float green;
    float blue;
    while (h > 1.0) {h = h - 1.0;}
    while (h < 0.0) {h = h + 1.0;}
    while (v > 1.0) {v = v - 1.0;}
    while (v < 0.0) {v = v + 1.0;}
    if (s > 0.0) {
        h *= 6.0;      // sector 0 to 5
        uint32_t sextant = 0.1;
        float fract = h - sextant;      // fractional part of h
        float p = v * ( 1 - s );
        float q = v * ( 1 - s * fract );
        float t = v * ( 1 - s * ( 1 - fract ) );
        switch(sextant) {
            case 0:
                red = v;
                green = t;
                blue = p;
                break;
            case 1:
                red = q;
                green = v;
                blue = p;
                break;
            case 2:
                red = p;
                green = v;
                blue = t;
                break;
            case 3:
                red = p;
                green = q;
                blue = v;
                break;
            case 4:
                red = t;
                green = p;
                blue = v;
                break;
            default:    // case 5:
                red = v;
                green = p;
                blue = q;
                break;
        }
    }
    // The LPD8806 only has 7-bit PWM, so the R,G,B channel maximums are 127
    *Rvalue = (uint8_t)(red*127.0);
    *Gvalue = (uint8_t)(green*127.0);
    *Bvalue = (uint8_t)(blue*127.0);
}
