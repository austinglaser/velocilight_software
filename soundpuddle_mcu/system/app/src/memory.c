/**@file    memory.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Memory Source
 *
 * @addtogroup MEMORY
 * @{
 *
 * @defgroup MEMORY_PRIVATE Memory Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "memory.h"

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
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void memory_barrier_data(void)
{
    asm volatile ("dmb\n\t");
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup MEMORY_PRIVATE */
/** @} addtogroup MEMORY */
