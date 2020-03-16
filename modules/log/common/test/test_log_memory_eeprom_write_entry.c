/**@file    test_log_memory_eeprom_write_entry.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestLogMemoryEepromWriteEntry Source
 *
 * @addtogroup TEST_LOG_MEMORY_EEPROM_WRITE_ENTRY
 * @{
 *
 * Test list:
 * [X] Write entry to empty memory
 * [X] Write entry when memory has some data
 *      [X] New entry will not overflow
 *      [] New entry will overflow
 * [X] Write entry when too long for end of memory
 * [] Write entry when memory has already wrapped
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_memory.h"
#include "log_memory_implementation.h"
#include "log_memory_eeprom.h"
#include "unity.h"

#include "CException.h"
#include "eeprom.h"
#include "ensure.h"
#include "ensure_c_exception.h"
#include "project_info.h"
#include "util.h"

#include "log_memory_eeprom_test_util.h"

#include "mock_eeprom.h"
#include "fake_eeprom.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

/** Value used in the log used to denote an invalid 32-bit value */
#define INVALID_VALUE   0xFFFFFFFF

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Fills @p entry with a length and a constant value throughout its body
 *
 * @param[in] entry:            Buffer to fill
 * @param[in] fill_byte:        Value to fill entry with
 * @param[in] entry_length:     Length of buffer; value to put in first 4 bytes
 *                              of @p entry
 */
static void _fill_entry(uint8_t * entry,
                        uint8_t fill_byte,
                        uint32_t entry_length);

/** Validate that the memory at @p address matches the provided entry
 *
 * @param[in] address:          Where in memory to look for the entry
 * @param[in] expected_entry:   Entry that should live at @p address
 * @param[in] expected_length:  Length of @p expected_entry
 */
static void _validate_entry(uint32_t address,
                            uint8_t const * expected_entry,
                            uint32_t expected_length);

/** Expect that log_memory_eeprom_write_entry will fail when passed the
 * provided arguments
 *
 * @param[in,out] lm:           A log memory handle
 * @param[in] entry:            An entry to write
 */
static void _expect_log_memory_eeprom_write_entry_failure(log_memory_t * lm,
                                                          uint8_t const * entry);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static log_memory_t lm;    /**< A log memory instance */

static eeprom_t e;         /**< Dummy EEPROM */
static mem_pool_t mp;      /**< Dummy memory pool */
static thread_t lm_thread; /**< Dummy thread handle*/
static mailbox_t mbox;     /**< Dummy mailbox */
static project_info_t pi;  /**< Dummy project information */

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void setUp(void)
{
    log_memory_eeprom_helper_fill_project_info(&pi);

    lm.e      = &e;
    lm.mp     = &mp;
    lm.pi     = &pi;
    lm.thread = &lm_thread;
    lm.mbox   = mbox;

    fake_eeprom_reset(lm.e);

    eeprom_erase_StubWithCallback(fake_eeprom_erase);
    eeprom_read_StubWithCallback(fake_eeprom_read);
    eeprom_write_StubWithCallback(fake_eeprom_write);
    eeprom_size_IgnoreAndReturn(EEPROM_MEMORY_SIZE);
    eeprom_write_size_IgnoreAndReturn(1);

    log_memory_eeprom_setup(&lm);
}

/* --- TESTS ---------------------------------------------------------------- */

void test_log_memory_eeprom_write_entry_writes_entry_when_log_empty(void)
{
    uint32_t entry_length = 32;
    uint8_t entry[128];
    _fill_entry(entry, 0x55, entry_length);

    log_memory_eeprom_write_entry(&lm, entry);

    uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
    uint32_t head      = log_memory_eeprom_helper_get_head(&e);
    uint32_t tail      = log_memory_eeprom_helper_get_tail(&e);

    uint32_t log_data_start = log_start + BK_LENGTH;
    TEST_ASSERT_EQUAL_UINT32(log_data_start,                tail);
    TEST_ASSERT_EQUAL_UINT32(log_data_start + entry_length, head);

    _validate_entry(tail, entry, entry_length);
}

void test_log_memory_eeprom_write_entry_writes_two_entries_back_to_back(void)
{
    uint32_t const first_entry_length = 32;
    uint8_t first_entry[first_entry_length];
    _fill_entry(first_entry, 0x55, first_entry_length);

    uint32_t const second_entry_length = 16;
    uint8_t second_entry[second_entry_length];
    _fill_entry(second_entry, 0xAA, second_entry_length);

    log_memory_eeprom_write_entry(&lm, first_entry);
    log_memory_eeprom_write_entry(&lm, second_entry);

    uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
    uint32_t head      = log_memory_eeprom_helper_get_head(&e);
    uint32_t tail      = log_memory_eeprom_helper_get_tail(&e);

    uint32_t log_data_start = log_start + BK_LENGTH;
    uint32_t expected_tail = log_data_start;
    uint32_t expected_head = log_data_start +
                             first_entry_length +
                             second_entry_length;
    TEST_ASSERT_EQUAL_UINT32(expected_tail, tail);
    TEST_ASSERT_EQUAL_UINT32(expected_head, head);

    _validate_entry(tail,
                    first_entry,
                    first_entry_length);
    _validate_entry(tail + first_entry_length,
                    second_entry,
                    second_entry_length);
}

void test_log_memory_eeprom_write_entry_wraps_when_entry_too_long(void)
{
    uint32_t const entry_length = 20;
    uint8_t entry[entry_length];
    _fill_entry(entry, 0x80, entry_length);

    uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
    uint32_t log_end   = log_memory_eeprom_helper_get_log_end(&e);
    uint32_t starting_head = EEPROM_MEMORY_SIZE - 16;
    uint32_t starting_tail = log_start + BK_LENGTH + entry_length + 4;
    log_memory_eeprom_helper_set_head(&e, starting_head);
    log_memory_eeprom_helper_set_tail(&e, starting_tail);

    /* This is so the cached head and tail values are updated */
    log_memory_eeprom_setup(&lm);

    log_memory_eeprom_write_entry(&lm, entry);

    uint32_t head          = log_memory_eeprom_helper_get_head(&e);
    uint32_t tail          = log_memory_eeprom_helper_get_tail(&e);
    uint32_t expected_tail = starting_tail;
    uint32_t bytes_at_end  = log_end - starting_head;
    uint32_t expected_head = log_start + BK_LENGTH + (entry_length - bytes_at_end);
    TEST_ASSERT_EQUAL_UINT32(expected_tail, tail);
    TEST_ASSERT_EQUAL_UINT32(expected_head, head);
    _validate_entry(starting_head, entry, entry_length);
}

void test_log_memory_eeprom_write_entry_removes_oldest_entry_when_full(void)
{
    uint32_t const entry_length = 20;
    uint8_t entry[entry_length];
    _fill_entry(entry, 0x88, entry_length);

    uint32_t starting_head = 200;
    uint32_t starting_tail = 216;
    uint32_t tail_entry_length = 28;
    log_memory_eeprom_helper_set_head(&e, starting_head);
    log_memory_eeprom_helper_set_tail(&e, starting_tail);
    log_memory_eeprom_helper_set_value(&e, starting_tail, tail_entry_length);

    /* This is so the cached head and tail values are updated */
    log_memory_eeprom_setup(&lm);

    log_memory_eeprom_write_entry(&lm, entry);

    uint32_t head          = log_memory_eeprom_helper_get_head(&e);
    uint32_t tail          = log_memory_eeprom_helper_get_tail(&e);
    uint32_t expected_tail = starting_tail + tail_entry_length;
    uint32_t expected_head = starting_head + entry_length;
    TEST_ASSERT_EQUAL_UINT32(expected_tail, tail);
    TEST_ASSERT_EQUAL_UINT32(expected_head, head);
    _validate_entry(head - entry_length, entry, entry_length);
}

void test_log_memory_eeprom_write_entry_removes_multiple_entries_when_full(void)
{
    uint32_t const entry_length = 28;
    uint8_t entry[entry_length];
    _fill_entry(entry, 0x11, entry_length);

    uint32_t starting_head = 116;
    uint32_t starting_tail = 120;
    uint32_t first_tail_entry_length = 16;
    uint32_t second_tail_entry_length = 16;
    log_memory_eeprom_helper_set_head(&e, starting_head);
    log_memory_eeprom_helper_set_tail(&e, starting_tail);
    log_memory_eeprom_helper_set_value(&e,
                                      starting_tail,
                                      first_tail_entry_length);
    log_memory_eeprom_helper_set_value(&e,
                                      starting_tail + first_tail_entry_length,
                                      second_tail_entry_length);

    /* This is so the cached head and tail values are updated */
    log_memory_eeprom_setup(&lm);

    log_memory_eeprom_write_entry(&lm, entry);

    uint32_t head          = log_memory_eeprom_helper_get_head(&e);
    uint32_t tail          = log_memory_eeprom_helper_get_tail(&e);
    uint32_t expected_tail = starting_tail +
                             first_tail_entry_length +
                             second_tail_entry_length;
    uint32_t expected_head = starting_head + entry_length;
    TEST_ASSERT_EQUAL_UINT32(expected_tail, tail);
    TEST_ASSERT_EQUAL_UINT32(expected_head, head);
    _validate_entry(starting_head, entry, entry_length);
}

void test_log_memory_eeprom_write_entry_wraps_when_removing_entries(void)
{
    uint32_t const entry_length = 16;
    uint8_t entry[entry_length];
    _fill_entry(entry, 0x22, entry_length);

    uint32_t starting_tail = 2016;
    uint32_t starting_head = 2012;

    uint32_t tail_entry_length = 64;

    log_memory_eeprom_helper_set_head(&e, starting_head);
    log_memory_eeprom_helper_set_tail(&e, starting_tail);
    log_memory_eeprom_helper_set_value(&e, starting_tail, tail_entry_length);

    /* This is so the cached head and tail values are updated */
    log_memory_eeprom_setup(&lm);

    log_memory_eeprom_write_entry(&lm, entry);

    uint32_t head            = log_memory_eeprom_helper_get_head(&e);
    uint32_t tail            = log_memory_eeprom_helper_get_tail(&e);
    uint32_t wrap_address    = log_memory_eeprom_helper_get_log_start(&e) +
                               BK_LENGTH;
    uint32_t tail_entry_wrap = tail_entry_length -
                               (e.size - starting_tail);
    uint32_t expected_tail   = wrap_address + tail_entry_wrap;
    uint32_t expected_head   = starting_head + entry_length;
    TEST_ASSERT_EQUAL_UINT32(expected_tail, tail);
    TEST_ASSERT_EQUAL_UINT32(expected_head, head);
    _validate_entry(starting_head, entry, entry_length);
}

void test_log_memory_eeprom_write_entry_fails_when_entry_too_long(void)
{
    uint32_t const entry_length = e.size - HEADER_LENGTH - BK_LENGTH;
    uint8_t entry[entry_length];
    _fill_entry(entry, 0x33, entry_length);

    _expect_log_memory_eeprom_write_entry_failure(&lm, entry);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static void _fill_entry(uint8_t * entry,
                        uint8_t fill_byte,
                        uint32_t entry_length)
{
    memcpy(entry, &entry_length, sizeof(uint32_t));
    memset(entry + sizeof(uint32_t),
           fill_byte,
           entry_length - sizeof(uint32_t));
}

static void _validate_entry(uint32_t address,
                            uint8_t const * expected_entry,
                            uint32_t expected_length)
{
    uint8_t const * written_entry = e.memory + address;
    uint32_t written_length = *((uint32_t *) written_entry);

    TEST_ASSERT_EQUAL_UINT32(expected_length, written_length);

    uint32_t i;
    for (i = 0; i < expected_length; i++) {
        uint32_t current_offset = address + i;
        if (current_offset >= e.size) {
            uint32_t wrap_offset = log_memory_eeprom_helper_get_log_start(&e) +
                                   BK_LENGTH;
            current_offset = wrap_offset + (current_offset % e.size);
        }

        uint8_t const * current_byte = e.memory + current_offset;

        TEST_ASSERT_EQUAL_UINT8(expected_entry[i], *current_byte);
    }
}

static void _expect_log_memory_eeprom_write_entry_failure(log_memory_t * lm,
                                                          uint8_t const * entry)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;

    Try {
        log_memory_eeprom_write_entry(lm, entry);
    } Catch (e) {
        TEST_ASSERT_EQUAL_HEX32(ENSURE_FAILED, e);
        return;
    }

    TEST_FAIL_MESSAGE("No ensure exception thrown");
}

/** @} addtogroup TEST_LOG_MEMORY_EEPROM_WRITE_ENTRY */
