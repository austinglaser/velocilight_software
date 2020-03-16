/**@file    byteswap.c
 * @author  Austin Glaser <austin@boulderes.com>
 *
 * @brief   Byteswap implementation
 *
 * @addtogroup BYTESWAP
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "byteswap.h"

#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Shifts byte @p from_byte_index in @p value to position @p to_byte_index
 *
 * @param[in] value             The input value
 * @param[in] from_byte_index:  The byte position to extract from val
 * @param[in] to_byte_index:    The byte position to shift the value to
 *
 * @return      @p value, with byte @p from_byte_index in position @p
 *              to_byte_index, and all other bits zero
 */
static uint64_t _byteswap_byte_shift(uint64_t value,
                                     uint8_t from_byte_index,
                                     uint8_t to_byte_index);

/** Isolates byte @p byte_index from @p value
 *
 * @note    Performs no shifting, simply zeros all bits outside the 
 *          relevant byte
 *
 * @param[in] value:        The value to mask
 * @param[in] byte_index:   The byte to extract
 *
 * @return      @p value, with all bits other than those in byte @p byte_index
 *              zeroed
 */
static uint64_t _byteswap_byte(uint64_t value, uint8_t byte_index);

/** Mask for byte @p byte_index in an (up to) 64-bit value
 *
 * @param[in] byte_index:   The byte to mask
 *
 * @return      The byte mask
 */
static uint64_t _byteswap_byte_mask(uint8_t byte_index);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

uint16_t byteswap_uint16(uint16_t val)
{
    uint16_t val_swapped = _byteswap_byte_shift(val, 0, 1) |
                           _byteswap_byte_shift(val, 1, 0);

    return val_swapped;
}

uint32_t byteswap_uint32(uint32_t val)
{
    uint32_t val_swapped = _byteswap_byte_shift(val, 0, 3) |
                           _byteswap_byte_shift(val, 1, 2) |
                           _byteswap_byte_shift(val, 2, 1) |
                           _byteswap_byte_shift(val, 3, 0);

    return val_swapped;
}

uint64_t byteswap_uint64(uint64_t val)
{
    uint64_t val_swapped = _byteswap_byte_shift(val, 0, 7) |
                           _byteswap_byte_shift(val, 1, 6) |
                           _byteswap_byte_shift(val, 2, 5) |
                           _byteswap_byte_shift(val, 3, 4) |
                           _byteswap_byte_shift(val, 4, 3) |
                           _byteswap_byte_shift(val, 5, 2) |
                           _byteswap_byte_shift(val, 6, 1) |
                           _byteswap_byte_shift(val, 7, 0);

    return val_swapped;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static uint64_t _byteswap_byte_shift(uint64_t value,
                                     uint8_t from_byte_index,
                                     uint8_t to_byte_index)
{
    uint64_t from_byte = _byteswap_byte(value, from_byte_index);
    if (from_byte_index <= to_byte_index) {
        return from_byte << ((to_byte_index - from_byte_index) * 8);
    } else {
        return from_byte >> ((from_byte_index - to_byte_index) * 8);
    }
}

static uint64_t _byteswap_byte(uint64_t value, uint8_t byte_index)
{
    return value & _byteswap_byte_mask(byte_index);
}

static uint64_t _byteswap_byte_mask(uint8_t byte_index)
{
    return UINT64_C(0x00FF) << (byte_index * 8);
}

/** @} addtogroup BYTESWAP */
