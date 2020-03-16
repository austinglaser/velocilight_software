/**@file    log_memory_eeprom_test_util.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogMemoryEepromTestUtil Interface
 */

#ifndef LOG_MEMORY_EEPROM_TEST_UTIL_H
#define LOG_MEMORY_EEPROM_TEST_UTIL_H

/**@defgroup LOG_MEMORY_EEPROM_TEST_UTIL LogMemoryEepromTestUtil
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "eeprom.h"
#include "project_info.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/** EEPROM starting point */
#define BASE_ADDRESS                    ((uint32_t) 0x00000000)


/** Beginning of log header */
#define HEADER_ADDRESS                  (BASE_ADDRESS + 0x0000)

/** Full log header length */
#define HEADER_LENGTH                   ((uint32_t) 0x00000040)

/** Magic number location */
#define MAGIC_NUMBER_ADDRESS            (HEADER_ADDRESS + 0x0000)

/** Number used to identify EEPROM as being a valid log region */
#define LOG_MEMORY_EEPROM_MAGIC_NUMBER  ((uint32_t) 0x6C6F6702)

/** Beginning of git hash (in log header) */
#define GIT_HASH_ADDRESS                (HEADER_ADDRESS + 0x0004)

/** Bytes occupied by git hash */
#define GIT_HASH_LENGTH                 ((uint32_t) 0x000000014)

/** Address of timestamp */
#define TIMESTAMP_ADDRESS               (HEADER_ADDRESS + 0x0018)

/** Address of patch version */
#define VERSION_PATCH_ADDRESS           (HEADER_ADDRESS + 0x0020)

/** Address of minor version */
#define VERSION_MINOR_ADDRESS           (HEADER_ADDRESS + 0x0021)

/** Address where major version and flags can be found */
#define VERSION_MAJOR_FLAGS_ADDRESS     (HEADER_ADDRESS + 0x0022)

/** Mask for extracting project ID */
#define VERSION_MAJOR_MASK              ((uint16_t) 0x0FFF)

/** Mask for extracting dirty flag */
#define FLAG_DIRTY_MASK                 ((uint16_t) 0x8000)

/** Mask for extracting !stable flag */
#define FLAG_NOT_STABLE_MASK            ((uint16_t) 0x4000)

/** Mask for extracting reserved bits in PID_FLAGS */
#define FLAGS_RESERVED_MASK             ((uint16_t) 0x3000)

/** Address of project ID */
#define PROJECT_ID_ADDRESS              (HEADER_ADDRESS + 0x0024)

/** Address of client ID */
#define CLIENT_ID_ADDRESS               (HEADER_ADDRESS + 0x0026)

/** Log start address */
#define LOG_START_ADDRESS               (HEADER_ADDRESS + 0x0028)

/** Log end address */
#define LOG_END_ADDRESS                 (HEADER_ADDRESS + 0x002C)

/** Start of header reserved region */
#define HEADER_RESERVED_ADDRESS         (HEADER_ADDRESS + 0x0030)

/** Extent of header reserved region */
#define HEADER_RESERVED_LENGTH          ((uint32_t) 0x00000010)


/** Length of header reserved region
 *
 * @note The start address is the value at @ref LOG_START_ADDRESS
 */
#define BK_LENGTH               ((uint32_t) 0x00000010)

/** Offset from bookkeeping base address for head */
#define HEAD_OFFSET             ((uint32_t) 0x00000000)

/** Offset from bookkeeping base address for tail */
#define TAIL_OFFSET             ((uint32_t) 0x00000004)

/** Offset from bookkeeping base address for bookkeeping resrved region */
#define BK_RESERVED_OFFSET      ((uint32_t) 0x00000008)

/** Length of bookkeeping resrved region */
#define BK_RESERVED_LENGTH      ((uint32_t) 8)

/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Sets @p pi to some default values */
void log_memory_eeprom_helper_fill_project_info(project_info_t * pi);

/** Returns the value in the magic number field of EEPROM's memory */
uint32_t log_memory_eeprom_helper_get_magic_number(eeprom_t const * e);

/** Returns a pointer to a git hash array (length @ref GIT_HASH_LENGTH) */
uint8_t const * log_memory_eeprom_helper_get_git_hash(eeprom_t const * e);

/** Returns the value in the timestamp field of EEPROM's memory */
uint64_t log_memory_eeprom_helper_get_timestamp(eeprom_t const * e);

/** Returns the patch version number from EEPROM */
uint8_t log_memory_eeprom_helper_get_patch_version(eeprom_t const * e);

/** Returns the minor version number from EEPROM */
uint8_t log_memory_eeprom_helper_get_minor_version(eeprom_t const * e);

/** Returns the major version number from EEPROM */
uint16_t log_memory_eeprom_helper_get_major_version(eeprom_t const * e);

/** Returns the client ID */
uint16_t log_memory_eeprom_helper_get_client_id(eeprom_t const * e);

/** Returns the project ID */
uint16_t log_memory_eeprom_helper_get_project_id(eeprom_t const * e);

/** Returns the state of the dirty flag */
bool log_memory_eeprom_helper_get_dirty_flag(eeprom_t const * e);

/** Returns the state of the !stable flag */
bool log_memory_eeprom_helper_get_not_stable_flag(eeprom_t const * e);

/** Gets the contents of the reserved flags in the header */
uint16_t log_memory_eeprom_helper_get_reserved_flags(eeprom_t const * e);

/** Gets an EEPROM address for the start of the log region */
uint32_t log_memory_eeprom_helper_get_log_start(eeprom_t const * e);

/** Gets an EEPROM address for the end of the log region */
uint32_t log_memory_eeprom_helper_get_log_end(eeprom_t const * e);

/** Gets a pointer to the reserved section of the header (length @ref
 *  HEADER_RESERVED_LENGTH)
 */
uint8_t const * log_memory_eeprom_helper_get_reserved_header(eeprom_t const * e);

/** Retrieves the value in the head field of hte bookkeeping region */
uint32_t log_memory_eeprom_helper_get_head(eeprom_t const * e);

/** Retrieves the value in the tail field of hte bookkeeping region */
uint32_t log_memory_eeprom_helper_get_tail(eeprom_t const * e);

/** Get a 32-bit value at an EEPROM address */
uint32_t log_memory_eeprom_helper_get_value(eeprom_t const * e,
                                            uint32_t addr);

/** Writes a value to the head field of the bookkeeping region */
void log_memory_eeprom_helper_set_head(eeprom_t const * e,
                                       uint32_t head);

/** Writes a value to the tail field of the bookkeeping region */
void log_memory_eeprom_helper_set_tail(eeprom_t const * e,
                                       uint32_t tail);

/** Set a 32-bit value at an EEPROM address */
void log_memory_eeprom_helper_set_value(eeprom_t const * e,
                                        uint32_t addr,
                                        uint32_t value);

/** Gets a pointer to the reserved section of the bookkeeping region (length
 *  @ref BK_RESERVED_LENGTH)
 */
uint8_t const * log_memory_eeprom_helper_get_reserved_bookkeeping(eeprom_t const * e);

/** @} defgroup LOG_MEMORY_EEPROM_TEST_UTIL */

#endif /* ifndef LOG_MEMORY_EEPROM_TEST_UTIL_H */
