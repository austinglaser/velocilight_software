/**@file    test_log_serialize.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestLogSerialize Source
 *
 * @addtogroup TEST_LOG_SERIALIZE
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_serialize.h"
#include "unity.h"

#include "log.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

/** The number of bytes required to encode a minimal log */
#define ENTRY_MINIMAL_LEN       16

/** The number of additional bytes required to store a program counter */
#define ENTRY_PC_LEN            sizeof(uint32_t)

/** The number of additional bytes required to store a stack pointer */
#define ENTRY_SP_LEN            sizeof(uint32_t)

/** The number of additional bytes required to store stack usage */
#define ENTRY_SU_LEN            sizeof(uint32_t)

/** The number of additional bytes required to store a descriptor string
 * header
 */
#define ENTRY_DSC_HEADER_LEN    sizeof(uint32_t)

/** The number of additional bytes required to store a binary data count */
#define ENTRY_BIN_COUNT_LEN     sizeof(uint32_t)

/** The number of additional bytes required to store a binary data header */
#define ENTRY_BIN_HEADER_LEN    sizeof(uint32_t)

/** Offset (in bytes) where the entry length is stored */
#define LENGTH_OFFSET_BYTES     0

/** Offset (in bytes) where the entry timestamp is stored */
#define TIMESTAMP_OFFSET_BYTES  4

/** Offset (in bytes) where the entry flags are stored */
#define FLAGS_OFFSET_BYTES      14

/** Offset (in bytes) where the entry type is stored */
#define TYPE_OFFSET_BYTES       13

/** Offset (in bytes) where the entry subtype is stored */
#define SUBTYPE_OFFSET_BYTES    12

/** Bitshift for the padding byte within the string/binary data header word */
#define PADDING_SHIFT           24

/** Bitshift for the data type byte within the binary data header word */
#define DATA_TYPE_SHIFT         16

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */

/** Retrieve a constant @p type pointer to @p buffer + @p offset, cast
 *
 * @param[in] buffer:       A serialized log entry
 * @param[in] offset:       offset from the beginning of the array
 * @param[in] type:         The type to which to cast the output
 *
 * @return      effectively: (type const *) &buffer[offset]
 */
#define PTR_AT_OFFSET(buffer, offset, type) \
    ((type const *)(((uint8_t const *) (buffer)) + (offset)))

/** Retrieve the value in  @p buffer + @p offset, typecast as @p type
 *
 * @param[in] buffer:       A serialized log entry
 * @param[in] offset:       offset from the beginning of the array
 * @param[in] type:         The type to which to cast the output
 *
 * @return      effectively: (type) buffer[offset]
 */
#define VALUE_AT_OFFSET(buffer, offset, type) \
    (*PTR_AT_OFFSET(buffer, offset, type))

/** Ensures that a portion of the buffer matches the provided data
 *
 * Increments @p offset by @p data_len
 *
 * @param[in] buffer:        The serialized entry
 * @param[in,out] offset:    The offset to examine
 * @param[in] expected_data: The values expected to appear in @p buffer at
 *                           @p offset
 * @param[in] data_len:      Size of @p expected_data
 */
#define _log_serialize_validate_value_at_offset(buffer, \
                                                offset, \
                                                expected_data, \
                                                data_len) \
    _log_serialize_validate_buffer(buffer, \
                                   offset, \
                                   expected_data, \
                                   data_len, \
                                   __LINE__)

/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Get the length of a serialized buffer
 *
 * @param[in] buffer:   Buffer to examine
 *
 * @return      The value in the length field
 */
static uint32_t _log_serialize_get_length(uint8_t const * buffer);

/** Get the timestamp value from a serialized buffer
 *
 * @param[in] buffer:   Buffer to examine
 *
 * @return      The value in the timestamp field
 */
static uint64_t _log_serialize_get_timestamp(uint8_t const * buffer);

/** Get the flags from a serialized buffer
 *
 * @param[in] buffer:   Buffer to examine
 *
 * @return      The value in the flags field
 */
static uint16_t _log_serialize_get_flags(uint8_t const * buffer);

/** Get the entry type from a serialized buffer
 *
 * @param[in] buffer:   Buffer to examine
 *
 * @return      The value in the type field
 */
static uint8_t _log_serialize_get_type(uint8_t const * buffer);

/** Get the entry subtype from a serialized buffer
 *
 * @param[in] buffer:   Buffer to examine
 *
 * @return      The value in the subtype field
 */
static uint8_t _log_serialize_get_subtype(uint8_t const * buffer);

/** Ensure that the mandatory fields stored in the buffer contain the expected
 * values.
 *
 * @param[in] buffer:    The serialized log entry
 * @param[in] length:    Length value expected in @p buffer
 * @param[in] timestamp: Timestamp value expected in @p buffer
 * @param[in] flags:     Flags value expected in @p buffer
 * @param[in] type:      Type value expected in @p buffer
 * @param[in] subtype:   Subtype value expected in @p buffer
 */
static void _log_serialize_validate_mandatory_fields(uint8_t const * buffer,
                                                     uint32_t length,
                                                     uint64_t timestamp,
                                                     uint16_t flags,
                                                     uint8_t type,
                                                     uint8_t subtype);

/** Ensures that a portion of the buffer matches the provided data
 *
 * Increments @p offset by @p data_len
 *
 * @note    Should usually be called using the
 *          @ref _log_serialize_validate_value_at_offset macro
 *
 * @param[in] buffer:        The serialized entry
 * @param[in,out] offset:    The offset to examine
 * @param[in] expected_data: The values expected to appear in @p buffer at
 *                           @p offset
 * @param[in] data_len:      Size of @p expected_data
 * @param[in] line:          Line number of the assertion
 */
static void _log_serialize_validate_buffer(uint8_t const * buffer,
                                           size_t * offset,
                                           void const * expected_data,
                                           size_t data_len,
                                           uint32_t line);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void setUp(void)
{
    log_serialize_init();
}

/* --- TESTS ---------------------------------------------------------------- */

void test_log_serialize_should_include_mandatory_fields(void)
{
    uint8_t type = TYPE_STATE_CHANGE;
    uint8_t subtype = 0x34;
    uint16_t flags = LOG_NO_FLAGS;
    log_entry_t entry = {
        .type    = type,
        .subtype = subtype,
        .flags   = flags,
    };

    uint64_t timestamp = 8202382;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, 0, 0, 0);

    size_t expected_len = ENTRY_MINIMAL_LEN;
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);
}

void test_log_serialize_should_include_program_counter_when_pc_flag_set(void)
{
    uint8_t type = TYPE_EXCEPTION;
    uint8_t subtype = SUBTYPE_BUS_FAULT_EXCEPTION;
    uint16_t flags = LOG_FLAG_PC;
    log_entry_t entry = {
        .type    = type,
        .subtype = subtype,
        .flags   = flags,
    };

    uint64_t timestamp = 929323202;
    uint32_t pc = 0x08004DCC;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, pc, 0, 0);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_PC_LEN;
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &pc, ENTRY_PC_LEN);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_include_stack_pointer_when_sp_flag_set(void)
{
    uint8_t type = TYPE_EXCEPTION;
    uint8_t subtype = SUBTYPE_BUS_FAULT_EXCEPTION;
    uint16_t flags = LOG_FLAG_SP;
    log_entry_t entry = {
        .type    = type,
        .subtype = subtype,
        .flags   = flags,
    };

    uint64_t timestamp = 89898998;
    uint32_t sp = 0x2001294A;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, 0, sp, 0);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_SP_LEN;
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &sp, ENTRY_SP_LEN);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_include_stack_usage_when_su_flag_set(void)
{
    uint8_t type = TYPE_EXCEPTION;
    uint8_t subtype = SUBTYPE_BUS_FAULT_EXCEPTION;
    uint16_t flags = LOG_FLAG_SU;
    log_entry_t entry = {
        .type    = type,
        .subtype = subtype,
        .flags   = flags,
    };

    uint64_t timestamp = 7213223;
    uint32_t su = 934;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, 0, 0, su);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_SU_LEN;
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &su, ENTRY_SP_LEN);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_include_all_state_fields_when_all_state_flags_set(void)
{
    uint8_t type = TYPE_EXCEPTION;
    uint8_t subtype = SUBTYPE_BUS_FAULT_EXCEPTION;
    uint16_t flags = LOG_FLAG_PC | LOG_FLAG_SP | LOG_FLAG_SU;
    log_entry_t entry = {
        .type    = type,
        .subtype = subtype,
        .flags   = flags,
    };

    uint64_t timestamp = 47294382;
    uint32_t pc = 0x08000100;
    uint32_t sp = 0x20001888;
    uint32_t su = 1016;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, pc, sp, su);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_PC_LEN +
                          ENTRY_SP_LEN +
                          ENTRY_SU_LEN;
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    _log_serialize_validate_value_at_offset(buffer, &offset, &pc, ENTRY_PC_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset, &sp, ENTRY_SP_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset, &su, ENTRY_SU_LEN);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_include_descriptor_string_when_dsc_flag_set(void)
{
    uint8_t type = TYPE_RESET;
    uint8_t subtype = SUBTYPE_SOFTWARE_RESET;
    char const * descriptor = "abcdefgh";
    uint16_t flags = LOG_FLAG_DSC;
    log_entry_t entry = {
        .type              = type,
        .subtype           = subtype,
        .flags             = flags,
        .descriptor_string = descriptor,
    };

    TEST_ASSERT_EQUAL_MESSAGE(0, strlen(descriptor) % sizeof(uint32_t),
                              "Descriptor should be aligned for this test");

    uint64_t timestamp = 111111;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, 0, 0, 0);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_DSC_HEADER_LEN +
                          strlen(descriptor);
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    uint32_t expected_header = strlen(descriptor);
    _log_serialize_validate_value_at_offset(buffer,
                                            &offset,
                                            &expected_header,
                                            ENTRY_DSC_HEADER_LEN);
    _log_serialize_validate_value_at_offset(buffer,
                                            &offset,
                                            descriptor,
                                            strlen(descriptor));

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_include_padding_when_descriptor_misaligned(void)
{
    uint8_t type = TYPE_RESET;
    uint8_t subtype = SUBTYPE_SOFTWARE_RESET;
    char const * descriptor = "abcdefghij";
    uint16_t flags = LOG_FLAG_DSC;
    log_entry_t entry = {
        .type              = type,
        .subtype           = subtype,
        .flags             = flags,
        .descriptor_string = descriptor,
    };

    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, strlen(descriptor) % sizeof(uint32_t),
                                  "Descriptor should be misaligned for this test");

    uint32_t padding_bytes = sizeof(uint32_t) -
                            (strlen(descriptor) % sizeof(uint32_t));

    uint64_t timestamp = 46129432;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, 0, 0, 0);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_DSC_HEADER_LEN +
                          strlen(descriptor) +
                          padding_bytes;
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    uint32_t header = (padding_bytes << PADDING_SHIFT) |
                      (strlen(descriptor) + padding_bytes);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &header, ENTRY_DSC_HEADER_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            descriptor, strlen(descriptor));

    uint8_t const padding_values[4] = { 0, 0, 0, 0 };
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            padding_values, padding_bytes);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_include_binary_data_when_bin_flag_set(void)
{
    uint8_t type = TYPE_RESET;
    uint8_t subtype = SUBTYPE_SOFTWARE_RESET;
    struct {
        uint32_t x;
        uint32_t y;
    } an_object = {0, 1};
    uint32_t n_data = 1;
    uint8_t bin_data_type = 0x32;
    uint16_t flags = LOG_FLAG_BIN;
    log_entry_t entry = {
        .type              = type,
        .subtype           = subtype,
        .flags             = flags,
        .binary_data_count = n_data,
        .binary_data[0]    = {
            .type = bin_data_type,
            .len  = sizeof(an_object),
            .data = &an_object,
        },
    };

    TEST_ASSERT_EQUAL_MESSAGE(0, sizeof(an_object) % sizeof(uint32_t),
                              "Binary data should be aligned for this test");

    uint64_t timestamp = 111111;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, 0, 0, 0);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_BIN_COUNT_LEN +
                          ENTRY_BIN_HEADER_LEN +
                          sizeof(an_object);
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &n_data, ENTRY_BIN_COUNT_LEN);

    uint32_t header = (bin_data_type << DATA_TYPE_SHIFT) | sizeof(an_object);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &header, ENTRY_BIN_HEADER_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &an_object, sizeof(an_object));

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_include_multiple_binary_data(void)
{
    uint8_t type = TYPE_RUNTIME_ERROR;
    uint8_t subtype = 0x01;
    struct {
        uint32_t x;
        uint32_t y;
    } first_object = {1, 2};
    struct {
        uint32_t a;
        uint32_t b;
        uint32_t c;
    } second_object = {2, 3, 4};
    uint8_t first_data_type = 0x32;
    uint8_t second_data_type = 0x88;
    uint32_t n_data = 2;
    uint16_t flags = LOG_FLAG_BIN;
    log_entry_t entry = {
        .type              = type,
        .subtype           = subtype,
        .flags             = flags,
        .binary_data_count = n_data,
        .binary_data[0]    = {
            .type = first_data_type,
            .len  = sizeof(first_object),
            .data = &first_object,
        },
        .binary_data[1]    = {
            .type = second_data_type,
            .len  = sizeof(second_object),
            .data = &second_object,
        },
    };

    TEST_ASSERT_EQUAL_MESSAGE(0, sizeof(first_object) % sizeof(uint32_t),
                              "Binary data should be aligned for this test");
    TEST_ASSERT_EQUAL_MESSAGE(0, sizeof(second_object) % sizeof(uint32_t),
                              "Binary data should be aligned for this test");

    uint64_t timestamp = 32380232000000;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, 0, 0, 0);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_BIN_COUNT_LEN +
                          ENTRY_BIN_HEADER_LEN +
                          sizeof(first_object) +
                          ENTRY_BIN_HEADER_LEN +
                          sizeof(second_object);
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);
    size_t offset = ENTRY_MINIMAL_LEN;
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &n_data, ENTRY_BIN_COUNT_LEN);

    uint32_t header = (first_data_type << DATA_TYPE_SHIFT) | sizeof(first_object);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &header, ENTRY_BIN_HEADER_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &first_object, sizeof(first_object));

    header = (second_data_type << DATA_TYPE_SHIFT) | sizeof(second_object);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &header, ENTRY_BIN_HEADER_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &second_object, sizeof(second_object));

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_pad_binary_data_when_misaligned(void)
{
    uint8_t type = TYPE_RESET;
    uint8_t subtype = SUBTYPE_SOFTWARE_RESET;

    #pragma pack(push, 1)
    struct {
        uint32_t x;
        uint8_t y;
    } an_object = {1, 255};
    #pragma pack(pop)

    uint32_t n_data = 1;
    uint8_t bin_data_type = 0x55;
    uint16_t flags = LOG_FLAG_BIN;
    log_entry_t entry = {
        .type              = type,
        .subtype           = subtype,
        .flags             = flags,
        .binary_data_count = n_data,
        .binary_data[0]    = {
            .type = bin_data_type,
            .len  = sizeof(an_object),
            .data = &an_object,
        },
    };

    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, sizeof(an_object) % sizeof(uint32_t),
                                  "Binary data should not be aligned for this test");

    uint32_t padding_bytes = 4 - (sizeof(an_object) % sizeof(uint32_t));

    uint64_t timestamp = 888888888;
    uint8_t buffer[LOG_BUFFER_LEN];

    size_t entry_len = log_serialize(buffer, &entry, timestamp, 0, 0, 0);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_BIN_COUNT_LEN +
                          ENTRY_BIN_HEADER_LEN +
                          sizeof(an_object) +
                          padding_bytes;
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &n_data, ENTRY_BIN_COUNT_LEN);

    uint32_t header = (padding_bytes << PADDING_SHIFT) |
                      (bin_data_type << DATA_TYPE_SHIFT) |
                      (sizeof(an_object) + padding_bytes);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &header, ENTRY_BIN_HEADER_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &an_object, sizeof(an_object));

    uint8_t const padding_values[4] = { 0, 0, 0, 0 };
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &padding_values, padding_bytes);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

void test_log_serialize_should_serialize_everything(void)
{
    uint8_t type = TYPE_RESET;
    uint8_t subtype = SUBTYPE_SOFTWARE_RESET;
    char const * descriptor = "The system reset itself";
    uint32_t extra_desc_len = strlen(descriptor) % 4;
    uint32_t desc_padding_bytes = extra_desc_len == 0 ? 0
                                                      : 4 - extra_desc_len;

    uint16_t flags = LOG_FLAGS_MASK;
    log_entry_t entry = {
        .type              = type,
        .subtype           = subtype,
        .flags             = flags,
        .descriptor_string = descriptor,
        .binary_data_count = LOG_MAX_BINARY_DATA,
    };

    uint64_t binary_values[LOG_MAX_BINARY_DATA];
    uint32_t i;
    for (i = 0; i < LOG_MAX_BINARY_DATA; i++) {
        binary_values[i] = i + 1;
        entry.binary_data[i].data = &(binary_values[i]);
        entry.binary_data[i].len  = sizeof(binary_values[i]);
        entry.binary_data[i].type = i;
    }

    uint32_t timestamp = 8202382;
    uint32_t pc = 0x08001444;
    uint32_t sp = 0x20011100;
    uint32_t su = 123282;

    uint8_t buffer[LOG_BUFFER_LEN];
    uint32_t entry_len = log_serialize(buffer, &entry, timestamp, pc, sp, su);

    size_t expected_len = ENTRY_MINIMAL_LEN +
                          ENTRY_PC_LEN +
                          ENTRY_SP_LEN +
                          ENTRY_SU_LEN +
                          ENTRY_DSC_HEADER_LEN +
                          strlen(descriptor) +
                          desc_padding_bytes +
                          ENTRY_BIN_COUNT_LEN +
                          LOG_MAX_BINARY_DATA *
                          (ENTRY_BIN_HEADER_LEN +
                           sizeof(*binary_values));
    TEST_ASSERT_EQUAL_UINT64(expected_len, entry_len);
    _log_serialize_validate_mandatory_fields(buffer,
                                             expected_len,
                                             timestamp,
                                             flags,
                                             type,
                                             subtype);

    size_t offset = ENTRY_MINIMAL_LEN;
    _log_serialize_validate_value_at_offset(buffer, &offset, &pc, ENTRY_PC_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset, &sp, ENTRY_SP_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset, &su, ENTRY_SU_LEN);

    uint32_t header = (desc_padding_bytes << PADDING_SHIFT) |
                      (strlen(descriptor) + desc_padding_bytes);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &header, ENTRY_DSC_HEADER_LEN);
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            descriptor, strlen(descriptor));

    uint8_t const padding_values[4] = { 0, 0, 0, 0 };
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            padding_values, desc_padding_bytes);

    uint32_t bin_count = LOG_MAX_BINARY_DATA;
    _log_serialize_validate_value_at_offset(buffer, &offset,
                                            &bin_count, ENTRY_BIN_COUNT_LEN);

    for (i = 0; i < LOG_MAX_BINARY_DATA; i++) {
        uint32_t header = (i << 16) | sizeof(*binary_values);
        _log_serialize_validate_value_at_offset(buffer, &offset,
                                                &header, ENTRY_BIN_HEADER_LEN);

        uint64_t expected_data = i + 1;
        _log_serialize_validate_value_at_offset(buffer, &offset,
                                                &expected_data, sizeof(*binary_values));
    }

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected_len, offset,
                                     "test not aligned to expected fields");
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static uint32_t _log_serialize_get_length(uint8_t const * buffer)
{
    return VALUE_AT_OFFSET(buffer, LENGTH_OFFSET_BYTES, uint32_t);
}

static uint64_t _log_serialize_get_timestamp(uint8_t const * buffer)
{
    return VALUE_AT_OFFSET(buffer, TIMESTAMP_OFFSET_BYTES, uint64_t);
}

static uint16_t _log_serialize_get_flags(uint8_t const * buffer)
{
    return VALUE_AT_OFFSET(buffer, FLAGS_OFFSET_BYTES, uint16_t);
}

static uint8_t _log_serialize_get_type(uint8_t const * buffer)
{
    return VALUE_AT_OFFSET(buffer, TYPE_OFFSET_BYTES, uint8_t);
}

static uint8_t _log_serialize_get_subtype(uint8_t const * buffer)
{
    return VALUE_AT_OFFSET(buffer, SUBTYPE_OFFSET_BYTES, uint8_t);
}

static void _log_serialize_validate_mandatory_fields(uint8_t const * buffer,
                                                     uint32_t length,
                                                     uint64_t timestamp,
                                                     uint16_t flags,
                                                     uint8_t type,
                                                     uint8_t subtype)
{
    TEST_ASSERT_EQUAL_UINT32(length,    _log_serialize_get_length(buffer));
    TEST_ASSERT_EQUAL_UINT64(timestamp, _log_serialize_get_timestamp(buffer));
    TEST_ASSERT_EQUAL_HEX16(flags,      _log_serialize_get_flags(buffer));
    TEST_ASSERT_EQUAL_HEX8(type,        _log_serialize_get_type(buffer));
    TEST_ASSERT_EQUAL_HEX8(subtype,     _log_serialize_get_subtype(buffer));
}

static void _log_serialize_validate_buffer(uint8_t const * buffer,
                                           size_t * offset,
                                           void const * expected_data,
                                           size_t data_len,
                                           uint32_t line)
{
    void const * data = PTR_AT_OFFSET(buffer, *offset, void);

    UNITY_TEST_ASSERT_EQUAL_MEMORY(expected_data, data, data_len, line, NULL);

    *offset += data_len;
}

/** @} addtogroup TEST_LOG_SERIALIZE */
