/**@file    ensure_port.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsurePort Interface
 */

#ifndef ENSURE_PORT_H
#define ENSURE_PORT_H

/**@defgroup ENSURE_PORT EnsurePort
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

#include "ensure_modes.h"

#include "ensure_osal_assert.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */

#if ENSURE_MODE == ENSURE_MODE_OSAL_ASSERT
#   define ensure(condition) ensure_osal_assert(condition)
#   define ensure_get_line() 0
#   define ensure_get_file() (NULL)
#endif

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** @} defgroup ENSURE_PORT */

#endif /* ifndef ENSURE_PORT_H */
