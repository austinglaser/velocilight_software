/**@file    log_memory_implementation.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogMemoryImplementation Interface
 */

#ifndef LOG_MEMORY_IMPLEMENTATION_H
#define LOG_MEMORY_IMPLEMENTATION_H

/**@defgroup LOG_MEMORY_IMPLEMENTATION LogMemoryImplementation
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "eeprom.h"
#include "memory_pool.h"
#include "project_info.h"

#include "ch.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

#if !defined(LOG_MEMORY_BUFFER_LEN) || defined(_DOXYGEN_)
#   define LOG_MEMORY_MBOX_SIZE         5
#endif

/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** A log memory instance structure */
struct log_memory {
    eeprom_t * e;                         /**< EEPROM instance for data
                                               storage */
    mem_pool_t * mp;                      /**< Memory pool for buffer freeing */
    project_info_t const * pi;            /**< Build and project information */
    thread_t * thread;                    /**< Background thread for blocking
                                               operations */
    mailbox_t mbox;                       /**< Mailbox used to pass entries to
                                               background thread */
    msg_t mbox_buf[LOG_MEMORY_MBOX_SIZE]; /**< Buffer used by @ref iq */

    uint32_t log_start;                   /**< Cached version of log_start */
    uint32_t log_end;                     /**< Cached version of log_end */
    uint32_t head;                        /**< Cached version of head */
    uint32_t tail;                        /**< Cached version of tail */
};

/** A log memory instance */
typedef struct log_memory log_memory_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** @} defgroup LOG_MEMORY_IMPLEMENTATION */

#endif /* ifndef LOG_MEMORY_IMPLEMENTATION_H */
