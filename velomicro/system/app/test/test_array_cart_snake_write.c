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
#include "array.h"

// Mocks, fakes, test support
#include "mock_led_strip.h"
#include "unity_color_helper.h"
#include "unity_util.h"

// Source dependencies (present only to make Ceedling include the right
// objects)

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //

#define X       4
#define Y       5

// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //
// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //

static array_cart_snake_t _array_cart;

static color_t _buf[X * Y];
led_strip_t _strip;

array_t * _array = (array_t *) &_array_cart;

// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

void setUp(void) {
    led_strip_length_ExpectAndReturn(&_strip, X * Y);
    led_strip_write_all_ExpectAndReturn(
        &_strip,
        (color_t) COLOR_RGB_INIT(0., 0., 0.),

        ERROR_NONE
    );

    array_cart_snake_init(&_array_cart, &_strip, X, Y, _buf);
}

// --- PUBLIC TESTS -------------------------------------------------------- //

TEST_VALUE(0, 0, 0)
TEST_VALUE(1, 0, 1)
TEST_VALUE(2, 0, 2)
TEST_VALUE(3, 0, 3)
TEST_VALUE(0, 1, 7)
TEST_VALUE(1, 1, 6)
TEST_VALUE(2, 1, 5)
TEST_VALUE(3, 1, 4)
TEST_VALUE(0, 2, 8)
TEST_VALUE(1, 2, 9)
TEST_VALUE(2, 2, 10)
TEST_VALUE(3, 2, 11)
TEST_VALUE(0, 3, 15)
TEST_VALUE(1, 3, 14)
TEST_VALUE(2, 3, 13)
TEST_VALUE(3, 3, 12)
TEST_VALUE(0, 4, 16)
TEST_VALUE(1, 4, 17)
TEST_VALUE(2, 4, 18)
TEST_VALUE(3, 4, 19)
void test_array_write_maps_valid_coordinate(size_t x, size_t y, size_t led) {
    color_t color = COLOR_HSV_INIT(0.1, 0.2, 0.0);
    led_strip_write_ExpectAndReturn(&_strip, led, color, ERROR_NONE);

    TEST_ASSERT_EQUAL(ERROR_NONE, array_write(_array, x, y, color));
}

TEST_VALUE(X, 0)
TEST_VALUE(X, Y - 1)
TEST_VALUE(0, Y)
TEST_VALUE(X - 1, Y)
TEST_VALUE(X , Y)
TEST_VALUE(0xFFFFFFFF, 0)
TEST_VALUE(0, 0xFFFFFFFF)
TEST_VALUE(0xFFFFFFFF, 0xFFFFFFFF)
void test_array_write_detects_invalid_coordinates(size_t x, size_t y) {
    color_t color = COLOR_HSL_INIT(1.0, 1.0, 0.5);
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_write(_array, x, y, color));
}

TEST_VALUE(ERROR_PARAM)
TEST_VALUE(ERROR_COMM)
TEST_VALUE(ERROR_HW)
void test_array_write_detects_strip_failure(int err) {
    led_strip_write_IgnoreAndReturn(err);

    color_t color = COLOR_RGB_INIT(1.0, 1.0, 0.5);
    TEST_ASSERT_EQUAL(err, array_write(_array, 0, 0, color));
}

TEST_VALUE(0, 0)
TEST_VALUE(1, 0)
TEST_VALUE(0, 1)
TEST_VALUE(X / 2, Y / 2)
TEST_VALUE(X - 1, Y - 2)
TEST_VALUE(X - 2, Y - 1)
TEST_VALUE(X - 1, Y - 1)
void test_array_write_leaves_array_after_write_failure(size_t x, size_t y) {
    color_t first = COLOR_HSV_INIT(0.9, 0.1, 1.0);
    color_t second = COLOR_HSL_INIT(0.5, 0.5, 0.5);

    led_strip_write_IgnoreAndReturn(ERROR_NONE);
    array_write(_array, x, y, first);

    led_strip_write_IgnoreAndReturn(ERROR_GENERIC);
    array_write(_array, x, y, second);

    color_t color;
    array_read(_array, x, y, &color);
    TEST_ASSERT_EQUAL_color_t(first, color);
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

/// @} defgroup ARRAY_CART_SNAKE_TEST
/// @} addtogroup ARRAY_CART_SNAKE
