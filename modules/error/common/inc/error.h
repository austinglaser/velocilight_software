/**@file    error.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Error Interface
 */

#ifndef ERROR_H
#define ERROR_H

/**@defgroup ERROR Error
 * @{
 *
 * @brief Common error codes
 *
 * Provides common datatype and values for error return codes.
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */

/** Datatype for error return values */
typedef enum {
    ERROR_NONE    = 0,      /**< No error */
    ERROR_GENERIC = -1,     /**< An unspecified error */
    ERROR_COMM    = -2,     /**< An error on a communication interface */
    ERROR_PARAM   = -3,     /**< A function parameter was invalid */
    ERROR_HW      = -4,     /**< Hardware experienced an error */
    ERROR_TIMEOUT = -5,     /**< A timeout occurred */
    ERROR_NOMEM   = -6,     /**< Not enough memory available */
    ERROR_NOENT   = -7,     /**< Object does not exist or is not available */
} err_t;

/* --- PUBLIC MACROS ------------------------------------------------------- */

/** Short-circuit OR for @ref err_t
 *
 * If @p origerr is not ERROR_NONE, it is returned. Otherwise, @p newerr is.
 *
 * The most common use case is to propogate error values across several
 * function calls without explicitly checking the error after each one. It's
 * especially useful when several possibly error returning functions should be
 * executed, an error from any of them detected, and the earliest error
 * reported.
 *
 * Uses short-circuit operation -- that is, if @p newerr is an expression and
 * @p origerr evaluates to an error, @p newerr is never evaluated.
 *
 * For instance:
 * \verbatim
    err_t err;
    err = func1();
    err = ERROR_OR(err, func2());
    err = ERROR_OR(err, func3());
    if (err != ERROR_NONE) {
        return err;
    }
\endverbatim
 *
 * @note This is *very* nearly the same thing as `origerr || newerr`. The
 *       *only* difference is that the `||` operator evaluates to a `bool`, so
 *       the error value is lost.
 *
 * @param[in] origerr:      The original error value to preserve
 * @param[in] newerr:       A possible new error value
 *
 * @return      @p origerr if it was an error, otherwise @p newerr
 */
#define ERROR_OR(origerr, newerr)             \
    ({                                        \
        err_t __error_or_origerr = (origerr); \
        (__error_or_origerr != ERROR_NONE)    \
                ? __error_or_origerr          \
                : (newerr);                   \
    })

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** @} defgroup ERROR */

#endif /* ifndef ERROR_H */
