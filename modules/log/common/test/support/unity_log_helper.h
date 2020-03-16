/**@file    unity_log_helper.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   UnityLogHelper Interface
 */

#ifndef UNITY_LOG_HELPER_H
#define UNITY_LOG_HELPER_H

/**@defgroup UNITY_LOG_HELPER UnityLogHelper
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "log.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */

#define UNITY_TEST_ASSERT_EQUAL_log_binary_data_t(expected, actual, line, message) \
            AssertEqual_log_binary_data_t(expected, actual, line, message)

#define UNITY_TEST_ASSERT_EQUAL_log_entry_t(expected, actual, line, message) \
            AssertEqual_log_entry_t(expected, actual, line, message)

#define TEST_ASSERT_EQUAL_log_binary_data_t(expected, actual) \
            UNITY_TEST_ASSERT_EQUAL_log_binary_data_t(expected, actual, __LINE__, NULL)

#define TEST_ASSERT_EQUAL_log_entry_t(expected, actual) \
            UNITY_TEST_ASSERT_EQUAL_log_entry_t(expected, actual, __LINE__, NULL)

#define TEST_ASSERT_EQUAL_log_binary_data_t_MESSAGE(expected, actual, message) \
            UNITY_TEST_ASSERT_EQUAL_log_binary_data_t(expected, actual, __LINE__, message)

#define TEST_ASSERT_EQUAL_log_entry_t_MESSAGE(expected, actual, message) \
            UNITY_TEST_ASSERT_EQUAL_log_entry_t(expected, actual, __LINE__, message)

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void AssertEqual_log_binary_data_t(log_binary_data_t expected,
                                   log_binary_data_t actual,
                                   unsigned short line,
                                   const char * message);

void AssertEqual_log_entry_t(log_entry_t expected,
                             log_entry_t actual,
                             unsigned short line,
                             const char * message);

/** @} defgroup UNITY_LOG_HELPER */

#endif /* ifndef UNITY_LOG_HELPER_H */
