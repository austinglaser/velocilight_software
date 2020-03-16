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

void test_array_cart_snake_show_shows_strip(void) {
    led_strip_show_ExpectAndReturn(&_strip, ERROR_NONE);

    TEST_ASSERT_EQUAL(ERROR_NONE, array_show(_array));
}

TEST_VALUE(ERROR_PARAM)
TEST_VALUE(ERROR_COMM)
TEST_VALUE(ERROR_HW)
void test_array_cart_snake_show_detects_show_failure(int err) {
    led_strip_show_IgnoreAndReturn(err);

    TEST_ASSERT_EQUAL(err, array_show(_array));
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

/// @} defgroup ARRAY_CART_SNAKE_TEST
/// @} addtogroup ARRAY_CART_SNAKE
