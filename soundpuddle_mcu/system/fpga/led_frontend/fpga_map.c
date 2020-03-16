/**@file    fpga_map.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   FpgaMap Source
 *
 * @addtogroup FPGA_MAP
 * @{
 *
 * @defgroup FPGA_MAP_PRIVATE FpgaMap Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "fpga_map.h"

/* Supporting modules */
#include "ensure.h"
#include "fpga.h"
#include "memory.h"
#include "util.h"

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */

fpga_t * const FPGA = (fpga_t *) FPGA_REG_BASE;

/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

uint16_t fpga_get_stat(fpga_t * fpga)
{
    ensure(fpga != NULL);

    memory_barrier_data();

    uint16_t val = fpga->STAT;

    return val;
}

void fpga_set_ctrl(fpga_t * fpga, uint16_t ctrl)
{
    ensure(fpga != NULL);

    fpga->CTRL = ctrl;

    memory_barrier_data();
}

void fpga_set_data(fpga_t * fpga, uint16_t data)
{
    ensure(fpga != NULL);

    fpga->DATA = data;

    memory_barrier_data();
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup FPGA_MAP_PRIVATE */
/** @} addtogroup FPGA_MAP */
