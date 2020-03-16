/**@file    test_error.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Error Test Source
 *
 * @addtogroup ERROR
 * @{
 *
 * @defgroup ERROR_TEST Error Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

#include "unity.h"
#include "error.h"

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

void test_success_is_zero(void)
{
    TEST_ASSERT_EQUAL(0, ERROR_NONE);
}

void test_errors_are_negative(void)
{
    TEST_ASSERT_MESSAGE(ERROR_GENERIC < 0, "Generic error not negative");
    TEST_ASSERT_MESSAGE(ERROR_COMM    < 0, "Communication error not negative");
    TEST_ASSERT_MESSAGE(ERROR_PARAM   < 0, "Parameter error not negative");
    TEST_ASSERT_MESSAGE(ERROR_HW      < 0, "Hardware error not negative");
    TEST_ASSERT_MESSAGE(ERROR_TIMEOUT < 0, "Timeout error not negative");
    TEST_ASSERT_MESSAGE(ERROR_NOMEM   < 0, "Out-of-memory error not negative");
    TEST_ASSERT_MESSAGE(ERROR_NOENT   < 0, "No Entity error not negative");
}

void test_errors_are_unique(void)
{
    TEST_ASSERT_MESSAGE(ERROR_GENERIC != ERROR_COMM,
                        "Generic and Communication errors the same");
    TEST_ASSERT_MESSAGE(ERROR_GENERIC != ERROR_PARAM,
                        "Generic and Parameter errors the same");
    TEST_ASSERT_MESSAGE(ERROR_GENERIC != ERROR_HW,
                        "Generic and Hardware errors the same");
    TEST_ASSERT_MESSAGE(ERROR_GENERIC != ERROR_TIMEOUT,
                        "Generic and Timeout errors the same");
    TEST_ASSERT_MESSAGE(ERROR_GENERIC != ERROR_NOMEM,
                        "Generic and Out-of-Memory errors the same");
    TEST_ASSERT_MESSAGE(ERROR_GENERIC != ERROR_NOENT,
                        "Generic and No Entity errors the same");

    TEST_ASSERT_MESSAGE(ERROR_COMM != ERROR_PARAM,
                        "Communication and Parameter errors the same");
    TEST_ASSERT_MESSAGE(ERROR_COMM != ERROR_HW,
                        "Communication and Hardware errors the same");
    TEST_ASSERT_MESSAGE(ERROR_COMM != ERROR_TIMEOUT,
                        "Communication and Timeout errors the same");
    TEST_ASSERT_MESSAGE(ERROR_COMM != ERROR_NOMEM,
                        "Communication and Out-of-Memory errors the same");
    TEST_ASSERT_MESSAGE(ERROR_COMM != ERROR_NOENT,
                        "Communication and No Entity errors the same");

    TEST_ASSERT_MESSAGE(ERROR_PARAM != ERROR_HW,
                        "Parameter and Hardware errors the same");
    TEST_ASSERT_MESSAGE(ERROR_PARAM != ERROR_TIMEOUT,
                        "Parameter and Timeout errors the same");
    TEST_ASSERT_MESSAGE(ERROR_PARAM != ERROR_NOMEM,
                        "Parameter and Out-of-Memory errors the same");
    TEST_ASSERT_MESSAGE(ERROR_PARAM != ERROR_NOENT,
                        "Parameter and No Entity errors the same");

    TEST_ASSERT_MESSAGE(ERROR_HW != ERROR_TIMEOUT,
                        "Hardware and Timeout errors the same");
    TEST_ASSERT_MESSAGE(ERROR_HW != ERROR_NOMEM,
                        "Hardware and Out-of-Memory errors the same");
    TEST_ASSERT_MESSAGE(ERROR_HW != ERROR_NOENT,
                        "Hardware and No Entity errors the same");

    TEST_ASSERT_MESSAGE(ERROR_TIMEOUT != ERROR_NOMEM,
                        "Timeout and Out-of-Memory errors the same");
    TEST_ASSERT_MESSAGE(ERROR_TIMEOUT != ERROR_NOENT,
                        "Timeout and No Entity errors the same");

    TEST_ASSERT_MESSAGE(ERROR_NOMEM != ERROR_NOENT,
                        "Out-of-Memory and No Entity errors the same");
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup ERROR_TEST */
/** @} addtogroup ERROR */
