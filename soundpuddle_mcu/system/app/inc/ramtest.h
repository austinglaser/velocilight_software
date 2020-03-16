/**@file    ramtest.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Ramtest Interface
 */

#ifndef RAMTEST_H
#define RAMTEST_H

/**@defgroup RAMTEST Ramtest
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

bool ramtest8(void * start, size_t len);

bool ramtest16(void * start, size_t len);

bool ramtest32(void * start, size_t len);

/** @} defgroup RAMTEST */

#endif /* ifndef RAMTEST_H */
