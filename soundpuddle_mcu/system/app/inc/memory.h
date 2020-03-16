/**@file    memory.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Memory Interface
 */

#ifndef MEMORY_H
#define MEMORY_H

/**@defgroup MEMORY Memory
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
/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Forces all in-proces memory transactions to complete before continuing */
void memory_barrier_data(void);

/** @} defgroup MEMORY */

#endif /* ifndef MEMORY_H */
