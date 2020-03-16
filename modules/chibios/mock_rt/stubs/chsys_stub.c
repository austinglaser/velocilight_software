/**@file    chsys_stub.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   ChsysStub Source
 *
 * @addtogroup CHSYS_STUB
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "ch.h"

#include "chsys_stub.h"

#include "unity.h"

#include "util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

/** System lock flag */
static bool _chsys_stub_is_locked = false;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */
/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

bool chsys_stub_is_locked(void)
{
    return _chsys_stub_is_locked;
}

void chSysLock_stub_do_lock(int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    TEST_ASSERT_MESSAGE(!_chsys_stub_is_locked,
                        "Lock called while already locked");

    _chsys_stub_is_locked = true;
}

void chSysUnlock_stub_do_unlock(int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    TEST_ASSERT_MESSAGE(_chsys_stub_is_locked,
                        "Unlock called while already unlocked");

    _chsys_stub_is_locked = false;
}

/** @} addtogroup CHSYS_STUB */
