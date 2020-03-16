/**@file    unity_util.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   UnityUtil Source
 *
 * @addtogroup UNITY_UTIL
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity_util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

char * strncat_if_nonempty(char * out,
                           size_t out_len,
                           char const * first,
                           char const * second)
{
    out[0] = '\0';

    if (first != NULL && (strcmp(first, "") != 0)) {
        strncat(out, first, out_len - strlen(out) - 1);
        strncat(out, " ",  out_len - strlen(out) - 1);
    }

    strncat(out, second, out_len - strlen(out) - 1);
    strncat(out, ".",  out_len - strlen(out) - 1);

    return out;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup UNITY_UTIL */
