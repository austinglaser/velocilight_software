/**@file    log_memory_stub.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogMemoryStub Source
 *
 * @addtogroup LOG_MEMORY_STUB
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_memory_stub.h"

#include "log_memory.h"
#include "memory_pool.h"
#include "unity.h"
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

/** The number of times a stubbed log_memory_init function has been called */
static uint32_t _log_memory_stub_init_calls;

/** Memory pool captured by @ref _log_memory_init_capture_mp() */
static log_memory_init_args_t _log_memory_stub_init_args;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void log_memory_stub_reset(void)
{
    _log_memory_stub_init_calls = 0;
    memset(&_log_memory_stub_init_args, 0, sizeof(_log_memory_stub_init_args));
}

uint32_t log_memory_stub_init_calls(void)
{
    return _log_memory_stub_init_calls;
}

log_memory_init_args_t const * log_memory_stub_init_args(void)
{
    return &_log_memory_stub_init_args;
}

int log_memory_stub_init(log_memory_t * lm,
                         eeprom_t * e,
                         mem_pool_t * mp,
                         project_info_t const * pi,
                         int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    TEST_ASSERT_NOT_NULL_MESSAGE(lm, "log-memory must be non-NULL");
    TEST_ASSERT_NOT_NULL_MESSAGE(e, "eeprom must be non-NULL");
    TEST_ASSERT_NOT_NULL_MESSAGE(mp, "memory pool must be non-NULL");

    _log_memory_stub_init_calls += 1;

    _log_memory_stub_init_args.lm = lm;
    _log_memory_stub_init_args.e  = e;
    _log_memory_stub_init_args.mp = mp;
    _log_memory_stub_init_args.pi = pi;

    return 0;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup LOG_MEMORY_STUB */
