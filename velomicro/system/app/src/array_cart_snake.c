/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   ArrayCartSnake Source
///
/// @addtogroup ARRAY_CART_SNAKE
/// @{
///
/// @defgroup ARRAY_CART_SNAKE_PRIVATE ArrayCartSnake Private Members
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// This module
#include "array_cart_snake.h"

// Supporting modules
#include "array.h"

// Third-party headers

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //
// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //

/// Implementation of @ref array_write for a snaked rectangle.
///
/// @param[in,out] array    Will be written to. Must actually be a pointer to
///                         @ref array_cart_snake_t
/// @param[in] x            X coordinate to write.
/// @param[in] y            Y coordinate to write.
/// @param[in] color        Color to write.
///
/// @return     An error code. If such a code is returned, no modification to
///             the array has occurred.
static err_t _array_cart_snake_write(
    array_t * array,
    size_t x,
    size_t y,
    color_t color
);

/// Implementation of @ref array_write_all for a snaked rectangle.
///
/// @param[in,out] array    Will be written to. Must actually be a pointer to
///                         @ref array_cart_snake_t
/// @param[in] color        Color to write.
///
/// @return     An error code. If such a code is returned, no modification to
///             the array has occurred.
static err_t _array_cart_snake_write_all(array_t * array, color_t color);

/// Implementation of @ref array_read for a snaked rectangle.
///
/// @param[in] array        Will be read from. Must actually be a pointer to
///                         @ref array_cart_snake_t
/// @param[in] x            X coordinate to read.
/// @param[in] y            Y coordinate to read.
/// @param[out] color       Color at (x, y)
///
/// @return     An error code. If such a code is returned, @p color has not
///             been set.
static err_t _array_cart_snake_read(
    array_t const * array,
    size_t x,
    size_t y,
    color_t * color
);

/// Implementation of @ref array_show for a snaked rectangle.
///
/// @param[in] array        Will be read from. Must actually be a pointer to
///                         @ref array_cart_snake_t
///
/// @return     An error code.
static err_t _array_cart_snake_show(array_t const * array);

/// Get the LED index for a 2D coordinate.
///
/// @note   Does not check that @p x and @p y are in-bounds
///
/// @param[in] array        Determines array size.
/// @param[in] x            X coordinate to map.
/// @param[in] y            Y coordinate to map.
///
/// @return     An index in the backing strip's array which will correspond to
///             (x, y).
static size_t _led_for_coords(
    array_cart_snake_t const * array,
    size_t x,
    size_t y
);

// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //

static const struct array_methods _array_cart_snake_methods = {
    .write = _array_cart_snake_write,
    .write_all = _array_cart_snake_write_all,
    .read = _array_cart_snake_read,
    .show = _array_cart_snake_show,
};

// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

err_t array_cart_snake_init(
    array_cart_snake_t * array,
    led_strip_t * strip,
    size_t x,
    size_t y,
    color_t * buf
) {
    if (array == NULL || strip == NULL || buf == NULL || x == 0 || y == 0) {
        return ERROR_PARAM;
    }

    if (led_strip_length(strip) < x * y) {
        return ERROR_NOMEM;
    }

    static const color_t black = COLOR_RGB_INIT(0., 0., 0.);

    err_t err = led_strip_write_all(strip, black);
    if (err != ERROR_NONE) {
        return err;
    }

    array->vmt = &_array_cart_snake_methods;

    array->strip = strip;
    array->x = x;
    array->y = y;
    array->array = buf;

    return ERROR_NONE;
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

static err_t _array_cart_snake_write(
    array_t * _array,
    size_t x,
    size_t y,
    color_t color
) {
    array_cart_snake_t * array = (array_cart_snake_t *) _array;

    if (x >= array->x || y >= array->y) {
        return ERROR_PARAM;
    }

    size_t led = _led_for_coords(array, x, y);
    err_t err = led_strip_write(array->strip, led, color);
    if (err != ERROR_NONE) {
        return err;
    }

    array->array[led] = color;

    return ERROR_NONE;
}

static err_t _array_cart_snake_write_all(array_t * _array, color_t color) {
    array_cart_snake_t * array = (array_cart_snake_t *) _array;

    err_t err = led_strip_write_all(array->strip, color);
    if (err != ERROR_NONE) {
        return err;
    }

    for (size_t i = 0; i < array->x * array->y; i++) {
        array->array[i] = color;
    }

    return ERROR_NONE;
}

static err_t _array_cart_snake_read(
    array_t const * _array,
    size_t x,
    size_t y,
    color_t * color
) {
    array_cart_snake_t * array = (array_cart_snake_t *) _array;

    if (x >= array->x || y >= array->y) {
        return ERROR_PARAM;
    }

    *color = array->array[_led_for_coords(array, x, y)];
    return ERROR_NONE;
}

static err_t _array_cart_snake_show(array_t const * _array) {
    array_cart_snake_t * array = (array_cart_snake_t *) _array;

    return led_strip_show(array->strip);
}

static size_t _led_for_coords(
    array_cart_snake_t const * array,
    size_t x,
    size_t y
) {
    if (y % 2 == 0) {
        return y * array->x + x;
    } else {
        return (y + 1) * array->x - (x + 1);
    }
}

/// @} defgroup ARRAY_CART_SNAKE_PRIVATE
/// @} addtogroup ARRAY_CART_SNAKE
