/**@file    ensure_support.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureSupport Source
 *
 * @addtogroup ENSURE_SUPPORT
 * @{
 *
 * @defgroup ENSURE_SUPPORT_PRIVATE EnsureSupport Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

#include "ensure_support.h"

#include "CException.h"
#include "unity.h"
#include "unity_util.h"

#include "ensure.h"
#include "ensure_c_exception.h"

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

void assert_fails_ensure(void (*code)(void),
                         unsigned short line,
                         char const * message)
{
    char full_message[128];
    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Expected ensure() failure");

    CEXCEPTION_T e = CEXCEPTION_NONE;

    Try {
        code();
        UNITY_TEST_FAIL(line, full_message);
    } Catch (e) {
        UNITY_TEST_ASSERT_EQUAL_UINT(ENSURE_FAILED, e, line, full_message);
    }
}

void assert_fails_ensure_arg(void (*code)(void *),
                             void * arg,
                             unsigned short line,
                             char const * message)
{
    char full_message[128];
    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Expected ensure() failure");

    CEXCEPTION_T e = CEXCEPTION_NONE;

    Try {
        code(arg);
        UNITY_TEST_FAIL(line, full_message);
    } Catch (e) {
        UNITY_TEST_ASSERT_EQUAL_UINT(ENSURE_FAILED, e, line, full_message);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup ENSURE_SUPPORT_PRIVATE */
/** @} addtogroup ENSURE_SUPPORT */
