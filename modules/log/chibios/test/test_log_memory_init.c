/**@file    test_log_memory_init.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Log Memory initialization tests
 *
 * @addtogroup TEST_LOG_MEMORY_INIT
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_memory.h"
#include "log_memory_implementation.h"
#include "unity.h"

#include "CException.h"
#include "ensure.h"
#include "ensure_c_exception.h"

#include "ch.h"
#include "chthreads_stub.h"
#include "chsys_stub.h"

#include "mock_chthreads.h"
#include "mock_chsys.h"
#include "mock_chmboxes.h"
#include "mock_log_memory_eeprom.h"
#include "mock_memory_pool.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Expects that calling log_memory_init with the provided arguments will
 * result in an ensure exception
 */
void assert_log_memory_init_fails_ensure_with(log_memory_t * lm,
                                              eeprom_t * eeprom,
                                              mem_pool_t * mp,
                                              project_info_t * pi);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static log_memory_t log_memory;
static thread_t log_memory_thread;
static eeprom_t dummy_eeprom;
static mem_pool_t dummy_mempool;
static project_info_t dummy_project_info;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Forward declaration of memory access thread */
void _log_memory_thread_f(void * arg);

void setUp(void)
{
    chthreads_stubs_reset();

    chSysLock_StubWithCallback(chSysLock_stub_do_lock);
    chSysUnlock_StubWithCallback(chSysUnlock_stub_do_unlock);
    chThdCreateI_StubWithCallback(chThdCreateI_stub);
    chThdCreateI_return(&log_memory_thread);
}

/* --- TESTS ---------------------------------------------------------------- */

void test_log_memory_init_should_initialize_queue(void)
{
    chThdStart_IgnoreAndReturn(&log_memory_thread);

    chMBObjectInit_Expect(&(log_memory.mbox),
                          log_memory.mbox_buf,
                          LOG_MEMORY_MBOX_SIZE);

    log_memory_init(&log_memory,
                    &dummy_eeprom,
                    &dummy_mempool,
                    &dummy_project_info);
}

void test_log_memory_init_should_start_internal_thread(void)
{
    chMBObjectInit_Ignore();
    chThdStart_ExpectAndReturn(&log_memory_thread, &log_memory_thread);

    int err = log_memory_init(&log_memory,
                              &dummy_eeprom,
                              &dummy_mempool,
                              &dummy_project_info);
    TEST_ASSERT_EQUAL(0, err);

    TEST_ASSERT_EQUAL_UINT32(1, chThdCreateI_stub_calls());

    chThdCreateI_args_t const * args = chThdCreateI_stub_args();

    TEST_ASSERT_EQUAL_PTR(_log_memory_thread_f, args->pf);
}

void test_log_memory_init_should_provide_working_area(void)
{
    chMBObjectInit_Ignore();
    chThdStart_ExpectAndReturn(&log_memory_thread, &log_memory_thread);

    int err = log_memory_init(&log_memory,
                              &dummy_eeprom,
                              &dummy_mempool,
                              &dummy_project_info);
    TEST_ASSERT_EQUAL(0, err);

    TEST_ASSERT_EQUAL_UINT32(1, chThdCreateI_stub_calls());

    chThdCreateI_args_t const * args = chThdCreateI_stub_args();

    TEST_ASSERT_NOT_NULL(args->wsp);

    TEST_ASSERT_MESSAGE(args->size >= 256,
                        "Working area must be big enough for stacked values");
}

void test_log_memory_init_should_start_low_priority_thread(void)
{
    chMBObjectInit_Ignore();
    chThdStart_ExpectAndReturn(&log_memory_thread, &log_memory_thread);

    int err = log_memory_init(&log_memory,
                              &dummy_eeprom,
                              &dummy_mempool,
                              &dummy_project_info);
    TEST_ASSERT_EQUAL(0, err);

    TEST_ASSERT_EQUAL_UINT32(1, chThdCreateI_stub_calls());

    chThdCreateI_args_t const * args = chThdCreateI_stub_args();

    TEST_ASSERT_EQUAL(args->prio, LOWPRIO);
}

void test_log_memory_init_should_pass_log_memory_instance_to_thread(void)
{
    chMBObjectInit_Ignore();
    chThdStart_ExpectAndReturn(&log_memory_thread, &log_memory_thread);

    int err = log_memory_init(&log_memory,
                              &dummy_eeprom,
                              &dummy_mempool,
                              &dummy_project_info);
    TEST_ASSERT_EQUAL(0, err);

    TEST_ASSERT_EQUAL_UINT32(1, chThdCreateI_stub_calls());

    chThdCreateI_args_t const * args = chThdCreateI_stub_args();

    log_memory_t * lm = args->arg;

    TEST_ASSERT_NOT_NULL(lm);
    TEST_ASSERT_EQUAL_PTR(&dummy_eeprom,        lm->e);
    TEST_ASSERT_EQUAL_PTR(&dummy_mempool,       lm->mp);
    TEST_ASSERT_EQUAL_PTR(&dummy_project_info,  lm->pi);
    TEST_ASSERT_EQUAL_PTR(&log_memory_thread,   lm->thread);
}

void test_log_memory_init_should_detect_null_pointers(void)
{
    assert_log_memory_init_fails_ensure_with(NULL,
                                             &dummy_eeprom,
                                             &dummy_mempool,
                                             &dummy_project_info);
    assert_log_memory_init_fails_ensure_with(&log_memory,
                                             NULL,
                                             &dummy_mempool,
                                             &dummy_project_info);
    assert_log_memory_init_fails_ensure_with(&log_memory,
                                             &dummy_eeprom,
                                             NULL,
                                             &dummy_project_info);
    assert_log_memory_init_fails_ensure_with(&log_memory,
                                             &dummy_eeprom,
                                             &dummy_mempool,
                                             NULL);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

void assert_log_memory_init_fails_ensure_with(log_memory_t * lm,
                                              eeprom_t * eeprom,
                                              mem_pool_t * mp,
                                              project_info_t * pi)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;

    Try {
        log_memory_init(lm, eeprom, mp, pi);
    }
    Catch (e) {
        TEST_ASSERT_EQUAL_HEX32(ENSURE_FAILED, e);
        return;
    }

    TEST_FAIL_MESSAGE("No ensure exception thrown");
}

/** @} addtogroup TEST_LOG_MEMORY_INIT */
