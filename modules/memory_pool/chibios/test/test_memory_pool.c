/**@file    test_memory_pool.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestMemoryPool Source
 *
 * @addtogroup TEST_MEMORY_POOL
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "memory_pool.h"
#include "memory_pool_implementation.h"
#include "unity.h"

#include "ch.h"
#include "mock_chmempools.h"
#include "mock_chsys.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

#define MP_OBJ_LEN      32  /**< Length of objects managed by pool */
#define MP_N_OBJS       5   /**< Total number of objects managed by pool */

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

/** Memory pool for tests */
static mem_pool_t mp;

/** Memory doled out by the pool */
static uint8_t raw_pool[MP_OBJ_LEN * MP_N_OBJS];

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */
/* --- TESTS ---------------------------------------------------------------- */

void test_memory_pool_init_initializes_object(void)
{
    chPoolObjectInit_Expect(&mp, MP_OBJ_LEN, NULL);

    chPoolLoadArray_Ignore();

    memory_pool_init(&mp, raw_pool, MP_N_OBJS, MP_OBJ_LEN);
}

void test_memory_pool_init_loads_initial_array(void)
{
    chPoolLoadArray_Expect(&mp, raw_pool, MP_N_OBJS);

    chPoolObjectInit_Ignore();

    memory_pool_init(&mp, raw_pool, MP_N_OBJS, MP_OBJ_LEN);
}

void test_memory_pool_alloc_should_get_buffer_from_chibios(void)
{
    void * allocated_buffer;
    syssts_t status;

    status = 0;
    allocated_buffer = (void *) 0xDEADBEEF;

    chSysGetStatusAndLockX_ExpectAndReturn(status);
    chPoolAllocI_ExpectAndReturn(&mp, allocated_buffer);
    chSysRestoreStatusX_Expect(status);

    TEST_ASSERT_EQUAL_PTR(allocated_buffer, memory_pool_alloc(&mp));

    status = 1;
    allocated_buffer = (void *) 0xCAFEBABE;

    chSysGetStatusAndLockX_ExpectAndReturn(status);
    chPoolAllocI_ExpectAndReturn(&mp, allocated_buffer);
    chSysRestoreStatusX_Expect(status);
    TEST_ASSERT_EQUAL_PTR(allocated_buffer, memory_pool_alloc(&mp));

    status = 2;
    allocated_buffer = NULL;

    chSysGetStatusAndLockX_ExpectAndReturn(status);
    chPoolAllocI_ExpectAndReturn(&mp, allocated_buffer);
    chSysRestoreStatusX_Expect(status);

    TEST_ASSERT_EQUAL_PTR(allocated_buffer, memory_pool_alloc(&mp));
}

void test_memory_pool_free_should_return_buffer_to_chibios(void)
{
    uint8_t buffer_for_freeing[MP_OBJ_LEN];
    syssts_t status;

    status = 1;
    chSysGetStatusAndLockX_ExpectAndReturn(status);
    chPoolFreeI_Expect(&mp, buffer_for_freeing);
    chSysRestoreStatusX_Expect(status);

    memory_pool_free(&mp, buffer_for_freeing);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_MEMORY_POOL */
