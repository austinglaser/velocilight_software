/**@file    test_ensure_mode_osal_assert.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureModeOsalAssert Test Source
 *
 * @addtogroup ENSURE_MODE_OSAL_ASSERT
 * @{
 *
 * @defgroup ENSURE_MODE_OSAL_ASSERT_TEST EnsureModeOsalAssert Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

#include "unity.h"

#undef ENSURE_MODE
#define ENSURE_MODE ENSURE_MODE_OSAL_ASSERT

#include "ensure.h"

#include "mock_ensure_osal_assert.h"

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

void test_ensure_calls_ensure_osal_assert(void)
{
    ensure_osal_assert_Expect(true);
    ensure(true);

    ensure_osal_assert_Expect(false);
    ensure(false);
}

void test_ensure_get_file_always_returns_null(void)
{
    ensure_osal_assert_Ignore();

    TEST_ASSERT_NULL(ensure_get_file());

    ensure(false);

    TEST_ASSERT_NULL(ensure_get_file());
}

void test_ensure_get_line_always_returns_zero(void)
{
    ensure_osal_assert_Ignore();

    TEST_ASSERT_EQUAL(0, ensure_get_line());

    ensure(false);

    TEST_ASSERT_EQUAL(0, ensure_get_line());
}

/* --- PUBLIC TESTS -------------------------------------------------------- */
/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup ENSURE_MODE_OSAL_ASSERT_TEST */
/** @} addtogroup ENSURE_MODE_OSAL_ASSERT */
