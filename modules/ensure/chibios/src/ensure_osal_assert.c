/**@file    ensure_osal_assert.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureOsalAssert Source
 *
 * @addtogroup ENSURE_OSAL_ASSERT
 * @{
 *
 * @defgroup ENSURE_OSAL_ASSERT_PRIVATE EnsureOsalAssert Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

#include "ensure_osal_assert.h"

#include "osal.h"

#include "util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void ensure_osal_assert(bool condition)
{
    osalDbgAssert(condition, "Ensure failed");
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup ENSURE_OSAL_ASSERT_PRIVATE */
/** @} addtogroup ENSURE_OSAL_ASSERT */
