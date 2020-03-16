/**
 * @file    unity_color_helper.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   UnityColorHelper Interface
 */

#ifndef UNITY_COLOR_HELPER_H
#define UNITY_COLOR_HELPER_H

/**@defgroup UNITY_COLOR_HELPER UnityColorHelper
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "color.h"

#include <stdbool.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */

#define UNITY_TEST_ASSERT_EQUAL_color_t(expected, actual, line, message) \
            AssertEqual_color_t(expected, actual, line, message)

#define TEST_ASSERT_EQUAL_color_t(expected, actual) \
            UNITY_TEST_ASSERT_EQUAL_color_t(expected, actual, __LINE__, NULL)

#define TEST_ASSERT_EQUAL_color_t_MESSAGE(expected, actual, message) \
            UNITY_TEST_ASSERT_EQUAL_color_t(expected, actual, __LINE__, message)

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void AssertEqual_color_t(color_t expected,
                         color_t actual,
                         unsigned short line,
                         const char * message);

/** @} defgroup UNITY_COLOR_HELPER */

#endif /* ifndef UNITY_COLOR_HELPER_H */
