/**@file    ensure_osal_assert.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureOsalAssert Interface
 */

#ifndef ENSURE_OSAL_ASSERT_H
#define ENSURE_OSAL_ASSERT_H

/**@defgroup ENSURE_OSAL_ASSERT EnsureOsalAssert
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

#include "hal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** If @p condition is false, traps execution
 *
 * @param[in] condition     Condition to verify
 */
void ensure_osal_assert(bool condition);

/** @} defgroup ENSURE_OSAL_ASSERT */

#endif /* ifndef ENSURE_OSAL_ASSERT_H */
