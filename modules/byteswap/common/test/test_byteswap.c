/**
 * @file    test_byteswap.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestByteswap Source
 *
 * @addtogroup TEST_BYTESWAP
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"
#include "byteswap.h"

#include <stdbool.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void test_byteswap_halfword(void)
{
    uint16_t halfword = 0x0011;
    uint16_t expected = 0x1100;

    TEST_ASSERT_EQUAL_HEX16(expected, byteswap_uint16(halfword));
}

void test_byteswap_word(void)
{
    uint32_t word       = 0x00112233;
    uint32_t expected   = 0x33221100;

    TEST_ASSERT_EQUAL_HEX32(expected, byteswap_uint32(word));
}

void test_byteswap_doubleword(void)
{
    uint64_t doubleword = 0x0011223344556677;
    uint64_t expected   = 0x7766554433221100;

    TEST_ASSERT_EQUAL_HEX64(expected, byteswap_uint64(doubleword));
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_BYTESWAP */
