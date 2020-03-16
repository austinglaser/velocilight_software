/**@file    fpga.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Fpga Source
 *
 * @addtogroup FPGA
 * @{
 *
 * @defgroup FPGA_PRIVATE Fpga Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "fpga.h"

/* Supporting modules */
#include "error.h"
#include "fpga_image.h"

/* Third-party headers */
#include "ch.h"
#include "hal.h"
#include "hal_fsmc.h"
#include "hal_fsmc_sram.h"

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */

/** Configuration for FPGA SPI interface */
static const SPIConfig fpga_spi_config = {
    .end_cb = NULL,
    .ssport = PAL_PORT(LINE_FPGA_SPI_NSS),
    .sspad  = PAL_PAD(LINE_FPGA_SPI_NSS),
    .cr1    = SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA,
    .cr2    = 0,
};

/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

err_t fpga_init(void)
{
    spiStart(&FPGA_SPID, &fpga_spi_config);

    /* This must be done before the reset, so the iCE40 sees a low CS line when
     * it comes out of reset. If it doesn't, it'll go into SPI master mode and
     * configuration will fail.
     */
    spiSelect(&SPID1);

    /* Reset the iCE40, and wait for it to complete housekeeping tasks.
     *
     * The time required for housekeeping is listed as 800 us in the
     * programming guide, but other programmers observably wait longer (like
     * 2.5 ms). We are being very conservative because this code doesn't need
     * to be speed-optimized.
     */
    palClearLine(LINE_ICE40_RESET);
    chThdSleepMicroseconds(200);
    palSetLine(LINE_ICE40_RESET);
    chThdSleepMilliseconds(5);

    /* The fpga image must be broken into chunks here -- the DMA controller
     * has a length register 16 bits wide. If the FPGA's image is larger than
     * this (which it is), the SPI driver will SILENTLY drop the high-order
     * bits and perform a transfer smaller than what we want.
     *
     * A size of 4096 is conservatively small, but slightly smaller chunks
     * should make little difference performance-wise.
     */
    size_t n = 0;
    do {
        size_t len = (n + 4096 > fpga_image_len) ? fpga_image_len - n : 4096;
        spiSend(&SPID1, len, fpga_image + n);
        n += len;
    } while (n < fpga_image_len);

    /* The iCE40 requires at least 49 SCLK cycles to complete its
     * configuration. (7 bytes) * (8 cycles/byte) = 56 cycles >= 49
     */
    spiIgnore(&SPID1, 7);

    spiUnselect(&SPID1);

    /* CDONE should go high when the configuration is finished. */
    if (palReadLine(LINE_ICE40_CDONE) != PAL_HIGH) {
        return ERROR_HW;
    }

    return ERROR_NONE;
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup FPGA_PRIVATE */
/** @} addtogroup FPGA */
