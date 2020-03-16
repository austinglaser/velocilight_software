/**@file    system_info.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   System Interface
 */

#ifndef SYSTEM_H
#define SYSTEM_H

/**@defgroup SYSTEM System
 * @{
 *
 * Provides abstractions for getting system_info information
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "system_info_implementation.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Get the current system_info time */
system_time_t system_info_get_time(void);

/** Get the value of the link register
 *
 * This will be the link register's value in the calling function
 */
size_t system_info_get_lr(void);

/** Get the current stack pointer */
size_t system_info_get_sp(void);

/** Get the maximum stack used up to this point in execution */
size_t system_info_get_stack_used(void);

/** @} defgroup SYSTEM */

#endif /* ifndef SYSTEM_H */
