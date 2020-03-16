/**@file    ensure_modes.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureModes Interface
 */

#ifndef ENSURE_MODES_H
#define ENSURE_MODES_H

/**@defgroup ENSURE_MODES EnsureModes
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */


#ifdef ENSURE_HAS_PORT
#   include "ensure_modes_port.h"
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/** Ensure checks are disabled */
#define ENSURE_MODE_NONE            0

/** A failed ensure causes an exception */
#define ENSURE_MODE_C_EXCEPTION     1

/** Start of port-specific ensure modes */
#define ENSURE_MODE_PORT_BASE       256

/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** @} defgroup ENSURE_MODES */

#endif /* ifndef ENSURE_MODES_H */