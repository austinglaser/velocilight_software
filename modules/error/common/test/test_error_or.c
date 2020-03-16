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

/** If called more than one, fails the test
 *
 * Takes a pointer to a bool in which the function stores state
 */
static err_t _fails_if_called_twice(bool * called_before);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */
/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_error_preserve_returns_none_when_both_values_none(void)
{
    err_t err = ERROR_OR(ERROR_NONE, ERROR_NONE);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
}

void test_error_preserve_returns_error_when_only_one_error(void)
{
    err_t err1 = ERROR_OR(ERROR_NONE,  ERROR_GENERIC);
    err_t err2 = ERROR_OR(ERROR_PARAM, ERROR_NONE);
    TEST_ASSERT_EQUAL(ERROR_GENERIC, err1);
    TEST_ASSERT_EQUAL(ERROR_PARAM,   err2);
}

void test_error_preserve_returns_original_when_both_error(void)
{
    err_t err = ERROR_OR(ERROR_PARAM, ERROR_GENERIC);
    TEST_ASSERT_EQUAL(ERROR_PARAM, err);
}

void test_error_preserve_is_short_circuit(void)
{
    int i = 0;

    err_t err = ERROR_OR(ERROR_PARAM, i++);

    TEST_ASSERT_EQUAL(ERROR_PARAM, err);
    TEST_ASSERT_EQUAL(0, i);
}

/** Ensures that ERROR_OR doesn't suffer from a double-evaluation bug.
 *
 * Getting short-circuit evaluation in a function-like mannner requires us to
 * use a macro. But with use of a macro comes all the associated pitfalls.
 *
 * This test fails if ERROR_OR() evaluates either of its arguments more
 * than once. Note that (as tested above) ERROR_OR IS allowed to never
 * evaluate the second argument.
 */
void test_error_preserve_evaluates_arguments_once(void)
{
    bool called_before;

    called_before = false;
    err_t err = ERROR_OR(_fails_if_called_twice(&called_before),
                               ERROR_NONE);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);

    called_before = false;
    err = ERROR_OR(ERROR_NONE,
                         _fails_if_called_twice(&called_before));
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static err_t _fails_if_called_twice(bool * called_before)
{
    if (*called_before) {
        TEST_FAIL_MESSAGE("Function called twice!");
    }

    *called_before = true;

    return ERROR_NONE;
}

/** @} defgroup ERROR_TEST */
/** @} addtogroup ERROR */
