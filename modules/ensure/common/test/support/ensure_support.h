/**@file    ensure_support.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureSupport Interface
 */

#ifndef ENSURE_SUPPORT_H
#define ENSURE_SUPPORT_H

/**@defgroup ENSURE_SUPPORT EnsureSupport
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */

/** Assert that a code snippet should cause an ensure failure
 *
 * @param[in] code:     A void function pointer which should throw an ensure
 *                      failure
 */
#define TEST_ASSERT_FAILS_ENSURE(code) \
    assert_fails_ensure(code, __LINE__, NULL)

/** Assert that a code snippet should cause an ensure failure
 *
 * Passes a void pointer to the code
 *
 * @param[in] code:     A void function pointer which should throw an ensure
 *                      failure
 * @param[in] arg:      An argument to be passed to @p code
 */
#define TEST_ASSERT_FAILS_ENSURE_ARG(code, arg) \
    assert_fails_ensure_arg(code, arg, __LINE__, NULL)

/** Assert that a code snippet should cause an ensure failure
 *
 * Prints a custom message on failure
 *
 * @param[in] code:     A void function pointer which should throw an ensure
 *                      failure
 * @param[in] message:  A message to print
 */
#define TEST_ASSERT_FAILS_ENSURE_MESSAGE(code, message) \
    assert_fails_ensure(code, __LINE__, message)

/** Assert that a code snippet should cause an ensure failure
 *
 * Passes a void pointer to the code
 *
 * Prints a custom message on failure
 *
 * @param[in] code:     A void function pointer which should throw an ensure
 *                      failure
 * @param[in] message:  A message to print
 */
#define TEST_ASSERT_FAILS_ENSURE_ARG_MESSAGE(code, arg, message) \
    assert_fails_ensure_arg(code, arg, __LINE__, message)

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/**@brief   The provided code snippet should cause an ensure failure
 *
 * Generally should not be called directly, instead one of
 * TEST_ASSERT_FAILS_ENSURE or TEST_ASSERT_FAILS_ENSURE_MESSAGE should be
 * called.
 *
 * Relies on the default ENSURE_MODE of ENSURE_MODE_C_EXCEPTION.
 *
 * Should only be called within a unity unit test.
 *
 * @param[in] code:     A function pointer to a routine which is expected to
 *                      fail an ensure() test
 * @param[in] line:     Line number of assertion
 * @param[in] message:  An optional message
 */
void assert_fails_ensure(void (*code)(void),
                         unsigned short line,
                         char const * message);

/**@brief   The provided code snippet should cause an ensure failure
 *
 * Passes an argument to the code
 *
 * Generally should not be called directly, instead one of
 * TEST_ASSERT_FAILS_ENSURE or TEST_ASSERT_FAILS_ENSURE_MESSAGE should be
 * called.
 *
 * Relies on the default ENSURE_MODE of ENSURE_MODE_C_EXCEPTION.
 *
 * Should only be called within a unity unit test.
 *
 * @param[in] code:     A function pointer to a routine which is expected to
 *                      fail an ensure() test
 * @param[in] arg:      Argument to pass to @p code
 * @param[in] line:     Line number of assertion
 * @param[in] message:  An optional message
 */
void assert_fails_ensure_arg(void (*code)(void *),
                             void * arg,
                             unsigned short line,
                             char const * message);

/** @} defgroup ENSURE_SUPPORT */

#endif /* ifndef ENSURE_SUPPORT_H */
