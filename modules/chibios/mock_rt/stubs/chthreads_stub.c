/**@file    chthreads_stub.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   ChthreadsStub Source
 *
 * @addtogroup CHTHREADS_STUB
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "chthreads_stub.h"

#include "unity.h"
#include "chsys_stub.h"

#include "ch.h"
#include "chthreads.h"
#include "util.h"

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

/** Number of calls to chThdCreateStatic_stub */
static uint32_t _chThdCreateStatic_stub_calls;

/** Arguments passed to chThdCreateStatic_stub */
static chThdCreateStatic_args_t _chThdCreateStatic_stub_args;

/** Value for chThdCreateStatic_stub to return */
static thread_t * _chThdCreateStatic_stub_return_value;

/** Number of calls to chThdCreateI_stub */
static uint32_t _chThdCreateI_stub_calls;

/** Arguments passed to chThdCreateI_stub */
static chThdCreateI_args_t _chThdCreateI_stub_args;

/** Value for chThdCreateI_stub to return */
static thread_t * _chThdCreateI_stub_return_value;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void chthreads_stubs_reset(void)
{
    _chThdCreateStatic_stub_calls = 0;
    memset(&_chThdCreateStatic_stub_args, 0, sizeof(_chThdCreateStatic_stub_args));
    _chThdCreateStatic_stub_return_value = NULL;

    _chThdCreateI_stub_calls = 0;
    memset(&_chThdCreateI_stub_args, 0, sizeof(_chThdCreateI_stub_args));
    _chThdCreateI_stub_return_value = NULL;
}

uint32_t chThdCreateStatic_stub_calls(void)
{
    return _chThdCreateStatic_stub_calls;
}

chThdCreateStatic_args_t const * chThdCreateStatic_stub_args(void)
{
    return &_chThdCreateStatic_stub_args;
}

void chThdCreateStatic_return(thread_t * tp)
{
    _chThdCreateStatic_stub_return_value = tp;
}

thread_t *chThdCreateStatic_stub(void *wsp, size_t size,
                                 tprio_t prio, tfunc_t pf, void *arg,
                                 int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    _chThdCreateStatic_stub_args.wsp  = wsp;
    _chThdCreateStatic_stub_args.size = size;
    _chThdCreateStatic_stub_args.prio = prio;
    _chThdCreateStatic_stub_args.pf   = pf;
    _chThdCreateStatic_stub_args.arg  = arg;

    _chThdCreateStatic_stub_calls += 1;

    return _chThdCreateStatic_stub_return_value;
}

uint32_t chThdCreateI_stub_calls(void)
{
    return _chThdCreateI_stub_calls;
}

chThdCreateI_args_t const * chThdCreateI_stub_args(void)
{
    return &_chThdCreateI_stub_args;
}

void chThdCreateI_return(thread_t * tp)
{
    _chThdCreateI_stub_return_value = tp;
}

thread_t *chThdCreateI_stub(void *wsp, size_t size,
                                 tprio_t prio, tfunc_t pf, void *arg,
                                 int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    TEST_ASSERT_MESSAGE(chsys_stub_is_locked(),
                        "Called outside lock zone");

    _chThdCreateI_stub_args.wsp  = wsp;
    _chThdCreateI_stub_args.size = size;
    _chThdCreateI_stub_args.prio = prio;
    _chThdCreateI_stub_args.pf   = pf;
    _chThdCreateI_stub_args.arg  = arg;

    _chThdCreateI_stub_calls += 1;

    return _chThdCreateI_stub_return_value;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup CHTHREADS_STUB */
