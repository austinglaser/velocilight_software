/**@file    log_memory_eeprom_test_util.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogMemoryEepromTestUtil Source
 *
 * @addtogroup LOG_MEMORY_EEPROM_TEST_UTIL
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_memory_eeprom_test_util.h"

#include "eeprom.h"
#include "project_info.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */

/** Retrieve a pointer to EEPROM memory at the given offset
 *
 * Returns a value of type 'type *'
 *
 * @param[in] e:        The fake eeprom to pull from
 * @param[in] address:  The address (offset) to look at
 * @param[in] type:     Type to cast to
 */
#define EEPROM_MEMORY_AS_TYPE(e, address, type) \
            ((type *)((e)->memory + address))

/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Gets the combined values of the project id, and dirty/!stable flags */
static uint16_t _log_memory_eeprom_helper_get_maj_flags(eeprom_t const * e);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void log_memory_eeprom_helper_fill_project_info(project_info_t * pi)
{
    static uint8_t const example_git_hash[20] = { 0x7a, 0x96, 0x20, 0xd7,
                                                  0xbf, 0x90, 0x18, 0x16,
                                                  0x7e, 0xce, 0xab, 0xb8,
                                                  0x9a, 0x42, 0xfd, 0xfa,
                                                  0x40, 0x90, 0x8e, 0xdd };

    memcpy(pi->git_hash, example_git_hash, sizeof(example_git_hash));
    pi->build_timestamp = 1463532510;
    pi->repo_dirty      = false;
    pi->stable_version  = true;
    pi->project_id      = 6;
    pi->client_id       = 99;
    pi->version_major   = 1;
    pi->version_minor   = 2;
    pi->version_patch   = 12;
}

uint32_t log_memory_eeprom_helper_get_magic_number(eeprom_t const * e)
{
    return log_memory_eeprom_helper_get_value(e, MAGIC_NUMBER_ADDRESS);
}

uint8_t const * log_memory_eeprom_helper_get_git_hash(eeprom_t const * e)
{
    return EEPROM_MEMORY_AS_TYPE(e, GIT_HASH_ADDRESS, uint8_t);
}

uint64_t log_memory_eeprom_helper_get_timestamp(eeprom_t const * e)
{
    return *(EEPROM_MEMORY_AS_TYPE(e, TIMESTAMP_ADDRESS, uint64_t));
}

uint8_t log_memory_eeprom_helper_get_patch_version(eeprom_t const * e)
{
    return *(EEPROM_MEMORY_AS_TYPE(e, VERSION_PATCH_ADDRESS, uint8_t));
}

uint8_t log_memory_eeprom_helper_get_minor_version(eeprom_t const * e)
{
    return *(EEPROM_MEMORY_AS_TYPE(e, VERSION_MINOR_ADDRESS, uint8_t));
}

uint16_t log_memory_eeprom_helper_get_major_version(eeprom_t const * e)
{
    return _log_memory_eeprom_helper_get_maj_flags(e) & VERSION_MAJOR_MASK;
}

uint16_t log_memory_eeprom_helper_get_client_id(eeprom_t const * e)
{
    return *(EEPROM_MEMORY_AS_TYPE(e, CLIENT_ID_ADDRESS, uint16_t));
}

uint16_t log_memory_eeprom_helper_get_project_id(eeprom_t const * e)
{
    return *(EEPROM_MEMORY_AS_TYPE(e, PROJECT_ID_ADDRESS, uint16_t));
}

bool log_memory_eeprom_helper_get_dirty_flag(eeprom_t const * e)
{
    return _log_memory_eeprom_helper_get_maj_flags(e) & FLAG_DIRTY_MASK;
}

bool log_memory_eeprom_helper_get_not_stable_flag(eeprom_t const * e)
{
    return _log_memory_eeprom_helper_get_maj_flags(e) & FLAG_NOT_STABLE_MASK;
}

uint16_t log_memory_eeprom_helper_get_reserved_flags(eeprom_t const * e)
{
    return _log_memory_eeprom_helper_get_maj_flags(e) & FLAGS_RESERVED_MASK;
}

uint32_t log_memory_eeprom_helper_get_log_start(eeprom_t const * e)
{
    return log_memory_eeprom_helper_get_value(e, LOG_START_ADDRESS);
}

uint32_t log_memory_eeprom_helper_get_log_end(eeprom_t const * e)
{
    return log_memory_eeprom_helper_get_value(e, LOG_END_ADDRESS);
}

uint8_t const * log_memory_eeprom_helper_get_reserved_header(eeprom_t const * e)
{
    return EEPROM_MEMORY_AS_TYPE(e, HEADER_RESERVED_ADDRESS, uint8_t);
}

uint32_t log_memory_eeprom_helper_get_head(eeprom_t const * e)
{
    uint32_t log_start = log_memory_eeprom_helper_get_log_start(e);
    return log_memory_eeprom_helper_get_value(e, log_start + HEAD_OFFSET);
}

uint32_t log_memory_eeprom_helper_get_tail(eeprom_t const * e)
{
    uint32_t log_start = log_memory_eeprom_helper_get_log_start(e);
    return log_memory_eeprom_helper_get_value(e, log_start + TAIL_OFFSET);
}

uint32_t log_memory_eeprom_helper_get_value(eeprom_t const * e,
                                            uint32_t addr)
{
    return *(EEPROM_MEMORY_AS_TYPE(e, addr, uint32_t));
}

void log_memory_eeprom_helper_set_head(eeprom_t const * e,
                                       uint32_t head)
{
    uint32_t log_start = log_memory_eeprom_helper_get_log_start(e);
    log_memory_eeprom_helper_set_value(e, log_start + HEAD_OFFSET, head);
}

void log_memory_eeprom_helper_set_tail(eeprom_t const * e,
                                       uint32_t tail)
{
    uint32_t log_start = log_memory_eeprom_helper_get_log_start(e);
    log_memory_eeprom_helper_set_value(e, log_start + TAIL_OFFSET, tail);
}

uint8_t const * log_memory_eeprom_helper_get_reserved_bookkeeping(eeprom_t const * e)
{
    uint32_t log_start = log_memory_eeprom_helper_get_log_start(e);
    return EEPROM_MEMORY_AS_TYPE(e, log_start + BK_RESERVED_OFFSET, uint8_t);
}

void log_memory_eeprom_helper_set_value(eeprom_t const * e,
                                        uint32_t addr,
                                        uint32_t value)
{
    uint32_t * valuep = EEPROM_MEMORY_AS_TYPE(e, addr, uint32_t);

    *valuep = value;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static uint16_t _log_memory_eeprom_helper_get_maj_flags(eeprom_t const * e)
{
    return *(EEPROM_MEMORY_AS_TYPE(e, VERSION_MAJOR_FLAGS_ADDRESS, uint16_t));
}

/** @} addtogroup LOG_MEMORY_EEPROM_TEST_UTIL */
