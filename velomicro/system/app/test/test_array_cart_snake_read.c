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

// Source dependencies (to make Ceedling include the right objects)

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

void test_array_starts_all_black(void)
{
    static const color_t black = COLOR_RGB_INIT(0., 0., 0.);
    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            color_t color;

            TEST_ASSERT_EQUAL(ERROR_NONE, array_read(_array, x, y, &color));
            TEST_ASSERT_EQUAL_color_t(black, color);
        }
    }
}

TEST_VALUE(0, 0)
TEST_VALUE(1, 0)
TEST_VALUE(0, 1)
TEST_VALUE(X / 2, Y / 2)
TEST_VALUE(X - 1, Y - 2)
TEST_VALUE(X - 2, Y - 1)
TEST_VALUE(X - 1, Y - 1)
void test_array_cart_snake_read_gives_back_color(size_t x, size_t y) {
    led_strip_write_IgnoreAndReturn(ERROR_NONE);

    color_t first = COLOR_RGB_INIT(0.1, 0.2, 0.5);
    array_write(_array, x, y, first);

    color_t color;
    array_read(_array, x, y, &color);
    TEST_ASSERT_EQUAL_color_t(first, color);

    color_t second = COLOR_HSV_INIT(0.3, 1.0, 1.0);
    array_write(_array, x, y, second);

    array_read(_array, x, y, &color);
    TEST_ASSERT_EQUAL_color_t(second, color);
}

void test_array_cart_snake_read_holds_array_of_colors(void) {
    led_strip_write_IgnoreAndReturn(ERROR_NONE);

    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            color_t color = COLOR_RGB_INIT(
                (float) x/(float) X,
                (float) y/(float) Y,
                0.0
            );

            array_write(_array, x, y, color);
        }
    }

    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            color_t expected = COLOR_RGB_INIT(
                (float) x/(float) X,
                (float) y/(float) Y,
                0.0
            );

            color_t color;
            TEST_ASSERT_EQUAL(ERROR_NONE, array_read(_array, x, y, &color));
            TEST_ASSERT_EQUAL_color_t(expected, color);
        }
    }
}

TEST_VALUE(X, 0)
TEST_VALUE(X, Y - 1)
TEST_VALUE(0, Y)
TEST_VALUE(X - 1, Y)
TEST_VALUE(X , Y)
TEST_VALUE(0xFFFFFFFF, 0)
TEST_VALUE(0, 0xFFFFFFFF)
TEST_VALUE(0xFFFFFFFF, 0xFFFFFFFF)
void test_array_cart_snake_read_detects_invalid_coordinates(size_t x, size_t y) {
    color_t color;
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_read(_array, x, y, &color));
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

/// @} defgroup ARRAY_CART_SNAKE_TEST
/// @} addtogroup ARRAY_CART_SNAKE
