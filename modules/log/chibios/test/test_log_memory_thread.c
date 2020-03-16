/**@file    test_log_memory_thread.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestLogMemoryThread Source
 *
 * @addtogroup TEST_LOG_MEMORY_THREAD
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_memory.h"
#include "log_memory_implementation.h"
#include "unity.h"


#include "ch.h"

#include "mock_chmboxes.h"
#include "mock_log_memory_eeprom.h"
#include "mock_memory_pool.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

/** Number of loops used to verify thread runs in an 'infinite' loop */
#define LOG_MEMORY_THREAD_TEST_LOOPS        100

/** Exception to throw to get out of the thread's infinite loop */
#define GET_OUT_OF_LOOP                     0x80808080

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Throws an exception to get out of _log_memory_thread_f after all mock checks
 * done
 *
 * @param[in] lm: Value to pass to the thread
 */
static void _log_memory_thread_f_call_and_bail(log_memory_t * lm);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static log_memory_t lm; /**< Log memory instance for these tests */

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Forward declaration so we can access internal function */
void _log_memory_thread_f(void * _lm);

/* --- TESTS ---------------------------------------------------------------- */

void test_log_memory_thread_f_should_write_entry_from_mailbox(void)
{
    uint8_t entry_buf[4] = {0};
    uint8_t * entry = entry_buf;

    log_memory_eeprom_setup_Expect(&lm);
    chMBFetch_ExpectAndReturn(&(lm.mbox), NULL, TIME_INFINITE, MSG_OK);
    chMBFetch_IgnoreArg_msgp();
    chMBFetch_ReturnThruPtr_msgp((msg_t *) &entry);

    log_memory_eeprom_write_entry_Expect(&lm, entry);
    memory_pool_free_Expect(lm.mp, entry);

    _log_memory_thread_f_call_and_bail(&lm);
}

void test_log_memory_thread_f_should_not_write_entry_if_mbox_fetch_fails(void)
{
    log_memory_eeprom_setup_Expect(&lm);
    chMBFetch_ExpectAndReturn(&(lm.mbox), NULL, TIME_INFINITE, MSG_RESET);
    chMBFetch_IgnoreArg_msgp();

    _log_memory_thread_f_call_and_bail(&lm);
}

void test_log_memory_thread_f_should_loop(void)
{
    uint8_t entry_buf[4] = {0};
    uint8_t * entry = entry_buf;

    log_memory_eeprom_setup_Expect(&lm);

    uint32_t i;
    for (i = 0; i < LOG_MEMORY_THREAD_TEST_LOOPS; i++) {
        chMBFetch_ExpectAndReturn(&(lm.mbox), NULL, TIME_INFINITE, MSG_OK);
        chMBFetch_IgnoreArg_msgp();
        chMBFetch_ReturnThruPtr_msgp((msg_t *) &entry);

        log_memory_eeprom_write_entry_Expect(&lm, entry);
        memory_pool_free_Expect(lm.mp, entry);
    }

    _log_memory_thread_f_call_and_bail(&lm);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static void _log_memory_thread_f_call_and_bail(log_memory_t * lm)
{
    chMBFetch_ExpectAndThrow(NULL, NULL, 0, GET_OUT_OF_LOOP);
    chMBFetch_IgnoreArg_mbp();
    chMBFetch_IgnoreArg_msgp();
    chMBFetch_IgnoreArg_timeout();

    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        _log_memory_thread_f(lm);
    } Catch (e) { }
}

/** @} addtogroup TEST_LOG_MEMORY_THREAD */
