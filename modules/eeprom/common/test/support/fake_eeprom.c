/**@file    fake_eeprom.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   FakeEeprom Source
 *
 * @addtogroup FAKE_EEPROM
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "fake_eeprom.h"

#include "unity.h"

#include "util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void fake_eeprom_reset(eeprom_t * e)
{
    e->size = EEPROM_MEMORY_SIZE;

    fake_eeprom_erase(e, 0);
}

int fake_eeprom_erase(eeprom_t * e, int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    memset(e->memory, 0xFF, e->size);

    return 0;
}

int fake_eeprom_read(eeprom_t * e,
                     uint32_t address,
                     void * data,
                     size_t len,
                     int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    TEST_ASSERT_MESSAGE(address + len <= e->size,
                        "Attempt to read outside of EEPROM memory");

    uint8_t * src = e->memory + address;
    memcpy(data, src, len);

    return 0;
}

int fake_eeprom_write(eeprom_t * e,
                      uint32_t address,
                      void const * data,
                      size_t len,
                      int num_prev_calls)
{
    UNUSED_VARIABLE(num_prev_calls);

    TEST_ASSERT_MESSAGE(address + len <= e->size,
                        "Attempt to write outside of EEPROM memory");

    uint8_t * dest = e->memory + address;
    memcpy(dest, data, len);

    return 0;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup FAKE_EEPROM */
