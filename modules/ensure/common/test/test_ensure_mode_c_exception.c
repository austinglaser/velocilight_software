/**@file    test_ensure_mode_c_exception.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestEnsureModeCException Source
 *
 * @addtogroup TEST_ENSURE_MODE_C_EXCEPTION
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"

#include "ensure_modes.h"

#undef  ENSURE_MODE
#define ENSURE_MODE ENSURE_MODE_C_EXCEPTION

#include "ensure.h"
#include "mock_ensure_c_exception.h"

#include "CException.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */
/* --- TESTS ---------------------------------------------------------------- */

void test_ensure_passes_condition_to_c_exception(void)
{
    ensure_c_exception_Expect(true, NULL, 0);
    ensure_c_exception_IgnoreArg_file();
    ensure_c_exception_IgnoreArg_line();

    ensure(true);

    ensure_c_exception_Expect(false, NULL, 0);
    ensure_c_exception_IgnoreArg_file();
    ensure_c_exception_IgnoreArg_line();

    ensure(false);
}

void test_ensure_passes_file_to_c_exception(void)
{
    ensure_c_exception_Expect(false, __FILE__, 0);
    ensure_c_exception_IgnoreArg_condition();
    ensure_c_exception_IgnoreArg_line();

    ensure(false);
}

void test_ensure_passes_line_to_c_exception(void)
{
    /* TODO: __LINE__ + 4 is fairly brittle, and more than a little hacky */
    ensure_c_exception_Expect(false, NULL, __LINE__ + 4);
    ensure_c_exception_IgnoreArg_condition();
    ensure_c_exception_IgnoreArg_file();

    ensure(false);
}

void test_ensure_get_line_calls_c_exception_get_line(void)
{
    ensure_c_exception_get_line_ExpectAndReturn(33);

    TEST_ASSERT_EQUAL_UINT32(33, ensure_get_line());
}

void test_ensure_get_file_calls_c_exception_get_file(void)
{
    ensure_c_exception_get_file_ExpectAndReturn("some/file/path.c");

    TEST_ASSERT_EQUAL_STRING("some/file/path.c", ensure_get_file());
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_ENSURE_MODE_C_EXCEPTION */
