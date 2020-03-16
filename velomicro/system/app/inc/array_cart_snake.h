/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   ArrayCartSnake Interface

#ifndef ARRAY_CART_SNAKE_H
#define ARRAY_CART_SNAKE_H

/// @defgroup ARRAY_CART_SNAKE ArrayCartSnake
/// @{
///
/// @brief

// --- PUBLIC DEPENDENCIES ------------------------------------------------- //

// Supporting modules
#include "array.h"
#include "led_strip.h"

// Third-party headers

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PUBLIC CONSTANTS ---------------------------------------------------- //
// --- PUBLIC DATATYPES ---------------------------------------------------- //

/// Cartesian mapping on a snaked LED strip.
///
/// Compatible with the array interface.
///
/// The strips are assumed to be laid along the x-axis, with the led at (0,0)
/// being the first LED on the first strip.
///
/// Diagramatically, the mapping of a 4 x 3 array would look like:
///
/// @beginverbatim
///
///       +---------------+
///   2 +-> 8 | 9 | 10| 11|
///     | +---------------+
///     |
///     | +---------------+
///   1 +-+ 7 | 6 | 5 | 4 <-+
///       +---------------+ |
///                         |
///       +---------------+ |
///   0   | 0 | 1 | 2 | 3 +-+
///       +---------------+
///   y
///     x   0   1   2   3
///
/// @endverbatim
typedef struct {
    /// Method table.
    ///
    /// Required to be first for array_t compatibility
    struct array_methods const * vmt;

    /// Comon array data.
    _array_data

    /// Strip driver on which to map.
    led_strip_t * strip;

    /// X-dimension of array.
    ///
    /// In other words: The strip segment length.
    size_t x;

    /// Y-dimension of array.
    ///
    /// In other words: The total number of strips.
    size_t y;

    /// Backing array data.
    color_t * array;
} array_cart_snake_t;

// --- PUBLIC MACROS ------------------------------------------------------- //
// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

/// Initialize a cartesian mapping on an LED strip.
///
/// After initialization, all operations should be performed through the @ref
/// ARRAY interface.
///
/// The array will be initialized to be all black, as will the led strip
/// (though that initial all-black array will not be shown). This may lead to
/// redundant writes to the led_strip array buffer.
///
/// @param[out] array       Will be initialized
///
/// @param[in] strip        Used to display the array's data. Must have at
///                         least (@p x * @p y) elements.
///
///                         @p strip should already have been initialized.
///
/// @param[in] x            X dimension of LED matrix. Must be > 0
///
/// @param[in] y            Y dimension of LED matrix. Must be > 0
///
/// @param[in] buf          Used to store array data. A reference to @p buf is
///                         kept in @p array -- it should be considered owned
///                         by the array after this function is called.
///
///                         Must be at least @p x * @p y elements long
///
/// @retval ERROR_NONE      The array was successfully initialized
///
/// @retval ERROR_NOMEM     The provided LED strip was too short
///
/// @retval ERROR_PARAM     Some parameter was invalid -- either a NULL pointer
///                         was passed, or one of the dimensions was zero.
///
/// @retval another error   Clearing the strip failed.
err_t array_cart_snake_init(
    array_cart_snake_t * array,
    led_strip_t * strip,
    size_t x,
    size_t y,
    color_t * buf
);

/// @} defgroup ARRAY_CART_SNAKE

#endif // ifndef ARRAY_CART_SNAKE_H
