/**@file    test_ensure_mode_off.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureModeOff Test Source
 *
 * @addtogroup ENSURE_MODE_OFF
 * @{
 *
 * @defgroup ENSURE_MODE_NONE_TEST EnsureModeNone Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

#include "unity.h"

#undef ENSURE_MODE
#define ENSURE_MODE ENSURE_MODE_OFF

#include "ensure.h"

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

void test_ensure_does_nothing(void)
{
    ensure(true);

    ensure(false);
}

void test_ensure_get_file_always_returns_null(void)
{
    TEST_ASSERT_NULL(ensure_get_file());

    ensure(false);

    TEST_ASSERT_NULL(ensure_get_file());
}

void test_ensure_get_line_always_returns_zero(void)
{
    TEST_ASSERT_EQUAL(0, ensure_get_line());

    ensure(false);

    TEST_ASSERT_EQUAL(0, ensure_get_line());
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup ENSURE_MODE_NONE_TEST */
/** @} addtogroup ENSURE_MODE_NONE */
