/**@file    ensure.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Ensure Interface
 */

#ifndef ENSURE_H
#define ENSURE_H

/**@defgroup ENSURE Ensure
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "ensure_modes.h"
#include "ensure_c_exception.h"

#ifdef ENSURE_HAS_PORT
#   include "ensure_port.h"
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */

#if !defined(ENSURE_MODE) && !defined(__DOXYGEN__)
#   error "Ensure mode must be set. See ensure_modes.h"
#endif

#if ENSURE_MODE == ENSURE_MODE_OFF
#   define ensure(condition)
#   define ensure_get_line() 0
#   define ensure_get_file() NULL
#endif

#if ENSURE_MODE == ENSURE_MODE_C_EXCEPTION
#   define ensure(condition) ensure_c_exception(condition, __FILE__, __LINE__)
#   define ensure_get_line() ensure_c_exception_get_line()
#   define ensure_get_file() ensure_c_exception_get_file()
#endif

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** @} defgroup ENSURE */

#endif /* ifndef ENSURE_H */