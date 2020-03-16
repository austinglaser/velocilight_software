/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   Array Source
///
/// @addtogroup ARRAY
/// @{
///
/// @defgroup ARRAY_PRIVATE Array Private Members
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// This module
#include "array.h"

// Supporting modules

// Third-party headers

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

err_t array_write(array_t * array, size_t alpha, size_t beta, color_t color) {
    if (array == NULL || array->vmt == NULL) {
        return ERROR_PARAM;
    }

    if (array->vmt->write == NULL) {
        return ERROR_NOENT;
    }

    return array->vmt->write(array, alpha, beta, color);
}

err_t array_write_all(array_t * array, color_t color) {
    if (array == NULL || array->vmt == NULL) {
        return ERROR_PARAM;
    }

    if (array->vmt->write_all == NULL) {
        return ERROR_NOENT;
    }

    return array->vmt->write_all(array, color);
}

err_t array_read(
    array_t const * array,
    size_t alpha,
    size_t beta,
    color_t * color
) {
    if (array == NULL || array->vmt == NULL) {
        return ERROR_PARAM;
    }

    if (array->vmt->read == NULL) {
        return ERROR_NOENT;
    }

    return array->vmt->read(array, alpha, beta, color);
}

err_t array_show(array_t const * array) {
    if (array == NULL || array->vmt == NULL) {
        return ERROR_PARAM;
    }

    if (array->vmt->show == NULL) {
        return ERROR_NOENT;
    }

    return array->vmt->show(array);
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

/// @} defgroup ARRAY_PRIVATE
/// @} addtogroup ARRAY
