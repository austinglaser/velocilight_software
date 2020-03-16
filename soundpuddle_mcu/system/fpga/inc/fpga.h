/**@file    fpga.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Fpga Interface
 */

#ifndef FPGA_H
#define FPGA_H

/**@defgroup FPGA Fpga
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */
#include "error.h"

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */

/** Base address for FPGA registers
 *
 * FPGA registers are accessible through SRAM Bank 2
 *
 * Specific registers will be declared in the header for the specific FPGA
 * image
 */
#define FPGA_REG_BASE       0x64000000

#include "fpga_map.h"

/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Initializes the FPGA image */
err_t fpga_init(void);

/** @} defgroup FPGA */

#endif /* ifndef FPGA_H */
