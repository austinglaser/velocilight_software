/**@file    log_memory_eeprom.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogMemoryEeprom Interface
 */

#ifndef LOG_MEMORY_EEPROM_H
#define LOG_MEMORY_EEPROM_H

/**@defgroup LOG_MEMORY_EEPROM LogMemoryEeprom
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "log_memory.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Set up the provided EEPROM region so that it's a log
 *
 * @note Blocks on EEPROM operations
 *
 * @param[in] lm: log_memory instance
 */
void log_memory_eeprom_setup(log_memory_t * lm);

/** Write a single entry to the EEPROM region
 *
 * @note Blocks on EEPROM operations
 *
 * @param[in] lm:       log_memory instance
 * @param[in] entry:    entry to serialize
 */
void log_memory_eeprom_write_entry(log_memory_t * lm, uint8_t const * entry);

/** @} defgroup LOG_MEMORY_EEPROM */

#endif /* ifndef LOG_MEMORY_EEPROM_H */
