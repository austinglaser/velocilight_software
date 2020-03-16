/**@file    ensure_modes_port.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureModesPort Interface
 */

#ifndef ENSURE_MODES_PORT_H
#define ENSURE_MODES_PORT_H

/**@defgroup ENSURE_MODES_PORT EnsureModesPort
 * @{
 *
 * @brief Chibios-specific ensure modes
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

#include "ensure_modes.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */

/** An ensure wraps an osalDbgAssert */
#define ENSURE_MODE_OSAL_ASSERT     (ENSURE_MODE_PORT_BASE)

/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** @} defgroup ENSURE_MODES_PORT */

#endif /* ifndef ENSURE_MODES_PORT_H */
