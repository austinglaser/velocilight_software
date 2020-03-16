/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   Array Interface

#ifndef ARRAY_H
#define ARRAY_H

/// @defgroup ARRAY Array
/// @{
///
/// An interface targetted at LED mappings to various coordinate spaces.

// --- PUBLIC DEPENDENCIES ------------------------------------------------- //

// Supporting modules
#include "color.h"
#include "error.h"

// Third-party headers

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PUBLIC CONSTANTS ---------------------------------------------------- //
// --- PUBLIC DATATYPES ---------------------------------------------------- //

/// Base methods for a array class
#define _array_methods                                                        \
    err_t (*write)(                                                           \
        array_t * array,                                                      \
        size_t alpha,                                                         \
        size_t beta,                                                          \
        color_t color                                                         \
    );                                                                        \
    err_t (*write_all)(array_t * array, color_t color);                       \
    err_t (*read)(                                                            \
        array_t const * array,                                                \
        size_t alpha,                                                         \
        size_t beta,                                                          \
        color_t * color                                                       \
    );                                                                        \
    err_t (*show)(array_t const * array);                                     \

/// Base data for a array class
#define _array_data

/// Base type for a array interface
typedef struct array {
    struct array_methods const * vmt;
    _array_data
} array_t;

struct array_methods {
    _array_methods
};

// --- PUBLIC MACROS ------------------------------------------------------- //
// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

/// Write a single LED.
///
/// The meaning of the coordinates is different depending on the array
/// type.
///
/// @param[in,out] array        Array to write
/// @param[in] alpha            The first coordinate (x, r, etc).
/// @param[in] beta             The second coordinate (y, theta, etc).
/// @param[in] color            Color to write.
///
/// @return An error if any of the parameters is invalid, or for an
/// implementation-defined reason.
err_t array_write(array_t * array, size_t alpha, size_t beta, color_t color);

/// Write all LEDs to a single color.
///
/// @param[in,out] array        Array to write
/// @param[in] color            Color to write.
///
/// @return An error if any of the parameters is invalid, or for an
/// implementation-defined reason.
err_t array_write_all(array_t * array, color_t color);

/// Read a single LED's color
///
/// @param[in array             Array to read
/// @param[in] alpha            The first coordinate (x, r, etc).
/// @param[in] beta             The second coordinate (y, theta, etc).
/// @param[out] color           Color at (@p alpha, @p beta).
///
/// @return An error if any of the parameters is invalid, or for an
/// implementation-defined reason.
err_t array_read(
    array_t const * array,
    size_t alpha,
    size_t beta,
    color_t * color
);

/// Push data to the physical array.
///
/// @param[in] array        Will be displayed
err_t array_show(array_t const * array);

/// @} defgroup ARRAY

#endif // ifndef ARRAY_H
