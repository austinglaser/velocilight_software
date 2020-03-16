/**@file    test_ensure_osal_assert.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureOsalAssert Test Source
 *
 * @addtogroup ENSURE_OSAL_ASSERT
 * @{
 *
 * @defgroup ENSURE_OSAL_ASSERT_TEST EnsureOsalAssert Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

#include "unity.h"

#include "ensure_osal_assert.h"

#include "mock_osal.h"

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
/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_ensure_osal_assert_wraps_osal_assert(void)
{
    osalDbgAssert_Expect(true, "Ensure failed");
    ensure_osal_assert(true);

    osalDbgAssert_Expect(false, "Ensure failed");
    ensure_osal_assert(false);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup ENSURE_OSAL_ASSERT_TEST */
/** @} addtogroup ENSURE_OSAL_ASSERT */
