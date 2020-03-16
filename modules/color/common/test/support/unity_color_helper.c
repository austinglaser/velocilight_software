/**
 * @file    unity_color_helper.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   UnityColorHelper Source
 *
 * @addtogroup UNITY_COLOR_HELPER
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"
#include "unity_color_helper.h"
#include "unity_util.h"

#include "color.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

static const float color_delta = 0.0001;

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void AssertEqual_color_t(color_t expected,
                         color_t actual,
                         unsigned short line,
                         const char * message)
{
    char full_message[128];

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Color Type");
    UNITY_TEST_ASSERT_EQUAL_INT(expected.type, actual.type,
                                line, full_message);

    if (expected.type == COLOR_TYPE_RGB) {
        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Red channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.r, actual.r,
                                       line, full_message);

        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Green channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.g, actual.g,
                                       line, full_message);

        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Blue channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.b, actual.b,
                                       line, full_message);
    }
    else if (expected.type == COLOR_TYPE_HSV) {
        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Hue channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.h, actual.h,
                                       line, full_message);

        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Saturation channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.s, actual.s,
                                       line, full_message);

        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Value channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.v, actual.v,
                                       line, full_message);
    }
    else if (expected.type == COLOR_TYPE_HSL) {
        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Hue channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.h, actual.h,
                                       line, full_message);

        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Saturation channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.s, actual.s,
                                       line, full_message);

        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Lightness channel");
        UNITY_TEST_ASSERT_FLOAT_WITHIN(color_delta,
                                       expected.l, actual.l,
                                       line, full_message);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup UNITY_COLOR_HELPER */
