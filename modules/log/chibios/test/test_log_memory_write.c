/**@file    test_log_memory_write.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestLogMemoryWrite Source
 *
 * @addtogroup TEST_LOG_MEMORY_WRITE
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_memory.h"
#include "log_memory_implementation.h"
#include "unity.h"

#include "ch.h"
#include "mock_chsys.h"
#include "mock_chmboxes.h"

#include "mock_memory_pool.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static log_memory_t lm;    /**< A log memory instance */

static eeprom_t e;         /**< Dummy EEPROM */
static mem_pool_t mp;      /**< Dummy memory pool */
static thread_t lm_thread; /**< Dummy thread handle*/
static mailbox_t mbox;     /**< Dummy mailbox */

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void setUp(void)
{
    lm.e      = &e;
    lm.mp     = &mp;
    lm.thread = &lm_thread;
    lm.mbox   = mbox;
}

/* --- TESTS ---------------------------------------------------------------- */

void test_log_memory_write_should_write_entry_to_mailbox(void)
{
    uint8_t entry[16];

    chSysLock_Expect();
    chMBPostI_ExpectAndReturn(&(lm.mbox), (msg_t) entry, MSG_OK);
    chSysUnlock_Expect();

    log_memory_write(&lm, entry);
}

void test_log_memory_write_should_free_entry_if_queue_write_fails(void)
{
    uint8_t entry[32];

    chSysLock_Expect();
    chMBPostI_ExpectAndReturn(&(lm.mbox), (msg_t) entry, MSG_TIMEOUT);
    chSysUnlock_Expect();

    memory_pool_free_Expect(lm.mp, entry);

    log_memory_write(&lm, entry);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_LOG_MEMORY_WRITE */
