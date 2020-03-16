/**@file    ensure_c_exception.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureCException Interface
 */

#ifndef ENSURE_C_EXCEPTION_H
#define ENSURE_C_EXCEPTION_H

/**@defgroup ENSURE_C_EXCEPTION EnsureCException
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/** Exception type thrown by failed ensures */
#define ENSURE_FAILED           0xEBAD0000

/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** If @p condition is false, throws an exception
 *
 * @param[in] line          Line where check occurs
 * @param[in] condition     Condition to verify
 *
 * @throws ENSURE_FAILED    if @p condition is false
 */
void ensure_c_exception(bool condition, char const * file, uint16_t line);

/** Retrieve line number at which an exception ocurred
 *
 * @return  The line number passed to @ref ensure_c_exception(), or 0 if no
 *          exception ocurred
 */
uint32_t ensure_c_exception_get_line(void);

/** Retrieve the file name in which an exception ocurred
 *
 * @return  The filename passed to @ref ensure_c_exception(), or NULL if no
 *          exception ocurred
 */
char const * ensure_c_exception_get_file(void);

/** @} defgroup ENSURE_C_EXCEPTION */

#endif /* ifndef ENSURE_C_EXCEPTION_H */
