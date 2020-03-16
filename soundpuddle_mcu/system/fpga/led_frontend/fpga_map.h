/**@file    fpga_map.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   FpgaMap Interface
 */

#ifndef FPGA_MAP_H
#define FPGA_MAP_H

/**@defgroup FPGA_MAP FpgaMap
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

/** IDLE bit in FPGA->STAT */
#define FPGA_STAT_IDLE          0x0001

/** GO bit in FPGA->CTRL */
#define FPGA_CTRL_GO            0x0001

/* --- PUBLIC DATATYPES ---------------------------------------------------- */

/** FPGA register map */
typedef struct __attribute((aligned(2))) {
    /** STAT register
     *
     * \verbatim
         1 1 1 1 1 1
         5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
        +-----------------------------+-+
        + RESERVED                    |I+
        +-----------------------------+-+
     \endverbatim
     *
     * Read-only
     *
     * I: high when the device is idle, and low while it is actively writing a
     * frame
     */
    volatile uint16_t STAT;

    /** CTRL register
     *
     * \verbatim
         1 1 1 1 1 1
         5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
        +-----------------------------+-+
        + RESERVED                    |S+
        +-----------------------------+-+
     \endverbatim
     *
     * Write-only
     *
     * Write S high to start the transmission of a frame. This also has the effect
     * of resetting the strip index to zero (see the DATA register).
     *
     * This bit will ultimately be self-clearing, but currently it must be
     * manually cleared. This is best done immediately after writing it high.
     */
    volatile uint16_t CTRL;
    /** DATA register
     *
     * \verbatim
         1 1 1 1 1 1
         5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
        +-------------------------------+
        + STRIP                         +
        +-------------------------------+
     \endverbatim
     *
     * Write-only
     *
     * Data written here will be transmitted on SPI channel N when CTRL.S is next
     * written high (see register CTRL).
     *
     * N here is an auto-incrementing value. At reset, and at each transmission,
     * it is reset to zero. Otherwise, it increments each time DATA is written. It
     * wraps modulo 72.
     */
    volatile uint16_t DATA;
} fpga_t;

/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */

/** Handle for FPGA-access operations */
extern fpga_t * const FPGA;

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Gets the current value in the STAT register */
uint16_t fpga_get_stat(fpga_t * fpga);

/** Write a value to the CTRL register */
void fpga_set_ctrl(fpga_t * fpga, uint16_t ctrl);

/** Write a value to the DATA register */
void fpga_set_data(fpga_t * fpga, uint16_t data);

/** @} defgroup FPGA_MAP */

#endif /* ifndef FPGA_MAP_H */
