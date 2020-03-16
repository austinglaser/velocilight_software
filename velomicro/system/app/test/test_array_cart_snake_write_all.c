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

void test_array_cart_snake_write_all_writes_all(void) {
    color_t color = COLOR_RGB_INIT(1.0, 0.5, 0.2);
    led_strip_write_all_ExpectAndReturn(&_strip, color, ERROR_NONE);

    TEST_ASSERT_EQUAL(ERROR_NONE, array_write_all(_array, color));
}

void test_can_read_back_colors_after_write_all(void) {
    led_strip_write_all_IgnoreAndReturn(ERROR_NONE);

    color_t color = COLOR_HSL_INIT(0.9, 0.1, 1.0);
    array_write_all(_array, color);

    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            color_t read;
            array_read(_array, x, y, &read);
            TEST_ASSERT_EQUAL_color_t(color, read);
        }
    }
}

TEST_VALUE(ERROR_PARAM)
TEST_VALUE(ERROR_COMM)
TEST_VALUE(ERROR_HW)
void test_array_cart_snake_write_all_detects_write_failure(int err) {
    led_strip_write_all_IgnoreAndReturn(err);

    color_t color = COLOR_RGB_INIT(1.0, 0.5, 0.2);
    TEST_ASSERT_EQUAL(err, array_write_all(_array, color));
}

TEST_VALUE(ERROR_PARAM)
TEST_VALUE(ERROR_COMM)
TEST_VALUE(ERROR_HW)
void test_array_unmodified_after_write_failure(int err) {
    color_t first = COLOR_HSL_INIT(0.9, 0.1, 1.0);
    color_t second = COLOR_RGB_INIT(0.5, 0.5, 0.5);

    led_strip_write_all_IgnoreAndReturn(ERROR_NONE);
    array_write_all(_array, first);

    led_strip_write_all_IgnoreAndReturn(err);
    array_write_all(_array, second);

    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            color_t read;
            array_read(_array, x, y, &read);
            TEST_ASSERT_EQUAL_color_t(first, read);
        }
    }
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

/// @} defgroup ARRAY_CART_SNAKE_TEST
/// @} addtogroup ARRAY_CART_SNAKE
