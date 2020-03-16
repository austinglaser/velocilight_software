/**@file    byteswap.h
 * @author  Austin Glaser <austin@boulderes.com>
 *
 * @brief   Byteswap interface
 */

#ifndef BYTESWAP_H_
#define BYTESWAP_H_

/**@defgroup BYTESWAP Byteswap Utilities
 * @{
 *
 * @brief   Generic integer byte-swapping utilities
 *
 * @note    Not optimized or implemented in assembly. This code should be
 *          portable to basically any architecture, and should be kept that way,
 *          with non-portable sections protected by preprocessor guards, and the generic
 *          code left in as the default.
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Swaps the bytes in the 16-bit integer val
 *
 * @param[in] val:      The integer to be byte-wise reversed
 *
 * @return      val, bytes reversed
 */
uint16_t byteswap_uint16(uint16_t val);

/** Swaps the bytes in the 32-bit integer val
 *
 * @param[in] val:      The integer to be byte-wise reversed
 *
 * @return      val, bytes reversed
 */
uint32_t byteswap_uint32(uint32_t val);

/** Swaps the bytes in the 64-bit integer val
 *
 * @param[in] val:      The integer to be byte-wise reversed
 *
 * @return      val, bytes reversed
 */
uint64_t byteswap_uint64(uint64_t val);

/** @} defgroup BYTESWAP */

#endif /* ifndef BYTESWAP_H_ */
