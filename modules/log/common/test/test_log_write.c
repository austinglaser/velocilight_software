/**@file    test_log_write.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestLogWrite Source
 *
 * @addtogroup TEST_LOG_WRITE
 * @{
 *
 * [X] Request no system_info data when flags cleared
 * [X] Pass memory_pool buffer to serialize
 * [X] Pass buffer and entry length to log_memory
 * [X] Request appropriate system data when various flags set
 * [X] Pass log entry through unchanged when valid
 * [X] Silently clear invalid flags
 * [X] Check for invalid types and flags
 * [X] Do nothing when memory allocation fails
 *
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"
#include "log.h"

#include "CException.h"
#include "ensure.h"
#include "ensure_c_exception.h"
#include "unity_log_helper.h"
#include "unity_util.h"
#include "util.h"

#include "mock_log_memory.h"
#include "mock_log_serialize.h"
#include "mock_memory_pool.h"
#include "mock_system_info.h"

#include "memory_pool_stub.h"
#include "log_memory_stub.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

/** The shortest possible log, containing only mandatory fields */
#define MINIMAL_LOG_LEN     16

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Expect that log_write will throw an ENSURE_FAILURE when passed @p entry
 *
 * @param[in] entry:    An invalid entry
 */
static void _log_write_should_fail_ensure_for_entry(log_entry_t const * entry);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static eeprom_t       dummy_eeprom;
static project_info_t dummy_project_info;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void setUp(void)
{
    memory_pool_init_StubWithCallback(memory_pool_stub_init);
    log_serialize_init_Ignore();
    log_memory_init_StubWithCallback(log_memory_stub_init);

    log_init(&dummy_eeprom, &dummy_project_info);
}

/* --- TESTS ---------------------------------------------------------------- */

void test_log_write_should_request_only_timestamp_when_no_flags_given(void)
{
    log_entry_t entry = {
        .type    = TYPE_EXCEPTION,
        .subtype = SUBTYPE_UNKNOWN_EXCEPTION,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_time_t current_time = 1023923;
    system_info_get_time_ExpectAndReturn(current_time);

    log_serialize_ExpectAndReturn(NULL, NULL, current_time,
                                  0, 0, 0,
                                  MINIMAL_LOG_LEN);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_entry();
    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_request_timestamp_and_pc_when_pc_flag_set(void)
{
    log_entry_t entry = {
        .type    = TYPE_EXCEPTION,
        .subtype = SUBTYPE_UNKNOWN_EXCEPTION,
        .flags   = LOG_FLAG_PC,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_time_t current_time = 1023923;
    system_info_get_time_ExpectAndReturn(current_time);
    uint32_t pc = 0xAC942EF;
    system_info_get_lr_ExpectAndReturn(pc);

    log_serialize_ExpectAndReturn(NULL, NULL, current_time,
                                  pc, 0, 0,
                                  MINIMAL_LOG_LEN + sizeof(pc));
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_entry();
    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_request_timestamp_and_sp_when_sp_flag_set(void)
{
    log_entry_t entry = {
        .type    = TYPE_EXCEPTION,
        .subtype = SUBTYPE_UNKNOWN_EXCEPTION,
        .flags   = LOG_FLAG_SP,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_time_t current_time = 1023923;
    system_info_get_time_ExpectAndReturn(current_time);
    uint32_t sp = 0xFF0D045;
    system_info_get_sp_ExpectAndReturn(sp);

    log_serialize_ExpectAndReturn(NULL, NULL, current_time,
                                  0, sp, 0,
                                  MINIMAL_LOG_LEN + sizeof(sp));
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_entry();
    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_request_timestamp_and_usage_when_usage_flag_set(void)
{
    log_entry_t entry = {
        .type    = TYPE_EXCEPTION,
        .subtype = SUBTYPE_UNKNOWN_EXCEPTION,
        .flags   = LOG_FLAG_SU,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_time_t current_time = 1023923;
    system_info_get_time_ExpectAndReturn(current_time);
    uint32_t usage = 1014;
    system_info_get_stack_used_ExpectAndReturn(usage);

    log_serialize_ExpectAndReturn(NULL, NULL, current_time,
                                  0, 0, usage,
                                  MINIMAL_LOG_LEN + sizeof(usage));
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_entry();
    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_request_all_system_info_info_when_all_flags_set(void)
{
    log_entry_t entry = {
        .type    = TYPE_EXCEPTION,
        .subtype = SUBTYPE_UNKNOWN_EXCEPTION,
        .flags   = LOG_FLAG_PC | LOG_FLAG_SP | LOG_FLAG_SU,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_time_t current_time = 1023923;
    system_info_get_time_ExpectAndReturn(current_time);
    uint32_t pc = 0x0800FCDA;
    system_info_get_lr_ExpectAndReturn(pc);
    uint32_t sp = 0x20003340;
    system_info_get_sp_ExpectAndReturn(sp);
    uint32_t usage = 5000;
    system_info_get_stack_used_ExpectAndReturn(usage);

    log_serialize_ExpectAndReturn(NULL, NULL, current_time,
                                  pc, sp, usage,
                                  MINIMAL_LOG_LEN +
                                    sizeof(pc) +
                                    sizeof(sp) +
                                    sizeof(usage));
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_entry();
    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_allocate_buffer_from_initialized_memory_pool(void)
{
    log_entry_t entry = {
        .type    = TYPE_RUNTIME_ERROR,
        .subtype = SUBTYPE_UNKNOWN_RUNTIME_ERROR,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_init_args_t const * mempool_args = memory_pool_stub_init_args();
    memory_pool_alloc_ExpectAndReturn(mempool_args->mp, buffer);

    system_info_get_time_IgnoreAndReturn(8923230);
    log_serialize_IgnoreAndReturn(16);
    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_pass_allocated_buffer_to_serialize(void)
{
    log_entry_t entry = {
        .type    = TYPE_RUNTIME_ERROR,
        .subtype = SUBTYPE_UNKNOWN_RUNTIME_ERROR,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_time_t current_time = 9083842;
    system_info_get_time_IgnoreAndReturn(current_time);
    log_serialize_ExpectAndReturn(buffer, &entry, current_time,
                                  0, 0, 0,
                                  MINIMAL_LOG_LEN);
    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_pass_entry_through_unchanged_when_entry_is_valid(void)
{
    log_entry_t entry = {
        .type    = TYPE_RESET,
        .subtype = SUBTYPE_UNKNOWN_RESET,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_time_t current_time = 32458;
    system_info_get_time_IgnoreAndReturn(current_time);

    size_t len = 32;
    log_serialize_ExpectAndReturn(buffer, &entry, current_time, 0, 0, 0, len);

    log_memory_init_args_t const * args = log_memory_stub_init_args();
    log_memory_write_Expect(args->lm, buffer);

    log_write(&entry);
}

void test_log_write_should_not_write_to_memory_when_serialize_fails(void)
{
    log_entry_t entry = {
        .type    = TYPE_RESET,
        .subtype = SUBTYPE_UNKNOWN_RESET,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);
    system_info_get_time_IgnoreAndReturn(29232);
    log_serialize_IgnoreAndReturn(0);

    log_write(&entry);
}

void test_log_write_should_reject_invalid_flags(void)
{
    log_entry_t entry = {
        .type    = TYPE_RESET,
        .subtype = SUBTYPE_UNKNOWN_RESET,
        .flags   = 0xFFFF,
    };

    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        log_write(&entry);
    } Catch (e) { }

    TEST_ASSERT_EQUAL(e, ENSURE_FAILED);
}

void test_log_write_should_accept_type_of_zero(void)
{
    log_entry_t entry = {
        .type    = 0x00,
        .subtype = 0x00,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(90302);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 88);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_accept_max_type(void)
{
    log_entry_t entry = {
        .type    = MAX_TYPE,
        .subtype = 0x00,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(8632);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 88);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_accept_zero_custom_subtype(void)
{
    log_entry_t entry = {
        .type    = MAX_CUSTOM_TYPE,
        .subtype = 0x00,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(11111111111);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 88);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_accept_max_custom_subtype(void)
{
    log_entry_t entry = {
        .type    = MAX_CUSTOM_TYPE,
        .subtype = MAX_CUSTOM_TYPE_SUBTYPE,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(11111111111);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 88);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_accept_max_reset_subtype(void)
{
    log_entry_t entry = {
        .type    = TYPE_RESET,
        .subtype = MAX_RESET_SUBTYPE,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(11111111111);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 88);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_accept_max_exception_subtype(void)
{
    log_entry_t entry = {
        .type    = TYPE_EXCEPTION,
        .subtype = MAX_EXCEPTION_SUBTYPE,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(11111111111);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 88);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_accept_max_runtime_error_subtype(void)
{
    log_entry_t entry = {
        .type    = TYPE_RUNTIME_ERROR,
        .subtype = MAX_RUNTIME_ERROR_SUBTYPE,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(11111111111);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 88);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_accept_max_state_change_subtype(void)
{
    log_entry_t entry = {
        .type    = TYPE_STATE_CHANGE,
        .subtype = MAX_STATE_CHANGE_SUBTYPE,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(11111111111);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 88);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_reject_invalid_type(void)
{
    log_entry_t entry = {
        .subtype = 0x00,
        .flags   = LOG_NO_FLAGS,
    };

    uint8_t bad_types[] = { MAX_TYPE + 1, UINT8_MAX };

    uint32_t i;
    for (i = 0; i < ARRAY_ELEMENTS(bad_types); i++) {
        entry.type = bad_types[i];
        _log_write_should_fail_ensure_for_entry(&entry);
    }
}

void test_log_write_should_reject_invalid_reset_subtype(void)
{
    log_entry_t entry = {
        .type  = TYPE_RESET,
        .flags = LOG_NO_FLAGS,
    };

    uint8_t bad_subtypes[] = { MAX_RESET_SUBTYPE + 1, UINT8_MAX };

    uint32_t i;
    for (i = 0; i < ARRAY_ELEMENTS(bad_subtypes); i++) {
        entry.subtype = bad_subtypes[i];
        _log_write_should_fail_ensure_for_entry(&entry);
    }
}

void test_log_write_should_reject_invalid_exception_subtype(void)
{
    log_entry_t entry = {
        .type  = TYPE_EXCEPTION,
        .flags = LOG_NO_FLAGS,
    };

    uint8_t bad_subtypes[] = { MAX_EXCEPTION_SUBTYPE + 1, UINT8_MAX };

    uint32_t i;
    for (i = 0; i < ARRAY_ELEMENTS(bad_subtypes); i++) {
        entry.subtype = bad_subtypes[i];
        _log_write_should_fail_ensure_for_entry(&entry);
    }
}

void test_log_write_should_reject_invalid_runtime_error_subtype(void)
{
    log_entry_t entry = {
        .type  = TYPE_RUNTIME_ERROR,
        .flags = LOG_NO_FLAGS,
    };

    uint8_t bad_subtypes[] = { MAX_RUNTIME_ERROR_SUBTYPE + 1, UINT8_MAX };

    uint32_t i;
    for (i = 0; i < ARRAY_ELEMENTS(bad_subtypes); i++) {
        entry.subtype = bad_subtypes[i];
        _log_write_should_fail_ensure_for_entry(&entry);
    }
}

void test_log_write_should_reject_invalid_state_change_subtype(void)
{
    log_entry_t entry = {
        .type  = TYPE_STATE_CHANGE,
        .flags = LOG_NO_FLAGS,
    };

    uint8_t bad_subtypes[] = { MAX_STATE_CHANGE_SUBTYPE + 1, UINT8_MAX };

    uint32_t i;
    for (i = 0; i < ARRAY_ELEMENTS(bad_subtypes); i++) {
        entry.subtype = bad_subtypes[i];

        _log_write_should_fail_ensure_for_entry(&entry);
    }
}

void test_log_write_should_reject_invalid_custom_type_subtype(void)
{
    log_entry_t entry = {
        .type  = 0x001,
        .flags = LOG_NO_FLAGS,
    };

    uint8_t bad_subtypes[] = { MAX_CUSTOM_TYPE_SUBTYPE + 1, UINT8_MAX };

    uint32_t i;
    for (i = 0; i < ARRAY_ELEMENTS(bad_subtypes); i++) {
        entry.subtype = bad_subtypes[i];

        _log_write_should_fail_ensure_for_entry(&entry);
    }
}

void test_log_write_should_silently_fail_when_memory_allocation_fails(void)
{
    log_entry_t entry = {
        .type    = 0x001,
        .subtype = 0x02,
        .flags   = LOG_NO_FLAGS,
    };

    memory_pool_alloc_ExpectAndReturn(NULL, NULL);
    memory_pool_alloc_IgnoreArg_mp();

    log_write(&entry);
}

void test_log_write_should_accept_valid_descriptor_string_when_dsc_flag_set(void)
{
    log_entry_t entry = {
        .type              = TYPE_EXCEPTION,
        .subtype           = SUBTYPE_HARD_FAULT_EXCEPTION,
        .flags             = LOG_FLAG_DSC,
        .descriptor_string = "describes the exception",
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(8232320);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 42);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_reject_invalid_descriptor_string_when_dsc_flag_set(void)
{
    log_entry_t entry = {
        .type              = TYPE_EXCEPTION,
        .subtype           = SUBTYPE_HARD_FAULT_EXCEPTION,
        .flags             = LOG_FLAG_DSC,
        .descriptor_string = NULL,
    };

    _log_write_should_fail_ensure_for_entry(&entry);
}

void test_log_write_should_accept_single_valid_binary_data_when_bin_flag_set(void)
{
    struct {
        uint32_t x;
        uint8_t y;
    } object;

    log_entry_t entry = {
        .type              = TYPE_EXCEPTION,
        .subtype           = SUBTYPE_HARD_FAULT_EXCEPTION,
        .flags             = LOG_FLAG_BIN,
        .binary_data_count = 1,
        .binary_data[0]    = {
            .data = &object,
            .len  = sizeof(object),
        },
    };

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(8232320);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 42);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_accept_multiple_valid_binary_data_when_bin_flag_set(void)
{
    struct {
        uint32_t x;
        uint8_t y;
    } object;

    log_entry_t entry = {
        .type              = TYPE_EXCEPTION,
        .subtype           = SUBTYPE_HARD_FAULT_EXCEPTION,
        .flags             = LOG_FLAG_BIN,
        .binary_data_count = LOG_MAX_BINARY_DATA,
    };

    uint32_t i;
    for (i = 0; i < LOG_MAX_BINARY_DATA; i++) {
        entry.binary_data[i].len = sizeof(object);
        entry.binary_data[i].data = &object;
    }

    uint8_t buffer[LOG_BUFFER_LEN];
    memory_pool_alloc_IgnoreAndReturn(buffer);

    system_info_get_time_IgnoreAndReturn(8232320);

    log_serialize_ExpectAndReturn(NULL, &entry, 0, 0, 0, 0, 42);
    log_serialize_IgnoreArg_buf();
    log_serialize_IgnoreArg_timestamp();
    log_serialize_IgnoreArg_program_counter();
    log_serialize_IgnoreArg_stack_pointer();
    log_serialize_IgnoreArg_stack_usage();

    log_memory_write_Ignore();

    log_write(&entry);
}

void test_log_write_should_reject_null_entry(void)
{
    _log_write_should_fail_ensure_for_entry(NULL);
}

void test_log_write_should_reject_invalid_binary_data_count_when_bin_flag_set(void)
{
    struct {
        uint32_t x;
        uint8_t y;
    } object;

    /* We declare an array of entries here so we can 'safely' write beyond the
     * end of the binary_data field in the first one. */
    log_entry_t entries[2] = {
        {
            .type    = TYPE_EXCEPTION,
            .subtype = SUBTYPE_HARD_FAULT_EXCEPTION,
            .flags   = LOG_FLAG_BIN,
        },
        { 0 },
    };

    log_entry_t * entry = &(entries[0]);

    uint32_t i;
    for (i = 0; i < LOG_MAX_BINARY_DATA + 2; i++) {
        entry->binary_data[i].len = sizeof(object);
        entry->binary_data[i].data = &object;
    }

    uint32_t bad_counts[] = { 0, LOG_MAX_BINARY_DATA + 1, UINT32_MAX};

    for (i = 0; i < ARRAY_ELEMENTS(bad_counts); i++) {
        entry->binary_data_count = bad_counts[i];
        _log_write_should_fail_ensure_for_entry(entry);
    }
}

void test_log_write_should_reject_invalid_binary_data_size_when_bin_flag_set(void)
{
    struct {
        uint32_t x;
        uint8_t y;
    } object;

    log_entry_t entry = {
        .type              = TYPE_EXCEPTION,
        .subtype           = SUBTYPE_HARD_FAULT_EXCEPTION,
        .flags             = LOG_FLAG_BIN,
        .binary_data_count = LOG_MAX_BINARY_DATA,
    };

    uint32_t i;
    for (i = 0; i < LOG_MAX_BINARY_DATA; i++) {
        entry.binary_data[i].len = sizeof(object);
        entry.binary_data[i].data = &object;
    }

    entry.binary_data[3].len = 0;

    _log_write_should_fail_ensure_for_entry(&entry);
}

void test_log_write_should_reject_invalid_binary_data_pointer_when_bin_flag_set(void)
{
    struct {
        uint32_t x;
        uint8_t y;
    } object;

    log_entry_t entry= {
        .type              = TYPE_EXCEPTION,
        .subtype           = SUBTYPE_HARD_FAULT_EXCEPTION,
        .flags             = LOG_FLAG_BIN,
        .binary_data_count = LOG_MAX_BINARY_DATA,
    };

    uint32_t i;
    for (i = 0; i < LOG_MAX_BINARY_DATA; i++) {
        entry.binary_data[i].len = sizeof(object);
        entry.binary_data[i].data = &object;
    }

    entry.binary_data[LOG_MAX_BINARY_DATA - 1].data = NULL;

    _log_write_should_fail_ensure_for_entry(&entry);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static void _log_write_should_fail_ensure_for_entry(log_entry_t const * entry)
{
    volatile bool exception_thrown = false;
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        log_write(entry);
        TEST_FAIL_MESSAGE("log_write expected to throw an ensure exception");
    } Catch (e) {
        exception_thrown = true;
    }

    TEST_ASSERT_MESSAGE(exception_thrown, "No ensure exception thrown");
    TEST_ASSERT_EQUAL(e, ENSURE_FAILED);
}

/** @} addtogroup TEST_LOG_WRITE */
