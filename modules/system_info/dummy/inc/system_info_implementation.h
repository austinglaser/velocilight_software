/**@file    system_info_implementation.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Dummy System Implementation Interface
 */

#ifndef SYSTEM_IMPLEMENTATION_H
#define SYSTEM_IMPLEMENTATION_H

/**@defgroup SYSTEM_IMPLEMENTATION SystemImplementation
 * @{
 *
 * Provides dummy types approprieate for mock system_info tests
 *
 * @warning Get rid of this when an actual implementation is written
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** The maximum size of system_info time */
typedef uint64_t system_time_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** @} defgroup SYSTEM_IMPLEMENTATION */

#endif /* ifndef SYSTEM_IMPLEMENTATION_H */
