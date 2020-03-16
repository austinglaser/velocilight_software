/**@file    log_memory_eeprom.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogMemoryEeprom Source
 *
 * @addtogroup LOG_MEMORY_EEPROM
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log.h"
#include "log_memory_eeprom.h"

#include "eeprom.h"
#include "ensure.h"
#include "project_info.h"
#include "util.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- CONFIGURAITON VALIDATION --------------------------------------------- */

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#   error   This implementation currently assumes a little-endian platform
#endif

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

/** Address in EEPROM at which the header resides */
#define HEADER_ADDRESS      0

/** Magic number used to identify that a log is valid */
#define LOG_MAGIC_NUMBER    ((uint32_t) ((0x6C6F6700) | LOG_STANDARD_VERSION))

/** Mask for major version in @ref log_header_t::version_major_and_flags */
#define LOG_VERSION_MAJOR_MASK    ((uint16_t) 0x0FFF)

/** Mask for dirty bit in @ref log_header_t::version_major_and_flags */
#define LOG_BUILD_FLAG_DIRTY      ((uint16_t) 0x8000)

/** Mask for !stable bit in @ref log_header_t::version_major_and_flags */
#define LOG_BUILD_FLAG_NOT_STABLE ((uint16_t) 0x4000)

/** Mask for reserved bits in log_header_t::version_major_and_flags */
#define LOG_BUILD_FLAGS_RESERVED  ((uint16_t) 0x3000)

/** A value which can be used to determine whether an EEPROM address field is
 *  valid
 */
#define EEPROM_ADDRESS_INVALID ((uint32_t) 0xFFFFFFFF)

/* --- PRIVATE DATATYPES ---------------------------------------------------- */

/** Memory layout of the log's header
 *
 * Field order, __reservedx fields, and type are important here so this
 * structure matches the defined standard.
 */
#pragma pack(push, 1)
struct _log_header {
    uint32_t magic_number;            /**< Denotes a valid log region */
    uint8_t git_hash[20];             /**< Git hash of HEAD at build time */
    uint64_t build_timestamp;         /**< Unix time when compiled */

    uint8_t version_patch;            /**< Patch version number */
    uint8_t version_minor;            /**< Minor version number */
    uint16_t version_major_and_flags; /**< Major version and build flags */

    uint16_t project_id;              /**< Project identifier */
    uint16_t client_id;               /**< Client identifier */

    uint32_t log_start;               /**< Beginning of log region */
    uint32_t log_end;                 /**< End of log region */

    uint8_t __reserved[16];           /**< Unused bytes */
};
#pragma pack(pop)

/** Convenience typedef */
typedef struct _log_header log_header_t;

_Static_assert(sizeof(log_header_t) == 0x40,
               "Log header must be 64 bytes");

/** Memory layout of the log's bookkeeping
 *
 * Field order, __reservedx fields, and type are important here so this
 * structure matches the defined standard.
 */
#pragma pack(push, 1)
struct _log_bookkeeping {
    uint32_t head;         /**< Next insertion point */
    uint32_t tail;         /**< Next removal point */
    uint8_t __reserved[8]; /**< Unused bytes */
};
#pragma pack(pop)

/** Convenience typedef */
typedef struct _log_bookkeeping log_bookkeeping_t;

_Static_assert(sizeof(log_bookkeeping_t) == 0x10,
               "Log bookkeeping region must be 16 bytes");

/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Makes space for an entry of @p entry_length to be written to @p lm
 *
 * @param[in,out] lm:       Log memory instance
 * @param[in] entry_length: Number of bytes in @p entry
 */
static void _log_memory_eeprom_make_space_for(log_memory_t * lm,
                                              uint32_t entry_length);

/** Unconditionally writes entry to head, wrapping at the end of memory if necessary
 *
 * @warning     Doesn't verify space is available for the entry
 *
 * @param[in,out] lm:       Log memory instance
 * @param[in] entry:        Data to write
 * @param[in] entry_length: Number of bytes in @p entry
 */
static void _log_memory_eeprom_insert(log_memory_t * lm,
                                      uint8_t const * entry,
                                      uint32_t entry_length);

/** Retrieves the value in the length field of @p entry
 *
 * @param[in] entry:        Entry to examine
 *
 * @return  The value in the first four bytes of @p entry
 */
static uint32_t _log_memory_eeprom_get_entry_length(uint8_t const * entry);

/** Retrieves the current log_start EEPROM address
 *
 * @note    Uses a cached value if available
 *
 * @param[in,out] lm:           Log memory handle
 */
static uint32_t _log_memory_eeprom_get_log_start(log_memory_t * lm);

/** Retrieves the lowest address of the region in EEPROM for data storage
 *
 * @note    Uses a cached value if available
 *
 * @param[in] log_start:        The location where the log region starts
 *
 * @return  The lowest valid address where log entries can be stored
 */
static uint32_t _log_memory_eeprom_get_log_data_start(uint32_t log_start);

/** Retrieves the current log_end EEPROM address
 *
 * @note    Uses a cached value if available
 *
 * @param[in,out] lm:           Log memory handle
 */
static uint32_t _log_memory_eeprom_get_log_end(log_memory_t * lm);

/** Retrieves the current head EEPROM address
 *
 * @note    Uses a cached value if available
 *
 * @param[in,out] lm:           Log memory handle
 */
static uint32_t _log_memory_eeprom_get_head(log_memory_t * lm);

/** Retrieves the current tail EEPROM address
 *
 * @note    Uses a cached value if available
 *
 * @param[in,out] lm:           Log memory handle
 */
static uint32_t _log_memory_eeprom_get_tail(log_memory_t * lm);

/** Replaces head pointer in memory with @p head, and updates the cached value
 *
 * @param[in,out] lm:           Log memory handle
 * @param[in] head:             New head value
 */
static void _log_memory_eeprom_set_head(log_memory_t * lm, uint32_t head);

/** Replaces tail pointer in memory with @p tail, and updates the cached value
 *
 * @param[in,out] lm:           Log memory handle
 * @param[in] tail:             New tail value
 */
static void _log_memory_eeprom_set_tail(log_memory_t * lm, uint32_t tail);

/** Gets the value at @p addr, using @p cached unless it's invalid
 *
 * @param[in,out] lm:           Log memory handle
 * @param[in] addr:             Address where value resides
 * @param[in] cached:           Value to use unless invalid
 *
 * @return      @p cached if valid, otherwise EEPROM contents at @p addr
 */
static uint32_t _log_memory_eeprom_get_value(log_memory_t * lm,
                                             uint32_t addr,
                                             uint32_t cached);

/** Returns @p addr incremented by @p incr, wrapping within the valid entry region
 *
 * @param[in] addr:             Original EEPROM address
 * @param[in] incr:             Offset value
 *
 * @return      @p addr, incremented by @p incr, and wrapped
 */
static uint32_t _log_memory_eeprom_increment_addr_by(log_memory_t * lm,
                                                     uint32_t addr,
                                                     uint32_t incr);

/** Get the address of the next log entry in memory
 *
 * @param[in] lm:               Log memory handle
 * @param[in] current_entry:    Pointer to an entry
 */
static uint32_t _log_memory_eeprom_get_next_entry(log_memory_t * lm,
                                                  uint32_t current_entry);

/** Determines whether there's enough room for an entry of length @p
 *  entry_length given the provided memory state
 *
 * @param[in] lm:               Log memory handle
 * @param[in] candidate_tail:   Tail with some entries removed
 * @param[in] entry_length:     How much space is needed
 *
 * @return  true if the entry will fit, false otherwise
 */
static bool _log_memory_eeprom_has_enough_room(log_memory_t * lm,
                                               uint32_t candidate_tail,
                                               uint32_t entry_length);

/** Fills the magic_number field of @p h
 *
 * @param[out] h:   Header to fill
 * @param[in] mn:   The magic number
 */
static void _log_memory_eeprom_header_fill_magic_number(log_header_t * h,
                                                        uint32_t mn);

/** Fills the build information fields of @p h
 *
 * Fills git hash, build_timestamp, and the dirty/not_stable flags
 *
 * @param[out] h:               Header to fill
 * @param[in] pi:               Compile-time project information
 */
static void _log_memory_eeprom_header_fill_build_info(log_header_t * h,
                                                       log_memory_t const * lm);

/** Fills the project information fields of @p h
 *
 * Fills git h
 *
 * @param[out] h:               Header to fill
 * @param[in] pi:               Compile-time project information
 */
static void _log_memory_eeprom_header_fill_project_info(log_header_t * h,
                                                        log_memory_t const * lm);

/** Determine (from the EEPROM parameters) the extent of the log's memory
 *
 * Fills log_start, log_end
 *
 * @param[out] h:               Header to fill
 * @param[in] lm:               Log memory handle
 */
static void _log_memory_eeprom_header_fill_log_range(log_header_t * h,
                                                     log_memory_t const * lm);

/** Clears the reserved fields of the header
 *
 * @param[out] h:   The header to clear
 */
static void _log_memory_eeprom_header_clear_reserved(log_header_t * h);

/** Determines whether lm is valid
 *
 * @param[in] lm:               log_memory instance
 * @param[in] h:                Header that should be present
 *
 * @return false if @p h does not match the contents of memory, or if the
 *         bookkeeping region contains invalid data; otherwise true
 */
static bool _log_memory_is_valid(log_memory_t * lm,
                                 log_header_t const * h);

/** Determines whether @p h matches the current contents of the header in
 * memory
 *
 * @param[in] lm:               log_memory instance
 * @param[in] h:                Header to compare against
 *
 * @return  false if any of the data in h (including reserved regions) differs
 *          from that in the EEPROM's memory; true otherwise
 */
static bool _log_memory_header_matches(log_memory_t * lm,
                                       log_header_t const * h);

/** Determines whether the bookkeeping region in the EEPROM is valid
 *
 * @param[in] lm:               log_memory instance
 * @param[in] log_start:        EEPROM address where bookkeeping lives
 *
 * @return  false if either head or tail is outside the allowable range of
 *          EEPROM memory; true otherwise
 */
static bool _log_memory_bookkeeping_is_valid(log_memory_t * lm,
                                             uint32_t log_start);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void log_memory_eeprom_setup(log_memory_t * lm)
{
    log_header_t header;

    _log_memory_eeprom_header_fill_magic_number(&header, LOG_MAGIC_NUMBER);
    _log_memory_eeprom_header_fill_build_info(&header,   lm);
    _log_memory_eeprom_header_fill_project_info(&header, lm);
    _log_memory_eeprom_header_fill_log_range(&header,    lm);
    _log_memory_eeprom_header_clear_reserved(&header);

    log_bookkeeping_t bookkeeping = {
        .head = _log_memory_eeprom_get_log_data_start(header.log_start),
        .tail = _log_memory_eeprom_get_log_data_start(header.log_start),
    };

    if (!_log_memory_is_valid(lm, &header)) {
        eeprom_erase(lm->e);
        eeprom_write(lm->e, HEADER_ADDRESS,   &header,      sizeof(header));
        eeprom_write(lm->e, header.log_start, &bookkeeping, sizeof(bookkeeping));
    }

    lm->log_start = header.log_start;
    lm->log_end   = header.log_end;
    lm->tail      = EEPROM_ADDRESS_INVALID;
    lm->head      = EEPROM_ADDRESS_INVALID;
}

void log_memory_eeprom_write_entry(log_memory_t * lm, uint8_t const * entry)
{
    uint32_t entry_length = _log_memory_eeprom_get_entry_length(entry);
    uint32_t log_start = _log_memory_eeprom_get_log_start(lm);
    uint32_t max_entry_length = _log_memory_eeprom_get_log_end(lm) -
                                _log_memory_eeprom_get_log_data_start(log_start);
    ensure(entry_length < max_entry_length);

    _log_memory_eeprom_make_space_for(lm, entry_length);
    _log_memory_eeprom_insert(lm, entry, entry_length);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static void _log_memory_eeprom_make_space_for(log_memory_t * lm,
                                              uint32_t entry_length)
{
    uint32_t tail = _log_memory_eeprom_get_tail(lm);
    uint32_t new_tail = tail;

    while (!_log_memory_eeprom_has_enough_room(lm, new_tail, entry_length)) {
        new_tail = _log_memory_eeprom_get_next_entry(lm, new_tail);
    }

    if (new_tail != tail) {
        _log_memory_eeprom_set_tail(lm, new_tail);
    }
}

static void _log_memory_eeprom_insert(log_memory_t * lm,
                                      uint8_t const * entry,
                                      uint32_t entry_length)
{
    uint32_t head = _log_memory_eeprom_get_head(lm);
    uint32_t new_head = _log_memory_eeprom_increment_addr_by(lm,
                                                             head,
                                                             entry_length);

    bool split_entry = new_head < head;

    if (split_entry) {
        uint32_t log_start        = _log_memory_eeprom_get_log_start(lm);
        uint32_t log_end          = _log_memory_eeprom_get_log_end(lm);
        uint32_t first_half       = log_end - head;
        uint32_t second_half      = entry_length - first_half;
        uint32_t second_half_addr = _log_memory_eeprom_get_log_data_start(log_start);

        eeprom_write(lm->e, head,             entry,              first_half);
        eeprom_write(lm->e, second_half_addr, entry + first_half, second_half);
    } else {
        eeprom_write(lm->e, head, entry, entry_length);
    }

    _log_memory_eeprom_set_head(lm, new_head);
}

static uint32_t _log_memory_eeprom_get_entry_length(uint8_t const * entry)
{
    return *((uint32_t const *) entry);
}

static uint32_t _log_memory_eeprom_get_log_start(log_memory_t * lm)
{
    uint32_t log_start_addr = offsetof(log_header_t, log_start);

    lm->log_start = _log_memory_eeprom_get_value(lm, log_start_addr, lm->log_start);
    return lm->log_start;
}

static uint32_t _log_memory_eeprom_get_log_data_start(uint32_t log_start)
{
    return log_start + sizeof(log_bookkeeping_t);
}

static uint32_t _log_memory_eeprom_get_log_end(log_memory_t * lm)
{
    uint32_t log_end_addr = offsetof(log_header_t, log_end);

    lm->log_end = _log_memory_eeprom_get_value(lm, log_end_addr, lm->log_end);
    return lm->log_end;
}

static uint32_t _log_memory_eeprom_get_head(log_memory_t * lm)
{
    uint32_t log_start = _log_memory_eeprom_get_log_start(lm);
    uint32_t head_addr = log_start + offsetof(log_bookkeeping_t, head);

    lm->head = _log_memory_eeprom_get_value(lm, head_addr, lm->head);
    return lm->head;
}

static uint32_t _log_memory_eeprom_get_tail(log_memory_t * lm)
{
    uint32_t log_start = _log_memory_eeprom_get_log_start(lm);
    uint32_t tail_addr = log_start + offsetof(log_bookkeeping_t, tail);

    lm->tail = _log_memory_eeprom_get_value(lm, tail_addr, lm->tail);
    return lm->tail;
}

static void _log_memory_eeprom_set_head(log_memory_t * lm, uint32_t head)
{
    uint32_t log_start = _log_memory_eeprom_get_log_start(lm);
    uint32_t head_addr = log_start + offsetof(log_bookkeeping_t, head);

    lm->head = head;
    eeprom_write(lm->e, head_addr, &head, sizeof(head));
}

static void _log_memory_eeprom_set_tail(log_memory_t * lm, uint32_t tail)
{
    uint32_t log_start = _log_memory_eeprom_get_log_start(lm);
    uint32_t tail_addr = log_start + offsetof(log_bookkeeping_t, tail);

    lm->tail = tail;
    eeprom_write(lm->e, tail_addr, &tail, sizeof(tail));
}

static uint32_t _log_memory_eeprom_get_value(log_memory_t * lm,
                                             uint32_t addr,
                                             uint32_t cached)
{
    uint32_t value = cached;

    if (value == EEPROM_ADDRESS_INVALID) {
        eeprom_read(lm->e, addr, &value, sizeof(value));
    }

    return value;
}

static uint32_t _log_memory_eeprom_increment_addr_by(log_memory_t * lm,
                                                     uint32_t addr,
                                                     uint32_t incr)
{
    uint32_t incremented = addr + incr;

    uint32_t log_end = _log_memory_eeprom_get_log_end(lm);

    if (incremented >= log_end) {
        uint32_t overflow = incremented % log_end;
        uint32_t log_start = _log_memory_eeprom_get_log_start(lm);

        incremented = _log_memory_eeprom_get_log_data_start(log_start) + overflow;
    }

    return incremented;
}

static uint32_t _log_memory_eeprom_get_next_entry(log_memory_t * lm,
                                                  uint32_t current_entry)
{
    uint32_t current_entry_length;
    eeprom_read(lm->e, current_entry, &current_entry_length, sizeof(current_entry_length));
    return _log_memory_eeprom_increment_addr_by(lm,
                                                current_entry,
                                                current_entry_length);
}

static bool _log_memory_eeprom_has_enough_room(log_memory_t * lm,
                                               uint32_t candidate_tail,
                                               uint32_t entry_length)
{
    uint32_t head = _log_memory_eeprom_get_head(lm);
    uint32_t candidate_head = _log_memory_eeprom_increment_addr_by(lm,
                                                                   head,
                                                                   entry_length);

    bool empty        = candidate_tail == head;
    bool head_wrapped = candidate_head < head;
    bool entries_wrap = head_wrapped || (head < candidate_tail);

    bool enough_room  = empty ||
                        (entries_wrap
                            ? (candidate_head < candidate_tail)
                            : (candidate_head > candidate_tail));
    return enough_room;
}

static void _log_memory_eeprom_header_fill_magic_number(log_header_t * h,
                                                        uint32_t mn)
{
    h->magic_number = mn;
}

static void _log_memory_eeprom_header_fill_build_info(log_header_t * h,
                                                       log_memory_t const * lm)
{
    h->build_timestamp = lm->pi->build_timestamp;

    memcpy(h->git_hash, lm->pi->git_hash, 20);

    if (lm->pi->repo_dirty) {
        h->version_major_and_flags |= LOG_BUILD_FLAG_DIRTY;
    } else {
        h->version_major_and_flags &= ~LOG_BUILD_FLAG_DIRTY;
    }

    if (!(lm->pi->stable_version)) {
        h->version_major_and_flags |= LOG_BUILD_FLAG_NOT_STABLE;
    } else {
        h->version_major_and_flags &= ~LOG_BUILD_FLAG_NOT_STABLE;
    }
}

static void _log_memory_eeprom_header_fill_project_info(log_header_t * h,
                                                        log_memory_t const * lm)
{
    h->version_major_and_flags &= ~LOG_VERSION_MAJOR_MASK;
    h->version_major_and_flags |= lm->pi->version_major & LOG_VERSION_MAJOR_MASK;

    h->version_minor = lm->pi->version_minor;
    h->version_patch = lm->pi->version_patch;

    h->project_id = lm->pi->project_id;
    h->client_id  = lm->pi->client_id;
}

static void _log_memory_eeprom_header_fill_log_range(log_header_t * h,
                                                     log_memory_t const * lm)
{
    uint32_t write_size = eeprom_write_size(lm->e);
    h->log_start = write_size > sizeof(*h) ? write_size : sizeof(*h);
    h->log_end   = eeprom_size(lm->e);
}

static void _log_memory_eeprom_header_clear_reserved(log_header_t * h)
{
    h->version_major_and_flags &= ~LOG_BUILD_FLAGS_RESERVED;
    memset(h->__reserved, 0, sizeof(h->__reserved));
}

static bool _log_memory_is_valid(log_memory_t * lm,
                                 log_header_t const * h)
{
    return _log_memory_header_matches(lm, h) &&
           _log_memory_bookkeeping_is_valid(lm, h->log_start);
}

static bool _log_memory_header_matches(log_memory_t * lm,
                                       log_header_t const * h)
{
    log_header_t actual_header;
    eeprom_read(lm->e, 0, &actual_header, sizeof(actual_header));

    return memcmp(h, &actual_header, sizeof(*h)) == 0;
}

static bool _log_memory_bookkeeping_is_valid(log_memory_t * lm,
                                             uint32_t log_start)
{
    log_bookkeeping_t bk;
    eeprom_read(lm->e, log_start, &bk, sizeof(bk));

    uint32_t lowest_valid_address  = _log_memory_eeprom_get_log_data_start(log_start);
    uint32_t highest_valid_address = eeprom_size(lm->e) - 16;

    bool head_valid = (lowest_valid_address  <= bk.head) &&
                      (highest_valid_address >= bk.head);
    bool tail_valid = (lowest_valid_address  <= bk.tail) &&
                      (highest_valid_address >= bk.tail);

    return head_valid && tail_valid;
}

/** @} addtogroup LOG_MEMORY_EEPROM */
