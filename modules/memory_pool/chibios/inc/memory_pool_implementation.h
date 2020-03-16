/**@file    memory_pool_implementation.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   MemoryPoolImplementation Interface
 */

#ifndef MEMORY_POOL_IMPLEMENTATION_H
#define MEMORY_POOL_IMPLEMENTATION_H

/**@defgroup MEMORY_POOL_IMPLEMENTATION MemoryPoolImplementation
 * @{
 *
 * @brief   Implementation of memory pools for a chibios platform
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "ch.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** Our memory pool type is really just an alias for ChibiOS' */
typedef memory_pool_t mem_pool_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** @} defgroup MEMORY_POOL_IMPLEMENTATION */

#endif /* ifndef MEMORY_POOL_IMPLEMENTATION_H */
