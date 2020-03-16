/**@file    pylon_color.h
 * @author  John English <john@boulderes.com>
 * @brief   Pylon color utilities
 */

#ifndef PYLON_COLOR_H
#define PYLON_COLOR_H

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Chibios
#include "ch.h"
#include "hal.h"

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
#define N_LEDS 255
#define LPD8806_LATCH 0x00 //TODO put this in a seperate lpd8806.h file
#define LPD8806_LATCHCOUNT 4 //TODO put this in a seperate lpd8806.h file

/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */

extern uint8_t txbuf[(3*N_LEDS) + LPD8806_LATCHCOUNT + LPD8806_LATCHCOUNT];

static const SPIConfig _array_spi_config = {
    .end_cb = NULL,
    .cr1 = SPI_CR1_BR_0 | SPI_CR1_BR_2 | SPI_CR1_CPOL | SPI_CR1_CPHA,
};

// float h = 0.0;
// float s = 0.99;
// float v = 0.2;
extern uint8_t led_frame_reds[N_LEDS];
extern uint8_t led_frame_greens[N_LEDS];
extern uint8_t led_frame_blues[N_LEDS];
extern uint8_t led_red_channel;
extern uint8_t led_green_channel;
extern uint8_t led_blue_channel;
// extern float h;
// extern float s;
// extern float v;

uint16_t assemble_lpd8806_ledframe(uint8_t r_val, uint8_t g_val, uint8_t b_val);

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */
void hsv2rgb(float hue, float sat, float val, uint8_t* r_val, uint8_t* g_val, uint8_t* b_val);
void led_frame_write(void);
void pylon_spi_init(void);
// unsigned long assemble_lpd8806_ledframe(uint8_t r, uint8_t g, uint8_t b);

#endif /* ifndef PYLON_COLOR_H */
