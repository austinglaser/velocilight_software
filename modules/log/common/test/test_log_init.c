/**@file    test_log_init.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestLogInit Source
 *
 * @addtogroup TEST_LOG_INIT
 * @{
 *
 * Test list:
 *
 * [X] Initializes log serializer
 * [X] Initializes log memory
 * [X] Initializes memory pool
 * [x] Passes same memory pool to memory pool and log memory
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"
#include "log.h"

#include "eeprom.h"
#include "project_info.h"
#include "util.h"

#include "mock_log_memory.h"
#include "mock_log_serialize.h"
#include "mock_memory_pool.h"

#include "log_memory_stub.h"
#include "memory_pool_stub.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void setUp(void)
{
    log_memory_stub_reset();
    memory_pool_stub_reset();
}

/* --- TESTS ---------------------------------------------------------------- */

void test_log_init_initializes_log_serialize(void)
{
    memory_pool_init_Ignore();
    log_serialize_init_Expect();
    log_memory_init_IgnoreAndReturn(0);

    eeprom_t e;
    project_info_t pi;
    TEST_ASSERT_EQUAL(0, log_init(&e, &pi));
}

void test_log_init_initializes_log_memory(void)
{
    memory_pool_init_Ignore();
    log_serialize_init_Ignore();
    log_memory_init_StubWithCallback(log_memory_stub_init);

    eeprom_t e;
    project_info_t pi;
    TEST_ASSERT_EQUAL(0, log_init(&e, &pi));

    TEST_ASSERT_EQUAL_UINT32(1, log_memory_stub_init_calls());
}

void test_log_init_initializes_a_memory_pool(void)
{
    log_memory_init_IgnoreAndReturn(0);
    log_serialize_init_Ignore();
    memory_pool_init_StubWithCallback(memory_pool_stub_init);

    eeprom_t e;
    project_info_t pi;
    TEST_ASSERT_EQUAL(0, log_init(&e, &pi));

    TEST_ASSERT_EQUAL_UINT32(1, memory_pool_stub_init_calls());
}

void test_log_init_passes_same_pool_to_memory_pool_and_log_memory(void)
{
    memory_pool_init_StubWithCallback(memory_pool_stub_init);
    log_serialize_init_Ignore();
    log_memory_init_StubWithCallback(log_memory_stub_init);

    eeprom_t e;
    project_info_t pi;
    TEST_ASSERT_EQUAL(0, log_init(&e, &pi));

    TEST_ASSERT_EQUAL_UINT32(1, memory_pool_stub_init_calls());
    TEST_ASSERT_EQUAL_UINT32(1, log_memory_stub_init_calls());

    memory_pool_init_args_t const * mempool_args = memory_pool_stub_init_args();
    log_memory_init_args_t const * logmem_args = log_memory_stub_init_args();
    TEST_ASSERT_EQUAL_PTR(mempool_args->mp, logmem_args->mp);
}

void test_log_init_passes_e_to_log_memory(void)
{
    memory_pool_init_Ignore();
    log_serialize_init_Ignore();
    log_memory_init_StubWithCallback(log_memory_stub_init);

    eeprom_t e;
    project_info_t pi;
    TEST_ASSERT_EQUAL(0, log_init(&e, &pi));

    TEST_ASSERT_EQUAL_UINT32(1, log_memory_stub_init_calls());

    log_memory_init_args_t const * logmem_args = log_memory_stub_init_args();
    TEST_ASSERT_EQUAL_PTR(&e, logmem_args->e);
}

void test_log_init_passes_pi_to_log_memory(void)
{
    memory_pool_init_Ignore();
    log_serialize_init_Ignore();
    log_memory_init_StubWithCallback(log_memory_stub_init);

    eeprom_t e;
    project_info_t pi;
    TEST_ASSERT_EQUAL(0, log_init(&e, &pi));

    TEST_ASSERT_EQUAL_UINT32(1, log_memory_stub_init_calls());

    log_memory_init_args_t const * logmem_args = log_memory_stub_init_args();
    TEST_ASSERT_EQUAL_PTR(&pi, logmem_args->pi);
}

void test_log_init_fails_if_log_memory_init_fails(void)
{
    memory_pool_init_Ignore();
    log_serialize_init_Ignore();
    log_memory_init_ExpectAndReturn(NULL, NULL, NULL, NULL, -1);
    log_memory_init_IgnoreArg_lm();
    log_memory_init_IgnoreArg_e();
    log_memory_init_IgnoreArg_mp();
    log_memory_init_IgnoreArg_pi();

    TEST_ASSERT_MESSAGE(log_init(NULL, NULL) < 0,
                        "Initialization should fail when log_memory_init"
                        "fails");
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_LOG_INIT */
