/**@file    log_serialize.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogSerialize Source
 *
 * @addtogroup LOG_SERIALIZE
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_serialize.h"

#include "util.h"
#include "CException.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

/** Length of the mandatory fields in an entry */
#define LOG_SERIALIZE_MANDATORY_FIELDS_LENGTH \
    (sizeof(log_serialize_mandatory_fields_t))

/** Exception thrown when the buffer overflows */
#define LOG_SERIALIZE_BUFFER_OVERFLOW       0xBAADBEEF

/* --- PRIVATE DATATYPES ---------------------------------------------------- */

/** Mandatory fields for a log entry */
#pragma pack(push, 1)
struct _log_serialize_mandatory_fields {
    uint32_t length;    /**< Total entry length */
    uint64_t timestamp; /**< Timestamp of the entry */
    uint8_t  subtype;   /**< Entry subtype */
    uint8_t  type;      /**< Entry type */
    uint16_t flags;     /**< Entry flags */
};
#pragma pack(pop)

/** Convenience typedef for mandatory fields */
typedef struct _log_serialize_mandatory_fields
        log_serialize_mandatory_fields_t;

/** A full serialized log entry */
#pragma pack(push, 1)
struct _log_serialize_entry {
    log_serialize_mandatory_fields_t header; /**< The entry header */
    uint8_t body[0];                         /**< Optional fields */
};
#pragma pack(pop)

/** Convenience typedef for a serialized entry */
typedef struct _log_serialize_entry log_serialize_entry_t;

/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Appends optional fields based on the raw_entry flags
 *
 * @param[in,out] entry:        The partially-serialized entry
 * @param[in] raw_entry:        A log entry structure for serializaton
 * @param[in] program_counter:  Value for the program counter field, if
 *                              LOG_FLAG_PC is set in @p raw_entry
 * @param[in] stack_pointer:    Value for the stack pointer field, if
 *                              LOG_FLAG_SP is set in @P raw_entry
 * @param[in] stack_usage:      Value for the stack usage field, if
 *                              LOG_FLAG_SU is set in @P raw_entry
 *
 * @return 0 on success, negative on failure (buffer overflow).
 */
static int _log_serialize_add_optional_fields(log_serialize_entry_t * entry,
                                              log_entry_t const * raw_entry,
                                              uint32_t program_counter,
                                              uint32_t stack_pointer,
                                              uint32_t stack_usage);

/** Appends a value which can be treated as a unsigned 4-byte number to the end
 * of the entry
 *
 * @param[in,out] entry:    A partially-serialized entry for appending
 * @param[in] value:        The value to append
 *
 * @return 0 on success, negative on failure (buffer overflow).
 */
static int _log_serialize_append_uint32(log_serialize_entry_t * entry,
                                        uint32_t value);

/** Appends a 'long' (variable-length) field to the entry
 *
 * If @p len is not a multiple of 4, adds zero-padding bytes for alignment
 *
 * Includes the number of padding bytes, the (optional) data type designator,
 * and the total (with padding) length of the field before the padded data.
 *
 * @param[in,out] entry:    A partially serialized entry
 * @param[in] data:         The data to be appended
 * @param[in] len:          The number of valid bytes pointed to by @p data
 * @param[in] type:         An optional type designator. Can be zero
 *
 * @return 0 on success, negative on failure (buffer overflow).
 */
static int _log_serialize_append_long_field(log_serialize_entry_t * entry,
                                            void const * data,
                                            size_t len,
                                            uint8_t type);

/** Add a value to a partially serialized log entry
 *
 * The buffer's length is incremented by @p value_len
 *
 * @param[in,out] entry: The entry for appending
 * @param[in] value:     Pointer to the data for copying
 * @param[in] value_len: The size of @p value
 *
 * @return 0 on success, negative on failure (buffer overflow).
 */
static int _log_serialize_append_value(log_serialize_entry_t * entry,
                                       void const * value,
                                       size_t value_len);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void log_serialize_init(void)
{
}

size_t log_serialize(uint8_t * buf,
                     log_entry_t const * raw_entry,
                     uint64_t timestamp,
                     uint32_t program_counter,
                     uint32_t stack_pointer,
                     uint32_t stack_usage)
{
    log_serialize_entry_t * entry = (log_serialize_entry_t *) buf;

    entry->header.length    = LOG_SERIALIZE_MANDATORY_FIELDS_LENGTH;
    entry->header.timestamp = timestamp;
    entry->header.flags     = raw_entry->flags;
    entry->header.type      = raw_entry->type;
    entry->header.subtype   = raw_entry->subtype;

    int err = _log_serialize_add_optional_fields(entry,
                                                 raw_entry,
                                                 program_counter,
                                                 stack_pointer,
                                                 stack_usage);
    if (err != 0) {
        memset(buf, 0, LOG_BUFFER_LEN);
        return 0;
    }

    return entry->header.length;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static int _log_serialize_add_optional_fields(log_serialize_entry_t * entry,
                                              log_entry_t const * raw_entry,
                                              uint32_t program_counter,
                                              uint32_t stack_pointer,
                                              uint32_t stack_usage)
{
    int err;
    if (raw_entry->flags & LOG_FLAG_PC) {
        err = _log_serialize_append_uint32(entry, program_counter);
        if (err != 0) {
            return err;
        }
    }
    if (raw_entry->flags & LOG_FLAG_SP) {
        err = _log_serialize_append_uint32(entry, stack_pointer);
        if (err != 0) {
            return err;
        }
    }
    if (raw_entry->flags & LOG_FLAG_SU) {
        err = _log_serialize_append_uint32(entry, stack_usage);
        if (err != 0) {
            return err;
        }
    }
    if (raw_entry->flags & LOG_FLAG_DSC) {
        char const * desc = raw_entry->descriptor_string;
        uint16_t desc_len = strlen(desc);
        err = _log_serialize_append_long_field(entry, desc, desc_len, 0x00);
        if (err != 0) {
            return err;
        }
    }
    if (raw_entry->flags & LOG_FLAG_BIN) {
        uint32_t count = raw_entry->binary_data_count;
        err = _log_serialize_append_uint32(entry, count);
        if (err != 0) {
            return err;
        }
        uint32_t i;
        for (i = 0; i < count; i++) {
            log_binary_data_t const * bin_data = &(raw_entry->binary_data[i]);
            void const * data = bin_data->data;
            uint16_t len      = bin_data->len;
            uint8_t type      = bin_data->type;
            err = _log_serialize_append_long_field(entry, data, len, type);
            if (err != 0) {
                return err;
            }
        }
    }

    return 0;
}

static int _log_serialize_append_uint32(log_serialize_entry_t * entry,
                                        uint32_t value)
{
    return _log_serialize_append_value(entry, &value, sizeof(uint32_t));
}

static int _log_serialize_append_long_field(log_serialize_entry_t * entry,
                                            void const * data,
                                            size_t len,
                                            uint8_t type)
{
    uint8_t extra_bytes = len % 4;
    uint8_t pad_bytes = extra_bytes == 0 ? 0
                                         : 4 - extra_bytes;
    uint16_t full_length = len + pad_bytes;
    uint32_t pad_values = 0x00000000;

    int err;
    err = _log_serialize_append_value(entry, &full_length, sizeof(uint16_t));
    if (err != 0) {
        return err;
    }

    err = _log_serialize_append_value(entry, &type, sizeof(uint8_t));
    if (err != 0) {
        return err;
    }

    err = _log_serialize_append_value(entry, &pad_bytes, sizeof(uint8_t));
    if (err != 0) {
        return -1;
    }

    err = _log_serialize_append_value(entry, data, len);
    if (err != 0) {
        return -1;
    }

    err = _log_serialize_append_value(entry, &pad_values, pad_bytes);
    if (err != 0) {
        return -1;
    }

    return 0;
}

static int _log_serialize_append_value(log_serialize_entry_t * entry,
                                       void const * value,
                                       size_t value_len)
{
    size_t offset = entry->header.length -
                    LOG_SERIALIZE_MANDATORY_FIELDS_LENGTH;

    size_t new_length = entry->header.length + value_len;

    if (new_length >= LOG_BUFFER_LEN) {
        return -1;
    }

    memcpy(entry->body + offset, value, value_len);
    entry->header.length = new_length;

    return 0;
}

/** @} addtogroup LOG_SERIALIZE */
