/**@file    memory_pool_stub.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   MemoryPoolStub Interface
 */

#ifndef MEMORY_POOL_STUB_H
#define MEMORY_POOL_STUB_H

/**@defgroup MEMORY_POOL_STUB MemoryPoolStub
 * @{
 *
 * Stubs useful along with a mocked version of memory_pool
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "memory_pool.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** Structure holding all arguments to memory_pool_init */
struct _memory_pool_init_args {
    mem_pool_t * mp;        /**< Memory pool pointer */
    void * objs;            /**< Raw memory for allocation */
    size_t obj_n;           /**< Number of objects in pool */
    size_t obj_size;        /**< Size of objects in pool */
};

typedef struct _memory_pool_init_args memory_pool_init_args_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Reset persistent data stored by this module */
void memory_pool_stub_reset(void);

/** Retrieve the total number of calls made to memory_pool_stub_init_*
 * functions
 *
 * Reset by @ref memory_pool_stub_reset()
 *
 * @see memory_pool_stub_init
 *
 * @return  The total number of calls
 */
uint32_t memory_pool_stub_init_calls(void);

/** Retrieve the value of all arguments passed to memory_pool_stub_init()
 *
 * @see memory_pool_stub_init
 *
 * @return  A structure holding all arguments to @ref memory_pool_init()
 */
memory_pool_init_args_t const * memory_pool_stub_init_args(void);

/** Verify that all arguments passed to memory_pool_init() are valid, and save
 * them for later retrieval
 *
 * Increments the value returned by @ref memory_pool_stub_init_calls()
 *
 * @param[in] mp:               A memory pool pointer
 * @param[in] objs:             object buffer
 * @param[in] obj_n:            number of objects in @p objs
 * @param[in] obj_size:         size of objects in @p objs
 * @param[in] num_prev_calls:   Unused
 */
void memory_pool_stub_init(mem_pool_t * mp,
                           void * objs,
                           size_t obj_n,
                           size_t obj_size,
                           int num_prev_calls);

/** @} defgroup MEMORY_POOL_STUB */

#endif /* ifndef MEMORY_POOL_STUB_H */
