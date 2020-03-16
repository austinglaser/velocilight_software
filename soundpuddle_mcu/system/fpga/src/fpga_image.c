/**@file    fpga_image.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   FpgaImage Source
 *
 * @addtogroup FPGA_IMAGE
 * @{
 *
 * @defgroup FPGA_IMAGE_PRIVATE FpgaImage Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "fpga_image.h"

/* Supporting modules */

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

/** Raw start address from the fpga blob
 *
 * Like linker script variables, the values we care about are the *addresses*
 * of these symbols, not their actual values.
 *
 * Unfortunately, there's no type which makes the below casts unnecessary.
 * Logically, this is an addresss, so the void * type is less wrong than
 * others.
 */
extern void * _binary_fpga_blob_start;

/** Raw length from the fpga blob
 *
 * Like linker script variables, the values we care about are the *addresses*
 * of these symbols, not their actual values.
 *
 * Unfortunately, there's no type which makes the below casts unnecessary.
 * Logically, this is an addresss, so the void * type is less wrong than
 * others.
 */
extern void * _binary_fpga_blob_size;

/* --- PUBLIC VARIABLES ---------------------------------------------------- */

void const * const fpga_image = (void *) &_binary_fpga_blob_start;

const size_t fpga_image_len = (size_t) &_binary_fpga_blob_size;

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */
/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup FPGA_IMAGE_PRIVATE */
/** @} addtogroup FPGA_IMAGE */
