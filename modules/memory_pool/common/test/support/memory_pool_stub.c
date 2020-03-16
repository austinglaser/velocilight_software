/**@file    memory_pool_stub.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   MemoryPoolStub Source
 *
 * @addtogroup MEMORY_POOL_STUB
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "memory_pool_stub.h"

#include "memory_pool.h"
#include "unity.h"
#include "util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

/** The number of times a stubbed memory_pool_init function has been called */
static uint32_t _memory_pool_stub_init_calls;

/** Memory pool captured by @ref _memory_pool_init_capture_mp() */
static memory_pool_init_args_t _memory_pool_stub_init_args;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void memory_pool_stub_reset(void)
{
    _memory_pool_stub_init_calls = 0;
    memset(&_memory_pool_stub_init_args, 0, sizeof(_memory_pool_stub_init_args));
}

uint32_t memory_pool_stub_init_calls(void)
{
    return _memory_pool_stub_init_calls;
}

memory_pool_init_args_t const * memory_pool_stub_init_args(void)
{
    return &_memory_pool_stub_init_args;
}

void memory_pool_stub_init(mem_pool_t * mp,
                           void * objs,
                           size_t obj_n,
                           size_t obj_size,
                           int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    TEST_ASSERT_NOT_NULL(mp);
    TEST_ASSERT_NOT_NULL(objs);
    TEST_ASSERT_MESSAGE(obj_n >= 1,
                        "memory_pool_init called with zero objects");
    TEST_ASSERT_MESSAGE(obj_size >= 1,
                        "memory_pool_init called with zero-size objects");

    _memory_pool_stub_init_args.mp       = mp;
    _memory_pool_stub_init_args.objs     = objs;
    _memory_pool_stub_init_args.obj_n    = obj_n;
    _memory_pool_stub_init_args.obj_size = obj_size;

    _memory_pool_stub_init_calls += 1;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup MEMORY_POOL_STUB */
