/**@file    fake_eeprom.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   FakeEeprom Interface
 */

#ifndef FAKE_EEPROM_H
#define FAKE_EEPROM_H

/**@defgroup FAKE_EEPROM FakeEeprom
 * @{
 *
 * Callbacks appropriate for use with a mocked version of eeprom
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include "eeprom.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Resets the EEPROM's memory region */
void fake_eeprom_reset(eeprom_t * e);

/** EEEPROM CMock callback for eeprom_erase
 *
 * @param[in] e:            The fake eeprom handle
 * @param num_prev_calls:   Unused
 *
 * @return 0
 */
int fake_eeprom_erase(eeprom_t * e, int num_prev_calls);

/** EEPROM CMock callback for eeprom_read
 *
 * @param[in] e:            The fake eeprom handle
 * @param[in] address:      Address to access
 * @param[out] data:        Location to store data. Must be at least @p len long
 * @param[in] len:          Number of bytes to read
 * @param num_prev_calls:   Unused
 *
 * @return 0
 */
int fake_eeprom_read(eeprom_t * e,
                     uint32_t address,
                     void * data,
                     size_t len,
                     int num_prev_calls);

/** EEPROM CMock callback for eeprom_read
 *
 * @param[in] e:            The fake eeprom handle
 * @param[in] address:      Address to access
 * @param[in] data:         Data to write
 * @param[in] len:          Number of bytes to write
 * @param num_prev_calls:   Unused
 *
 * @return 0
 */
int fake_eeprom_write(eeprom_t * e,
                      uint32_t address,
                      void const * data,
                      size_t len,
                      int num_prev_calls);

/** @} defgroup FAKE_EEPROM */

#endif /* ifndef FAKE_EEPROM_H */
