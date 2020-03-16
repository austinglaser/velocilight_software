/**@file    log_memory_stub.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogMemoryStub Interface
 */

#ifndef LOG_MEMORY_STUB_H
#define LOG_MEMORY_STUB_H

/**@defgroup LOG_MEMORY_STUB LogMemoryStub
 * @{
 *
 * Stubs useful with a mocked version of log_memory
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "log_memory.h"
#include "memory_pool.h"
#include "project_info.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** Structure holding all arguments passed to log_memory_init */
struct _log_memory_init_args {
    log_memory_t * lm;         /**< log_memory instance */
    eeprom_t * e;              /**< EEPROM instance */
    mem_pool_t * mp;           /**< Memory pool instance */
    project_info_t const * pi; /**< Project information instance */
};

typedef struct _log_memory_init_args log_memory_init_args_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Reset persistent data stored by this module */
void log_memory_stub_reset(void);

/** Retrieve the total number of calls made to log_memory_stub_init_* functions
 *
 * Reset by @ref log_memory_stub_reset()
 *
 * @see log_memory_stub_init_validate_arguments
 * @see log_memory_stub_init_capture_mp
 *
 * @return  The total number of calls
 */
uint32_t log_memory_stub_init_calls(void);

/** Retrieve the arguments passed to log_memory_stub_init()
 *
 * @see log_memory_stub_init
 *
 * @return  All arguments passed to @ref log_memory_init()
 */
log_memory_init_args_t const * log_memory_stub_init_args(void);

/** Verify that all arguments passed to log_memory_init() are valid
 *
 * Increments the value returned by @ref log_memory_stub_init_calls()
 *
 * @param[in] e:                An EEPROM instance
 * @param[in] mp:               A memory pool instance
 * @param[in] pi:               A project-information instance
 * @param[in] num_prev_calls:   Unused
 *
 * @return 0
 */
int log_memory_stub_init(log_memory_t * lm,
                         eeprom_t * e,
                         mem_pool_t * mp,
                         project_info_t const * pi,
                         int num_prev_calls);

/** @} defgroup LOG_MEMORY_STUB */

#endif /* ifndef LOG_MEMORY_STUB_H */
