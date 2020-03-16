/**@file    log_memory_implementation.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   LogMemory Source
 *
 * @addtogroup LOG_MEMORY
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "log_memory.h"
#include "log_memory_implementation.h"
#include "log_memory_eeprom.h"

#include "ch.h"

#include "eeprom.h"
#include "ensure.h"
#include "memory_pool.h"
#include "util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Thread which writes buffers to memory
 *
 * @param[in] _lm:  log_memory instance to operate on
 */
void _log_memory_thread_f(void * _lm);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

/** Working area for memory-writing thread */
static THD_WORKING_AREA(log_memory_thread_wa, 128);

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

int log_memory_init(log_memory_t * lm,
                    eeprom_t * e,
                    mem_pool_t * mp,
                    project_info_t const * pi)
{
    ensure(lm != NULL);
    ensure(e  != NULL);
    ensure(mp != NULL);
    ensure(pi != NULL);

    lm->e  = e;
    lm->mp = mp;
    lm->pi = pi;

    chMBObjectInit(&(lm->mbox), lm->mbox_buf, LOG_MEMORY_MBOX_SIZE);

    chSysLock();
    lm->thread = chThdCreateI(&log_memory_thread_wa,
                              sizeof(log_memory_thread_wa),
                              LOWPRIO,
                              _log_memory_thread_f,
                              lm);
    chSysUnlock();

    chThdStart(lm->thread);

    return 0;
}

void log_memory_write(log_memory_t * lm, uint8_t * entry)
{
    chSysLock();
    msg_t err = chMBPostI(&(lm->mbox), (msg_t) entry);
    chSysUnlock();

    if (err != MSG_OK) {
        memory_pool_free(lm->mp, entry);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

void _log_memory_thread_f(void * _lm)
{
    log_memory_t * lm = _lm;

    log_memory_eeprom_setup(lm);

    while (true) {
        msg_t _entry;
        msg_t err = chMBFetch(&(lm->mbox), &_entry, TIME_INFINITE);

        if (err == MSG_OK) {
            uint8_t * entry = (uint8_t *) _entry;
            log_memory_eeprom_write_entry(lm, entry);
            memory_pool_free(lm->mp, entry);
        }
    }
}

/** @} addtogroup LOG_MEMORY */
