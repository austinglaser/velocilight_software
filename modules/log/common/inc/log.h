/**@file    log.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Logger Interface
 */

#ifndef LOG_H
#define LOG_H

/**@defgroup LOG Logger
 * @{
 *
 * Utility for logging event occurrences
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "eeprom.h"
#include "project_info.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/**@defgroup LOG_CONSTANTS
 * @{
 *
 * @note:   See Logging Standard for details
 */

/** Logger standard version this complies with */
#define LOG_STANDARD_VERSION                    2

/** The maximum number of binary data for a single log */
#define LOG_MAX_BINARY_DATA                     5

/** Entry types */
enum EVENT_TYPES {
    /** Upper limit (inclusive) for custom entry subtypes */
    MAX_CUSTOM_TYPE                             = 0x7F,

    /** Record a system_info reset event */
    TYPE_RESET                                  = 0x80,

    /** Record a system_info-level exception (NOT a CException 'exception') */
    TYPE_EXCEPTION                              = 0x81,

    /** Record a runtime error */
    TYPE_RUNTIME_ERROR                          = 0x82,

    /** Record a state-machine state change */
    TYPE_STATE_CHANGE                           = 0x83,

    /** Entry types greater than this value are reserved */
    MAX_TYPE                                    = 0x83,
};

/** Custom entry subtypes */
enum CUSTOM_TYPE_SUBTYPES {
    /** Upper limit (inclusive) for custom entry subtypes */
    MAX_CUSTOM_TYPE_SUBTYPE                     = 0x7F,
};

/** Reset subtypes */
enum RESET_SUBTYPES {
    /** No information about this reset's specific subtype */
    SUBTYPE_UNKNOWN_RESET                       = 0x80,

    /** Reset occurred because of a system_info power cycle */
    SUBTYPE_POWER_RESET                         = 0x81,

    /** Reset was requested by software */
    SUBTYPE_SOFTWARE_RESET                      = 0x82,

    /** Reset was caused by a watchdog timeout */
    SUBTYPE_WATCHDOG_RESET                      = 0x83,

    /** Reset subtypes greater than this value are reserved */
    MAX_RESET_SUBTYPE                           = 0x83,
};

/** Exception subtypes */
enum EXCEPTION_SUBTYPES {
    /** No information about this exception's specific subtype */
    SUBTYPE_UNKNOWN_EXCEPTION                   = 0x80,

    /** Exception occurred because of a stack overflow */
    SUBTYPE_STACK_OVERFLOW_EXCEPTION            = 0x81,

    /** A hard fault occurred */
    SUBTYPE_HARD_FAULT_EXCEPTION                = 0x82,

    /** A bus fault occurred */
    SUBTYPE_BUS_FAULT_EXCEPTION                 = 0x83,

    /** A usage fault occurred */
    SUBTYPE_USAGE_FAULT_EXCEPTION               = 0x84,

    /** Exception subtypes greater than this value are reserved */
    MAX_EXCEPTION_SUBTYPE                       = 0x84,
};

/** Runtime Error subtypes */
enum RUNTIME_ERROR_SUBTYPES {
    /** No information about this specific runtime error */
    SUBTYPE_UNKNOWN_RUNTIME_ERROR               = 0x80,

    /** Logger was called with an invalid log type */
    SUBTYPE_INVALID_LOG_TYPE_RUNTIME_ERROR      = 0x81,

    /** Logger was called with an invalid log subtype */
    SUBTYPE_INVALID_LOG_SUBTYPE_RUNTIME_ERROR   = 0x82,

    /** A function was called with an invalid argument */
    SUBTYPE_INVALID_ARGUMENT_RUNTIME_ERROR      = 0x83,

    /** A buffer overflow ocurred */
    SUBTYPE_BUFFER_OVERFLOW_RUNTIME_ERROR       = 0x84,

    /** A memory allocation failure ocurred */
    SUBTYPE_MEMORY_ALLOCATION_RUNTIME_ERROR     = 0x85,

    /** Runtime error subtypes greater than this value are reserved */
    MAX_RUNTIME_ERROR_SUBTYPE                   = 0x85,
};

/** State Change subtypes */
enum STATE_CHANGE_SUBTYPES {
    /** State changes are all custom subtypes */
    MAX_STATE_CHANGE_SUBTYPE                    = 0x7F,
};

/** Optional field flags */
enum LOG_FLAGS {
    /** No optional fields present in a log */
    LOG_NO_FLAGS                              = 0x0000,

    /** Include the program counter's value */
    LOG_FLAG_PC                               = 0x8000,

    /** Include the stack pointer's value */
    LOG_FLAG_SP                               = 0x4000,

    /** Include the maximum used stack */
    LOG_FLAG_SU                               = 0x2000,

    /** Include a descriptor string */
    LOG_FLAG_DSC                              = 0x1000,

    /** Include one or more binary fields */
    LOG_FLAG_BIN                              = 0x0800,

    /** All valid flag values */
    LOG_FLAGS_MASK                            = 0xF800,
};

/** @} defgroup LOG_CONSTANTS */

/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** Structure storing a single element of data for storage */
struct _log_binary_data {
    uint8_t type;                       /**< Optional identifier */
    uint32_t len;                       /**< The number of stored bytes */
    void const * data;                  /**< Pointer to the data to store */
};

/** Convenience typedef for binary data */
typedef struct _log_binary_data log_binary_data_t;

/** Structure encoding a log entry */
struct _log_entry {
    /** The entry type descriptor
     *
     * @see enum EVENT_TYPES
     */
    uint8_t type;

    /** The entry subtype descriptor
     *
     * Can be any value less then @ref MAX_CUSTOM_SUBTYPE, or one of the
     * defined subtype values
     *
     * @see enum RESET_SUBTYPES
     * @see enum EXCEPTION_SUBTYPES
     * @see enum RUNTIME_ERROR_SUBTYPES
     * @see enum STATE_CHANGE_SUBTYPES
     */
    uint8_t subtype;

    /** A logical OR of @ref enum LOG_FLAGS */
    uint16_t flags;

    /** A descriptor string for the log. Only included in final entry if @ref
     * LOG_FLAG_DSC is set in @ref flags.
     */
    const char * descriptor_string;

    /** The number of valid binary data (maximum @ref LOG_MAX_BINARY_DATA) */
    uint32_t binary_data_count;

    /** The binary data entries to be stored. Only included in the final entry
     * if @ref LOG_FLAG_BIN is set.
     */
    log_binary_data_t binary_data[LOG_MAX_BINARY_DATA];
};

/** Convenience typedef for log */
typedef struct _log_entry log_entry_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Initialize the Logger
 *
 * @param[in] e:    The memory where data will be logged
 *
 * Returns 0 on success, or a negative value on failure
 *
 * TODO: Make log handle top-level
 */
int log_init(eeprom_t * e, project_info_t const * pi);

/** Write a log entry to memory
 *
 * @param[in] entry:    Structure describing the entry to be written
 */
void log_write(log_entry_t const * entry);

/** @} defgroup LOG */

#endif /* ifndef LOG_H */
