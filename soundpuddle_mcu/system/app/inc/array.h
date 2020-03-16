/**@file    array.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Array Interface
 */

#ifndef ARRAY_H
#define ARRAY_H

/**@defgroup ARRAY Array
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */
#include "framebuffer.h"

/* Third-party headers */
#include "hal.h"

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */

/** Number of addressed strips */
#define ARRAY_STRIP_NUM     72

/* Make sure the array and framebuffer modules agree as to how many strips
 * there are.
 *
 * We perform this check (rather than just using the framebuffer define)
 * because the number of strips is highly hardware dependent
 */
_Static_assert(ARRAY_STRIP_NUM == FB_STRIP_NUM, "Strip count mismatch");

/* --- PUBLIC DATATYPES ---------------------------------------------------- */

/** Configuration for an LED array */
typedef struct {
    SPIDriver * spi0;
    SPIDriver * spi1;

    ioline_t spi0_mosi;
    uint32_t spi0_mosi_af;
    ioline_t spi0_sck;
    uint32_t spi0_sck_af;

    ioline_t spi1_mosi;
    uint32_t spi1_mosi_af;
    ioline_t spi1_sck;
    uint32_t spi1_sck_af;

    ioline_t b0_b2_act;
    ioline_t b1_b3_act;
    ioline_t strip_act[ARRAY_STRIP_NUM/4];

    uint32_t (*frame_buffer)[FB_STRIP_BUFFER_SIZE];
} array_config_t;

/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Initialize the array-management subsystem
 *
 * @param[out] led:     LED management handle
 * @param[in] fpga:     LED frontend to use
 */
void array_init(void);

/** Exports the logical frame to the physical LEDs */
void array_write(void);

/** Writes black to the entire array */
void array_clear(void);

/** @} defgroup ARRAY */

#endif /* ifndef ARRAY_H */
