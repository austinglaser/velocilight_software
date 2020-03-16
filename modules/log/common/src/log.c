/**@file    log.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Logger Source
 *
 * @addtogroup LOG
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log.h"

#include "eeprom.h"
#include "ensure.h"
#include "log_memory.h"
#include "log_serialize.h"
#include "memory_pool.h"
#include "project_info.h"
#include "system_info.h"
#include "util.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

#if !defined(LOG_N_BUFFERS) || defined(__DOXYGEN__)
/** Number of log buffers available */
#define LOG_N_BUFFERS       4
#endif

#if LOG_N_BUFFERS < 1
#error Logger needs at least one buffer
#endif

/* --- PRIVATE DATATYPES ---------------------------------------------------- */

/** Structure holding an instance of a log */
struct _log_t {
    /** The log's memory manager */
    log_memory_t lm;
    /** The log's memory pool */
    mem_pool_t mp;
    /** Buffers handed out by @ref mp */
    uint8_t mp_buffers[LOG_BUFFER_LEN * LOG_N_BUFFERS];
};

/** Convenience typedef for log state */
typedef struct _log_t log_t;

/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Determines whether @p entry has a valid type
 *
 * @param[in] entry: The entry to validate
 *
 * @return true if the type field in @p entry is valid, false otherwise
 */
static bool _log_entry_has_valid_type(log_entry_t const * entry);

/** Determines whether @p entry has a valid subtype
 *
 * @param[in] entry: The entry to validate
 *
 * @return true if the subtype field in @p entry is valid
 */
static bool _log_entry_has_valid_subtype(log_entry_t const * entry);

/** Determines whether @p entry has a valid flags field
 *
 * @param[in] entry: The entry to validate
 *
 * @return true if the flags field in @p entry is valid, false otherwise
 */
static bool _log_entry_has_valid_flags(log_entry_t const * entry);

/** Determines whether @p entry has a valid descriptor string field
 *
 * @param[in] entry: The entry to validate
 *
 * @return true if the descriptor string field in @p entry is valid, false otherwise
 */
static bool _log_entry_has_valid_descriptor_string(log_entry_t const * entry);

/** Determines whether @p entry has a valid set of binary data
 *
 * @param[in] entry: The entry to validate
 *
 * @return true if all binary data fields in @p entry are valid, false otherwise
 */
static bool _log_entry_has_valid_binary_data(log_entry_t const * entry);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

/** Log state instance */
static log_t log;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

int log_init(eeprom_t * e, project_info_t const * pi)
{
    memory_pool_init(&(log.mp), log.mp_buffers, LOG_N_BUFFERS, LOG_BUFFER_LEN);

    log_serialize_init();

    int err;
    err = log_memory_init(&(log.lm), e, &(log.mp), pi);
    if (err != 0) {
        return err;
    }

    return 0;
}

void log_write(log_entry_t const * entry)
{
    ensure(entry != NULL);
    ensure(_log_entry_has_valid_type(entry));
    ensure(_log_entry_has_valid_subtype(entry));
    ensure(_log_entry_has_valid_flags(entry));
    ensure(_log_entry_has_valid_descriptor_string(entry));
    ensure(_log_entry_has_valid_binary_data(entry));

    uint8_t * entry_serialized = memory_pool_alloc(&(log.mp));
    if (entry_serialized == NULL) {
        /* TODO: We might not want to silently pass here */
        return;
    }

    uint64_t timestamp = system_info_get_time();

    uint32_t program_counter = 0;
    if (entry->flags & LOG_FLAG_PC) {
        program_counter = system_info_get_lr();
    }

    uint32_t stack_pointer = 0;
    if (entry->flags & LOG_FLAG_SP) {
        stack_pointer = system_info_get_sp();
    }

    uint32_t stack_used = 0;
    if (entry->flags & LOG_FLAG_SU) {
        stack_used = system_info_get_stack_used();
    }

    size_t entry_size = log_serialize(entry_serialized,
                                      entry,
                                      timestamp,
                                      program_counter,
                                      stack_pointer,
                                      stack_used);

    if (entry_size > 0) {
        log_memory_write(&(log.lm), entry_serialized);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static bool _log_entry_has_valid_type(log_entry_t const * entry)
{
    return entry->type <= MAX_TYPE;
}

static bool _log_entry_has_valid_subtype(log_entry_t const * entry)
{
    if (entry->type <= MAX_CUSTOM_TYPE) {
        return entry->subtype <= MAX_CUSTOM_TYPE_SUBTYPE;
    }

    switch (entry->type) {
    case TYPE_RESET:
        return entry->subtype <= MAX_RESET_SUBTYPE;

    case TYPE_EXCEPTION:
        return entry->subtype <= MAX_EXCEPTION_SUBTYPE;

    case TYPE_RUNTIME_ERROR:
        return entry->subtype <= MAX_RUNTIME_ERROR_SUBTYPE;

    case TYPE_STATE_CHANGE:
        return entry->subtype <= MAX_STATE_CHANGE_SUBTYPE;

    default:
        return false;
    }
}

static bool _log_entry_has_valid_flags(log_entry_t const * entry)
{
    return (entry->flags & ~LOG_FLAGS_MASK) == UINT16_C(0);
}

static bool _log_entry_has_valid_descriptor_string(log_entry_t const * entry)
{
    if ((entry->flags & LOG_FLAG_DSC) == 0) {
        return true;
    }

    return entry->descriptor_string != NULL;
}

static bool _log_entry_has_valid_binary_data(log_entry_t const * entry)
{
    if ((entry->flags & LOG_FLAG_BIN) == 0) {
        return true;
    }

    if (entry->binary_data_count == 0 ||
        entry->binary_data_count > LOG_MAX_BINARY_DATA) {
        return false;
    }

    uint32_t i;
    for (i = 0; i < entry->binary_data_count; i++) {
        if (entry->binary_data[i].len == 0    ||
            entry->binary_data[i].data == NULL) {
            return false;
        }
    }

    return true;
}

/** @} addtogroup LOG */
