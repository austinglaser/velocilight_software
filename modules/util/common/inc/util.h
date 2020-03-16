/**@file    util.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Utility Interface
 */

#ifndef UTIL_H
#define UTIL_H

/**@defgroup UTIL Utilities
 * @{
 *
 * @brief   Miscellaneous helper utilities that don't fit in another module
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

/* Supporting modules */
#include "error.h"

/* Standard headers */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */

/** Returns the number of elements in array @p a
 *
 * @note    The array must have been declared in the current scope, not passed
 *           by reference into it
 */
#define ARRAY_ELEMENTS(a) (sizeof(a)/sizeof((a)[0]))

/** Marks a variable as legitimately unused, to silence a warning
 *
 * Useful as an implicit TODO, or to make a function conform to a signature
 * with more parameters than needed for the particular implementation.
 */
#ifndef UNUSED_VARIABLE
#    define UNUSED_VARIABLE(v) ((void) v)
#endif

/** Marks a function parameter as legitimately unused, to silence a warning
 *
 * Really the same thing as @ref UNUSED_VARIABLE, but distinct for readability
 *
 * Useful as an implicit TODO, or to make a function conform to a signature
 * with more parameters than needed for the particular implementation.
 */
#ifndef UNUSED_PARAMETER
#    define UNUSED_PARAMETER(p) UNUSED_VARIABLE(p)
#endif

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Converts @p str into an integer, writing it to @p val
 *
 * If the entirety of @p str does not represent a base @p base encoded integer,
 * returns ERROR_PARAM. Otherwise, returns ERROR_NONE.
 *
 * The @p base parameter has the same semantics as for strtol.
 *
 * @param[in] str:      String to convert
 * @param[out] val:     Converted value, if successful
 * @param[in] base:     Base to consider str in. "must be between 2 and 36
 *                      inclusive, or be the special value 0."
 */
err_t util_stoi(char const * str, int32_t * val, size_t base);

/** Returns min(@p a, @p b) */
uint8_t util_min8(uint8_t a, uint8_t b);

/** @} defgroup UTIL */

#endif /* ifndef UTIL_H */
