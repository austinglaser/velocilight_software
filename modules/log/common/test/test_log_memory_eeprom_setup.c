/**@file    test_log_memory_eeprom_setup.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestLogMemoryEepromSetup Source
 *
 * @addtogroup TEST_LOG_MEMORY_EEPROM_SETUP
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_memory.h"
#include "log_memory_implementation.h"
#include "log_memory_eeprom.h"
#include "unity.h"

#include "eeprom.h"
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

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Ensure that the header matches the values in @ref pi */
static void _validate_header(uint32_t expected_log_start);

/** Ensure that the bookkeeping values are valid */
static void _validate_bookkeeping(uint32_t expected_head,
                                  uint32_t expected_tail);

/** Ensure that the bookkeeping values are valid, and the log is empty */
static void _validate_bookkeeping_empty(void);

/** Returns true if eeprom was erased as part of init, false otherwise */
static bool _eeprom_has_been_erased(void);

/** Fills EEPROM memory so @ref _eeprom_has_been_erased() can function properly */
static void _eeprom_fill_to_detect_erasure(void);

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
}

/* --- TESTS ---------------------------------------------------------------- */

void test_log_memory_eeprom_setup_should_write_header_when_memory_is_blank(void)
{
    eeprom_write_size_IgnoreAndReturn(1);

    log_memory_eeprom_setup(&lm);

    _validate_header(HEADER_LENGTH);
}

void test_log_memory_eeprom_setup_should_start_log_at_next_page_boundary(void)
{
    /* Header data is stored in a separate EEPROM 'page' (minimal writeable
     * unit) to avoid excessive copy/rewrite of constant data (and possible
     * corruption). This test ensures that log_memory_eeprom_setup correctly
     * requests and uses this value when initializing the memory region.
     *
     * Note that, for many EEPROM parts, a page is the MAXIMUM writeable unit,
     * with the minimum writeable unit being a byte (thus eeprom_write_size()
     * instead of eeprom_page_size()).
     */
    uint32_t const write_size = 128;
    eeprom_write_size_IgnoreAndReturn(write_size);

    log_memory_eeprom_setup(&lm);

    _validate_header(write_size);
}

void test_log_memory_eeprom_setup_should_initialize_bookkeeping_region(void)
{
    eeprom_write_size_IgnoreAndReturn(1);

    log_memory_eeprom_setup(&lm);

    _validate_bookkeeping_empty();
}

void test_log_memory_eeprom_setup_should_zero_reserved_regions(void)
{
    eeprom_write_size_IgnoreAndReturn(1);

    log_memory_eeprom_setup(&lm);

    uint16_t reserved_flags         = log_memory_eeprom_helper_get_reserved_flags(&e);
    uint8_t const * reserved_header = log_memory_eeprom_helper_get_reserved_header(&e);
    uint8_t const * reserved_bk     = log_memory_eeprom_helper_get_reserved_bookkeeping(&e);

    uint8_t expected_reserved_fill[20] = { 0 };

    TEST_ASSERT_EQUAL_UINT16(0, reserved_flags);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_reserved_fill,
                                 reserved_header,
                                 HEADER_RESERVED_LENGTH);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_reserved_fill,
                                 reserved_bk,
                                 BK_RESERVED_LENGTH);
}

void test_log_memory_eeprom_setup_should_erase_memory_when_log_header_differs(void)
{
    eeprom_write_size_IgnoreAndReturn(1);

    log_memory_eeprom_setup(&lm);

    _eeprom_fill_to_detect_erasure();

    pi.build_timestamp = 1463539403;
    pi.repo_dirty      = true;
    pi.stable_version  = false;
    pi.project_id      = 6;
    pi.version_major   = 0;
    pi.version_minor   = 0;

    log_memory_eeprom_setup(&lm);

    TEST_ASSERT_MESSAGE(_eeprom_has_been_erased(), "EEPROM memory was not erased");
    _validate_header(HEADER_LENGTH);
    _validate_bookkeeping_empty();
}

void test_log_memory_eeprom_setup_should_not_erase_memory_when_log_header_identical(void)
{
    eeprom_write_size_IgnoreAndReturn(1);

    log_memory_eeprom_setup(&lm);

    _eeprom_fill_to_detect_erasure();

    uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
    uint32_t new_head = log_start + 1000;
    uint32_t new_tail = log_start + 80;

    log_memory_eeprom_helper_set_head(&e, new_head);
    log_memory_eeprom_helper_set_tail(&e, new_tail);

    log_memory_eeprom_setup(&lm);

    TEST_ASSERT_FALSE_MESSAGE(_eeprom_has_been_erased(), "EEPROM memory was erased");
    _validate_header(HEADER_LENGTH);
    log_start = log_memory_eeprom_helper_get_log_start(&e);
    _validate_bookkeeping(new_head, new_tail);
}

void test_log_memory_eeprom_setup_should_erase_memory_when_bookkeeping_invalid(void)
{
    eeprom_write_size_IgnoreAndReturn(1);

    log_memory_eeprom_setup(&lm);

    static uint32_t invalid_head_tail_values[] = {
        HEADER_LENGTH + EEPROM_MEMORY_SIZE,
        HEADER_LENGTH + EEPROM_MEMORY_SIZE - 15,
        HEADER_LENGTH,
        HEADER_LENGTH + BK_LENGTH - 1,
        0xFFFFFFFF,
        0x7FFFFFFF,
    };

    uint32_t i;
    for (i = 0; i < ARRAY_ELEMENTS(invalid_head_tail_values); i++) {
        uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
        log_memory_eeprom_helper_set_head(&e, invalid_head_tail_values[i]);
        log_memory_eeprom_helper_set_tail(&e, log_start + BK_LENGTH);

        _eeprom_fill_to_detect_erasure();

        log_memory_eeprom_setup(&lm);

        TEST_ASSERT_MESSAGE(_eeprom_has_been_erased(), "EEPROM memory was not erased");
        _validate_header(HEADER_LENGTH);

        log_start = log_memory_eeprom_helper_get_log_start(&e);
        _validate_bookkeeping_empty();

        log_start = log_memory_eeprom_helper_get_log_start(&e);
        log_memory_eeprom_helper_set_head(&e, log_start + BK_LENGTH);
        log_memory_eeprom_helper_set_tail(&e, invalid_head_tail_values[i]);

        _eeprom_fill_to_detect_erasure();

        log_memory_eeprom_setup(&lm);

        TEST_ASSERT_MESSAGE(_eeprom_has_been_erased(), "EEPROM memory was not erased");
        _validate_header(HEADER_LENGTH);

        log_start = log_memory_eeprom_helper_get_log_start(&e);
        _validate_bookkeeping_empty();
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static void _validate_header(uint32_t expected_log_start)
{
    uint32_t magic_number = log_memory_eeprom_helper_get_magic_number(&e);
    TEST_ASSERT_EQUAL_HEX32(LOG_MEMORY_EEPROM_MAGIC_NUMBER, magic_number);

    uint8_t const * git_hash = log_memory_eeprom_helper_get_git_hash(&e);
    uint64_t timestamp       = log_memory_eeprom_helper_get_timestamp(&e);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(pi.git_hash,    git_hash, GIT_HASH_LENGTH);
    TEST_ASSERT_EQUAL_UINT64(pi.build_timestamp, timestamp);

    bool dirty      = log_memory_eeprom_helper_get_dirty_flag(&e);
    bool not_stable = log_memory_eeprom_helper_get_not_stable_flag(&e);
    TEST_ASSERT_EQUAL(pi.repo_dirty,             dirty);
    TEST_ASSERT_EQUAL(pi.stable_version,         !not_stable);

    uint16_t client_id    = log_memory_eeprom_helper_get_client_id(&e);
    uint16_t project_id   = log_memory_eeprom_helper_get_project_id(&e);
    TEST_ASSERT_EQUAL_UINT16(pi.client_id,       client_id);
    TEST_ASSERT_EQUAL_UINT16(pi.project_id,      project_id);

    uint16_t version_major = log_memory_eeprom_helper_get_major_version(&e);
    uint8_t version_minor = log_memory_eeprom_helper_get_minor_version(&e);
    uint8_t version_patch = log_memory_eeprom_helper_get_patch_version(&e);
    TEST_ASSERT_EQUAL_UINT16(pi.version_major,   version_major);
    TEST_ASSERT_EQUAL_UINT8(pi.version_minor,    version_minor);
    TEST_ASSERT_EQUAL_UINT8(pi.version_patch,    version_patch);

    uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
    uint32_t log_end   = log_memory_eeprom_helper_get_log_end(&e);
    TEST_ASSERT_EQUAL_HEX32(expected_log_start,  log_start);
    TEST_ASSERT_EQUAL_HEX32(EEPROM_MEMORY_SIZE,  log_end);
}

static void _validate_bookkeeping(uint32_t expected_head,
                                  uint32_t expected_tail)
{
    uint32_t head = log_memory_eeprom_helper_get_head(&e);
    uint32_t tail = log_memory_eeprom_helper_get_tail(&e);

    TEST_ASSERT_EQUAL_HEX32(expected_head, head);
    TEST_ASSERT_EQUAL_HEX32(expected_tail, tail);
}

static void _validate_bookkeeping_empty(void)
{
    uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
    _validate_bookkeeping(log_start + BK_LENGTH, log_start + BK_LENGTH);
}

static bool _eeprom_has_been_erased(void)
{
    uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
    uint32_t log_data_offset = log_start + BK_LENGTH;

    uint8_t expected_memory[EEPROM_MEMORY_SIZE];
    memset(expected_memory, 0xFF, EEPROM_MEMORY_SIZE);

    return memcmp(expected_memory, e.memory + log_data_offset, e.size - log_data_offset) == 0;
}

static void _eeprom_fill_to_detect_erasure(void)
{
    uint32_t log_start = log_memory_eeprom_helper_get_log_start(&e);
    uint32_t log_data_offset = log_start + BK_LENGTH;

    memset(e.memory + log_data_offset, 0, e.size - log_data_offset);
}

/** @} addtogroup TEST_LOG_MEMORY_EEPROM_SETUP */
