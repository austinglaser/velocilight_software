/**@file    ramtest.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Ramtest Source
 *
 * @addtogroup RAMTEST
 * @{
 *
 * @defgroup RAMTEST_PRIVATE Ramtest Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "ramtest.h"

/* Supporting modules */
#include "util.h"

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

bool ramtest8(void * start, size_t len)
{
    volatile uint8_t * ram = start;

    static const uint8_t patterns[] = {
        0x00,
        0xFF,
        0xAA,
        0x55,
        0x0F,
        0xF0,
        0x3D,
    };

    static const size_t n_patterns = ARRAY_ELEMENTS(patterns);

    for (size_t offset = 0; offset < n_patterns; offset += 1) {
        for (size_t i = 0; i < len; i++) {
            uint8_t pattern = patterns[(i + offset) % n_patterns];

            ram[i] = pattern;
        }

        for (size_t i = 0; i < len; i++) {
            uint8_t pattern = patterns[(i + offset) % n_patterns];
            uint8_t result = ram[i];

            if (result != pattern) {
                return false;
            }
        }
    }

    return true;
}

bool ramtest16(void * start, size_t len)
{
    volatile uint16_t * ram = start;

    static const uint16_t patterns[] = {
        0x0000,
        0xFFFF,
        0xAAAA,
        0x5555,
        0x000F,
        0x00F0,
        0x0F00,
        0xF000,
        0xF0F0,
        0x0F0F,
        0x0FF0,
    };
    static const size_t n_patterns = ARRAY_ELEMENTS(patterns);

    for (size_t offset = 0; offset < n_patterns; offset += 1) {
        for (size_t i = 0; i < len/2; i++) {
            uint16_t pattern = patterns[(i + offset) % n_patterns];
            ram[i] = pattern;
        }

        for (size_t i = 0; i < len/2; i++) {
            uint16_t pattern = patterns[(i + offset) % n_patterns];
            uint16_t result = ram[i];

            if (result != pattern) {
                return false;
            }
        }
    }

    return true;
}

bool ramtest32(void * start, size_t len)
{
    volatile uint32_t * ram = start;

    static const uint32_t patterns[] = {
        0x00000000,
        0xFFFFFFFF,
        0xAAAAAAAA,
        0x55555555,
        0x000F000F,
        0x00F000F0,
        0x0F000F00,
        0xF000F000,
        0xF0F0F0F0,
        0x0F0F0F0F,
        0x0FF00FF0,
    };
    static const size_t n_patterns = ARRAY_ELEMENTS(patterns);

    for (size_t offset = 0; offset < n_patterns; offset += 1) {
        for (size_t i = 0; i < len/4; i++) {
            uint32_t pattern = patterns[(i + offset) % n_patterns];
            ram[i] = pattern;
        }
        for (size_t i = 0; i < len/4; i++) {
            uint32_t pattern = patterns[(i + offset) % n_patterns];
            uint32_t result = ram[i];

            if (result != pattern) {
                return false;
            }
        }
    }

    return true;
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup RAMTEST_PRIVATE */
/** @} addtogroup RAMTEST */
