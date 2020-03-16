/**@file    memory_pool_implementation.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   MemoryPoolImplementation Source
 *
 * @addtogroup MEMORY_POOL_IMPLEMENTATION
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "memory_pool.h"
#include "memory_pool_implementation.h"

#include "ch.h"
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
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void memory_pool_init(mem_pool_t * mp,
                      void * objs,
                      size_t obj_n,
                      size_t obj_size)
{
    chPoolObjectInit(mp, obj_size, NULL);
    chPoolLoadArray(mp, objs, obj_n);
}

void * memory_pool_alloc(mem_pool_t * mp)
{
    syssts_t status = chSysGetStatusAndLockX();
    void * obj = chPoolAllocI(mp);
    chSysRestoreStatusX(status);

    return obj;
}

void memory_pool_free(mem_pool_t * mp, void * buf)
{
    syssts_t status = chSysGetStatusAndLockX();
    chPoolFreeI(mp, buf);
    chSysRestoreStatusX(status);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup MEMORY_POOL_IMPLEMENTATION */
