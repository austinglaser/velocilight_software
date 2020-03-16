/**@file    fpga_image.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   FPGA Image
 */

#ifndef FPGA_IMAGE_H
#define FPGA_IMAGE_H

/**@defgroup FPGA_IMAGE FPGA Image
 * @{
 *
 * @brief Exposes the FPGA blob through C variables
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */

/** Starting address of the image */
extern void const * const fpga_image;

/** Bytes in the FPGA image */
extern const size_t fpga_image_len;

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** @} defgroup FPGA_IMAGE */

#endif /* ifndef FPGA_IMAGE_H */
