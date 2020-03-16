/**@file    test_ensure_c_exception.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestEnsureCException Source
 *
 * @addtogroup TEST_ENSURE_C_EXCEPTION
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"

#include "ensure_c_exception.h"

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

void test_ensure_c_exception_should_throw_no_exception_when_passed_true(void)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        ensure_c_exception(true, NULL, 0);
    }
    Catch (e) {
        TEST_FAIL_MESSAGE("true ensure should not throw exception");
    }

    TEST_ASSERT_EQUAL(e, CEXCEPTION_NONE);
}

void test_ensure_c_exception_should_not_record_file_when_passed_true(void)
{
    ensure_c_exception(true, "filename.c", 0);

    TEST_ASSERT_NULL(ensure_c_exception_get_file());
}

void test_ensure_c_exception_should_not_record_line_when_passed_true(void)
{
    ensure_c_exception(true, NULL, 388);

    TEST_ASSERT_EQUAL_UINT32(0, ensure_c_exception_get_line());
}

void test_ensure_c_exception_should_throw_exception_when_passed_false(void)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        ensure_c_exception(false, NULL, 0);
        TEST_FAIL_MESSAGE("false ensure should not fall through");
    }
    Catch (e) { }

    TEST_ASSERT_EQUAL(e, ENSURE_FAILED);
}

void test_ensure_c_exception_should_record_file_when_passed_false(void)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        ensure_c_exception(false, "filename.c", 0);
    }
    Catch (e) { }

    TEST_ASSERT_EQUAL_STRING("filename.c", ensure_c_exception_get_file());
}

void test_ensure_c_exception_should_record_line_when_passed_false(void)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        ensure_c_exception(false, NULL, 839);
    }
    Catch (e) { }

    TEST_ASSERT_EQUAL_UINT32(839, ensure_c_exception_get_line());
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_ENSURE_C_EXCEPTION */
