/**
 * @file    log_serialize.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Logger Serialization Interface
 */

#ifndef LOG_SERIALIZE_H
#define LOG_SERIALIZE_H

/**@defgroup LOG_SERIALIZE log_serialize
 * @{
 *
 * @brief
 *
 * TODO: Consider adding CRC to log entries
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "log.h"

#include <stdbool.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

#if !defined(LS_BUFFER_LEN) || defined(DOXYGEN)
#define LOG_BUFFER_LEN       128     /**< Length of data buffers */
#endif

#if LOG_BUFFER_LEN < 16
#error "Buffers must be at least long enough to store mandatory log fields"
#endif

/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Initialize the log serializer */
void log_serialize_init(void);

/** Serialize @p entry into @p buf
 *
 * @warning     This function does not verify the validity of its arguments. It
 *              should only be called internally from the log module (for
 *              instance, from log_write)
 *
 * @param[out] buf:             Where the serialized data will be written.
 *                              Assumed to be at least @ref LOG_BUFFER_LEN
 *                              bytes long
 * @param[in] entry:            A pointer to the entry for storage
 * @param[in] timestamp:        The timestamp of the entry
 * @param[in] program_counter:  The current thread's program counter
 * @param[in] stack_pointer:    The current thread's stack pointer
 * @param[in] stack_usage:      The current thread's total stack usage up to
 *                              this point
 *
 * @note    If serialization fails, will zero all of @p buf
 *
 * @return  The number of bytes the serialization of @p entry occupies in @p
 *          buf, or 0 if an error ocurred
 */
size_t log_serialize(uint8_t * buf,
                     log_entry_t const * entry,
                     uint64_t timestamp,
                     uint32_t program_counter,
                     uint32_t stack_pointer,
                     uint32_t stack_usage);

/** @} defgroup LOG_SERIALIZE */

#endif /* ifndef LOG_SERIALIZE_H */
