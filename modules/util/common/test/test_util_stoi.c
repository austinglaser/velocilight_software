/**@file    test_util.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Util Test Source
 *
 * @addtogroup UTIL
 * @{
 *
 * @defgroup UTIL_TEST Util Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* Test framework */
#include "unity.h"

/* Module under test */
#include "util.h"

/* Supporting modules */

/* Mocks, fakes, test support */

/* Source dependencies (present only to make Ceedling include the right
 * objects)
 */

/* Standard headers */
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

void test_util_stoi_converts_base_ten(void)
{
    int32_t val;
    char const * str;

    str = "0";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 10));
    TEST_ASSERT_EQUAL_INT32(0, val);

    str = "32";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 10));
    TEST_ASSERT_EQUAL_INT32(32, val);

    str = "-18";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 10));
    TEST_ASSERT_EQUAL_INT32(-18, val);

    /* INT32_MAX */
    str = "2147483647";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 10));
    TEST_ASSERT_EQUAL_INT32(2147483647, val);

    /* INT32_MIN */
    str = "-2147483648";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 10));
    TEST_ASSERT_EQUAL_INT32(-2147483648, val);
}

void test_util_stoi_converts_base_two(void)
{
    int32_t val;
    char const * str;

    str = "0";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 2));
    TEST_ASSERT_EQUAL_INT32(0, val);

    str = "0110";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 2));
    TEST_ASSERT_EQUAL_INT32(0b0110, val);

    str = "-11010110";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 2));
    TEST_ASSERT_EQUAL_INT32(-0b11010110, val);

    /* INT32_MAX */
    str = "01111111111111111111111111111111";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 2));
    TEST_ASSERT_EQUAL_INT32(2147483647, val);

    /* INT32_MIN */
    str = "-10000000000000000000000000000000";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 2));
    TEST_ASSERT_EQUAL_INT32(-2147483648, val);
}

void test_util_stoi_converts_base_sixteen(void)
{
    int32_t val;
    char const * str;

    str = "0";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 16));
    TEST_ASSERT_EQUAL_HEX32(0, val);

    str = "FABC";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 16));
    TEST_ASSERT_EQUAL_HEX32(0xFABC, val);

    str = "0xFABC";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 16));
    TEST_ASSERT_EQUAL_HEX32(0xFABC, val);

    str = "-83fd";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 16));
    TEST_ASSERT_EQUAL_HEX32(-0x83fd, val);

    str = "-0x83fd";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 16));
    TEST_ASSERT_EQUAL_HEX32(-0x83fd, val);

    /* INT32_MAX */
    str = "7FFFFFFF";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 16));
    TEST_ASSERT_EQUAL_HEX32(2147483647, val);

    /* INT32_MIN */
    str = "-80000000";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 16));
    TEST_ASSERT_EQUAL_HEX32(-2147483648, val);
}

void test_util_stoi_detects_base(void)
{
    int32_t val;
    char const * str;

    /* Defaults to decimal */
    str = "22";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 0));
    TEST_ASSERT_EQUAL_HEX32(22, val);

    /* Leading 0 is octal */
    str = "022";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 0));
    TEST_ASSERT_EQUAL_HEX32(022, val);

    /* Leading 0x  is hex */
    str = "0x22";
    TEST_ASSERT_EQUAL(ERROR_NONE, util_stoi(str, &val, 0));
    TEST_ASSERT_EQUAL_HEX32(0x22, val);
}

void test_util_stoi_detects_invalid_ints(void)
{
    int32_t val;
    char const * str;

    str = "";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 10));

    str = "092p";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 10));

    str = "d9932";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 10));

    str = "/.<.>\\;";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 10));
}

void test_util_stoi_detects_overflow(void)
{
    int32_t val;
    char const * str;

    /* INT32_MAX + 1 */
    str = "2147483648";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 10));

    /* INT32_MIN - 1 */
    str = "-2147483649";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 10));

    /* INT32_MAX + 1 */
    str = "10000000000000000000000000000000";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 2));

    /* INT32_MIN + 1 */
    str = "-10000000000000000000000000000001";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 2));

    /* INT32_MAX */
    str = "80000000";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 16));

    /* INT32_MIN */
    str = "-80000001";
    TEST_ASSERT_EQUAL(ERROR_PARAM, util_stoi(str, &val, 16));
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup UTIL_TEST */
/** @} addtogroup UTIL */
