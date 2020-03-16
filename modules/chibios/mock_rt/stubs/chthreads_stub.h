/**@file    chthreads_stub.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   ChthreadsStub Interface
 */

#ifndef CHTHREADS_STUB_H
#define CHTHREADS_STUB_H

/**@defgroup CHTHREADS_STUB ChthreadsStub
 * @{
 *
 * Useful stubs for dealing with chthreads functions
 *
 * @note    Implemented as-needed
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "ch.h"
#include "chthreads.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** Structure storing all arguments to chThdCreateStatic */
struct _chThdCreateStatic_args {
    void * wsp;         /**< Pointer to working area */
    size_t size;        /**< Working area size */
    tprio_t prio;       /**< Thread priority */
    tfunc_t pf;         /**< Thread function pointer */
    void * arg;         /**< Argument to be passed to the thread */
};

typedef struct _chThdCreateStatic_args chThdCreateStatic_args_t;

/** Structure storing all arguments to chThdCreateI */
struct _chThdCreateI_args {
    void * wsp;         /**< Pointer to working area */
    size_t size;        /**< Working area size */
    tprio_t prio;       /**< Thread priority */
    tfunc_t pf;         /**< Thread function pointer */
    void * arg;         /**< Argument to be passed to the thread */
};

typedef struct _chThdCreateI_args chThdCreateI_args_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Resets all metrics and stored data */
void chthreads_stubs_reset(void);

/** Retrieves the number of calls made to @ref chThdCreateStatic
 *
 * @return  The total number of times a stubbed chThdCreateStatic function has
 *          been called
 */
uint32_t chThdCreateStatic_stub_calls(void);

/** Retrieves the values of arguments passed to @ref chThdCreateStatic
 *
 * @return  A pointer to an argument structure
 */
chThdCreateStatic_args_t const * chThdCreateStatic_stub_args(void);

/** Provides a value for chThdCreateStatic_stub to return
 *
 * @param[in] tp:   The thread pointer to return
 */
void chThdCreateStatic_return(thread_t * tp);

/** Saves the values of arguments into a static structure.
 *
 * Argument values can be retrieved through @ref chThdCreateStatic_stub_args
 *
 * Increments the value returned by @ref chThdCreateStatic_stub_calls
 *
 * @return  The value passed to @ref chThdCreateStatic_return
 */
thread_t *chThdCreateStatic_stub(void *wsp, size_t size,
                                 tprio_t prio, tfunc_t pf, void *arg,
                                 int num_prev_calls);

/** Retrieves the number of calls made to @ref chThdCreateI
 *
 * @return  The total number of times a stubbed chThdCreateI function has
 *          been called
 */
uint32_t chThdCreateI_stub_calls(void);

/** Retrieves the values of arguments passed to @ref chThdCreateI
 *
 * @return  A pointer to an argument structure
 */
chThdCreateI_args_t const * chThdCreateI_stub_args(void);

/** Provides a value for chThdCreateI_stub to return
 *
 * @param[in] tp:   The thread pointer to return
 */
void chThdCreateI_return(thread_t * tp);

/** Saves the values of arguments into a static structure.
 *
 * Argument values can be retrieved through @ref chThdCreateI_stub_args
 *
 * Increments the value returned by @ref chThdCreateI_stub_calls
 *
 * @return  The value passed to @ref chThdCreateI_return
 */
thread_t *chThdCreateI_stub(void *wsp, size_t size,
                            tprio_t prio, tfunc_t pf, void *arg,
                            int num_prev_calls);

/** @} defgroup CHTHREADS_STUB */

#endif /* ifndef CHTHREADS_STUB_H */
