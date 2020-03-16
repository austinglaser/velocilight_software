/**@file    ensure_c_exception.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EnsureCException Source
 *
 * @addtogroup ENSURE_C_EXCEPTION
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "ensure_c_exception.h"

#include "CException.h"
#include "util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

/** The file where an ensure failed */
static char const * _ensure_c_exception_file;

/** The line where an ensure failed */
static uint32_t _ensure_c_exception_line;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void ensure_c_exception(bool condition, char const * file, uint16_t line)
{
    UNUSED_VARIABLE(line);

    if (!condition) {
        _ensure_c_exception_file = file;
        _ensure_c_exception_line = line;
        Throw(ENSURE_FAILED);
    }
}

uint32_t ensure_c_exception_get_line(void)
{
    return _ensure_c_exception_line;
}

char const * ensure_c_exception_get_file(void)
{
    return _ensure_c_exception_file;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup ENSURE_C_EXCEPTION */
