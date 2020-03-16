/**@file    log_memory.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Log Memory Interface
 */

#ifndef LOG_MEMORY_H
#define LOG_MEMORY_H

/**@defgroup LOG_MEMORY Logger Memory
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "log_memory_implementation.h"

#include "eeprom.h"
#include "memory_pool.h"
#include "project_info.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Initialize the log memory
 *
 * @param[in] lm:       Log Memory instance to instantiate
 * @param[in] e:        The memory where data will be written
 * @param[in] mp:       The memory pool where buffers will be freed after being
 *                      written to external memory
 * @param[in] pi:       A project and build information structure
 *
 * @return 0 on successful initialization, a negative value otherwise
 */
int log_memory_init(log_memory_t * lm,
                    eeprom_t * e,
                    mem_pool_t * mp,
                    project_info_t const * pi);

/** Write a serialized log entry to external memory
 *
 * @param[in] lm:       Log Memory instance to write to
 * @param[in] entry:    A serialized log entry. Memory should have been
 *                      allocated from the memory pool passed to @ref
 *                      log_memory_init()
 */
void log_memory_write(log_memory_t * lm, uint8_t * entry);

/** @} defgroup LOG_MEMORY */

#endif /* ifndef LOG_MEMORY_H */
