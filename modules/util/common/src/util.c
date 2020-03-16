/**@file    util.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Util Source
 *
 * @addtogroup UTIL
 * @{
 *
 * @defgroup UTIL_PRIVATE Util Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "util.h"

/* Supporting modules */
#include "error.h"

/* Third-party headers */

/* Standard headers */
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

err_t util_stoi(char const * str, int32_t * val, size_t base)
{
    /* Adapted from http://stackoverflow.com/a/19046736/4138486 */
    char * endptr = NULL;
    errno = 0;
    *val = strtol(str, &endptr, base);
    if (errno != 0 || endptr == str || *endptr != '\0') {
        return ERROR_PARAM;
    }

    return ERROR_NONE;
}

uint8_t util_min8(uint8_t a, uint8_t b)
{
    return (a < b) ? a : b;
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup UTIL_PRIVATE */
/** @} addtogroup UTIL */
