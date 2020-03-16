/**@file    chsys_stub.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   ChsysStub Interface
 */

#ifndef CHSYS_STUB_H
#define CHSYS_STUB_H

/**@defgroup CHSYS_STUB ChsysStub
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "ch.h"
#include "chsys.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Determine (based on previous calls to chSysLock / chSysUnlock) the system
 * lock state.
 */
bool chsys_stub_is_locked(void);

/** Simulates ChibiOS' locking functionality with a global flag.
 *
 * Lock state can be checked with @ref chsys_stub_is_locked()
 *
 * @warning NOT atomic or thread safe; intended only for logical verification
 * of lock conditions in a single-threaded environment
 */
void chSysLock_stub_do_lock(int num_prev_calls);

/** Simulates ChibiOS' locking functionality with a global flag.
 *
 * Lock state can be checked with @ref chsys_stub_is_locked()
 *
 * @warning NOT atomic or thread safe; intended only for logical verification
 * of lock conditions in a single-threaded environment
 */
void chSysUnlock_stub_do_unlock(int num_prev_calls);

/** @} defgroup CHSYS_STUB */

#endif /* ifndef CHSYS_STUB_H */
