/**@file    memory_pool.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Memory Pool Interface
 */

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

/**@defgroup MEMORY_POOL Memory Pool
 * @{
 *
 * Allows psuedo-dynamic memory management by handing out slices of a
 * statically allocated chunk of memory.
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "memory_pool_implementation.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Initializes a new memory pool object
 *
 * @note The memory pool must be filled with data
 *
 * @param[out] mp:      The pool to initialize
 * @param[in] objs:     The objects to be handed out by the pool. Must point to
 *                      a region a total of (@p obj_n * @p obj_size) bytes
 * @param[in] obj_n:    The number of objects in @p obj
 * @param[in] obj_size: The size of objects allocated with @p memory_pool_alloc
 */
void memory_pool_init(mem_pool_t * mp,
                      void * objs,
                      size_t obj_n,
                      size_t obj_size);

/** Gets a single object from @p mp
 *
 * The returned buffer will point to a valid memory region of @p obj_size (see
 * @ref memory_pool_init()) bytes.
 *
 * @param[in,out] mp:   The pool from which to allocate
 *
 * @return  A pointer to an allocated object, or NULL if pool allocation failed
 */
void * memory_pool_alloc(mem_pool_t * mp);

/** Frees a object back into @p mp
 *
 * @p buf must have been allocated by @ref memory_pool_alloc()
 *
 * @param[in,out] mp:   The pool to which to free
 * @param[in] buf:      The memory region to free
 */
void memory_pool_free(mem_pool_t * mp, void * buf);

/** @} defgroup MEMORY_POOL */

#endif /* ifndef MEMORY_POOL_H */
