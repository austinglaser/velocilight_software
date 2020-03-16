/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   ArrayCartSnake Test Source
///
/// @addtogroup ARRAY_CART_SNAKE
/// @{
///
/// @defgroup ARRAY_CART_SNAKE_TEST ArrayCartSnake Tests
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// Test arraywork
#include "unity.h"

// Module under test
#include "array_cart_snake.h"

// Supporting modules
#include "color.h"

// Mocks, fakes, test support
#include "mock_led_strip.h"
#include "unity_util.h"

// Source dependencies (present only to make Ceedling include the right
// objects)

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //
// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //
// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //

// --- PUBLIC FUNCTIONS ---------------------------------------------------- //
// --- PUBLIC TESTS -------------------------------------------------------- //

void test_array_cart_snake_init_writes_all_black(void) {
    static const size_t x = 3;
    static const size_t y = 4;

    led_strip_t strip;
    led_strip_length_ExpectAndReturn(&strip, x * y);
    led_strip_write_all_ExpectAndReturn(
        &strip,
        (color_t) COLOR_RGB_INIT(0., 0., 0.),

        ERROR_NONE
    );

    array_cart_snake_t array;
    color_t buf[x * y];
    TEST_ASSERT_EQUAL(
        ERROR_NONE,
        array_cart_snake_init(&array, &strip, x, y, buf)
    );
}

TEST_VALUE(ERROR_HW)
TEST_VALUE(ERROR_COMM)
TEST_VALUE(ERROR_PARAM)
void test_array_cart_snake_init_detects_write_all_failure(int err) {
    static const size_t x = 3;
    static const size_t y = 4;

    led_strip_t strip;
    led_strip_length_ExpectAndReturn(&strip, x * y);
    led_strip_length_IgnoreAndReturn(x * y);
    led_strip_write_all_IgnoreAndReturn(err);

    array_cart_snake_t array;
    color_t buf[x * y];
    TEST_ASSERT_EQUAL(err, array_cart_snake_init(&array, &strip, x, y, buf));
}

TEST_VALUE(0, 1, 1)
TEST_VALUE(1, 2, 1)
TEST_VALUE(1, 1, 2)
TEST_VALUE(0, 3, 4)
TEST_VALUE(11, 3, 4)
TEST_VALUE(255, 32, 8)
TEST_VALUE(255, 16, 16)
void test_array_cart_snake_init_checks_strip(size_t l, size_t x, size_t y) {
    TEST_ASSERT_MESSAGE(l < x * y, "Strip must be too short for this test");

    led_strip_t strip;
    led_strip_length_ExpectAndReturn(&strip, l);
    led_strip_write_all_IgnoreAndReturn(ERROR_NONE);

    array_cart_snake_t array;
    color_t buf[x * y];
    TEST_ASSERT_EQUAL(
        ERROR_NOMEM,
        array_cart_snake_init(&array, &strip, x, y, buf)
    );
}

TEST_VALUE(2, 1, 1)
TEST_VALUE(3, 2, 1)
TEST_VALUE(3, 1, 2)
TEST_VALUE(13, 3, 4)
TEST_VALUE(18, 3, 4)
TEST_VALUE(257, 32, 8)
TEST_VALUE(257, 16, 16)
void test_array_cart_snake_init_accepts_long_strip(size_t l, size_t x, size_t y) {
    TEST_ASSERT_MESSAGE(l > x * y, "Strip must be too long for this test");

    led_strip_t strip;
    led_strip_length_ExpectAndReturn(&strip, l);
    led_strip_write_all_IgnoreAndReturn(ERROR_NONE);

    array_cart_snake_t array;
    color_t buf[x * y];
    TEST_ASSERT_EQUAL(
        ERROR_NONE,
        array_cart_snake_init(&array, &strip, x, y, buf)
    );
}

void test_array_cart_snake_init_detects_null_handle(void) {
    led_strip_t strip;
    color_t buf[3 * 4];
    TEST_ASSERT_EQUAL(
        ERROR_PARAM,
        array_cart_snake_init(NULL, &strip, 3, 4, buf)
    );
}

void test_array_cart_snake_init_detects_null_strip(void) {
    array_cart_snake_t array;
    color_t buf[3 * 4];
    TEST_ASSERT_EQUAL(
        ERROR_PARAM,
        array_cart_snake_init(&array, NULL, 3, 4, buf)
    );
}

void test_array_cart_snake_init_detects_null_buf(void) {
    array_cart_snake_t array;
    led_strip_t strip;
    TEST_ASSERT_EQUAL(
        ERROR_PARAM,
        array_cart_snake_init(&array, &strip, 3, 4, NULL)
    );
}

void test_array_cart_snake_init_detects_invalid_x(void) {
    array_cart_snake_t array;
    led_strip_t strip;
    color_t buf[3 * 4];
    TEST_ASSERT_EQUAL(
        ERROR_PARAM,
        array_cart_snake_init(&array, &strip, 0, 4, buf)
    );
}

void test_array_cart_snake_init_detects_invalid_y(void) {
    array_cart_snake_t array;
    led_strip_t strip;
    color_t buf[3 * 4];
    TEST_ASSERT_EQUAL(
        ERROR_PARAM,
        array_cart_snake_init(&array, &strip, 3, 0, buf)
    );
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

/// @} defgroup ARRAY_CART_SNAKE_TEST
/// @} addtogroup ARRAY_CART_SNAKE
