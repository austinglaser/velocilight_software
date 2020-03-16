/**@file    eeprom.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Eeprom Interface
 */

#ifndef EEPROM_H
#define EEPROM_H

/**@defgroup EEPROM Eeprom
 * @{
 *
 * A driver for persistent external memory
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "eeprom_implementation.h"

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Initialize an eeprom instance
 *
 * @param[in,out] e:    Instance handle
 * @param[in] config:   Eeprom configuration
 *
 * @return  0 on success, nonzero if the eeprom could not be initialized
 */
int eeprom_init(eeprom_t * e, eeprom_config_t const * config);

/** Determine the size of an EEPROM
 *
 * @param[in] e:        Instance handle
 *
 * @return  The total memory size
 */
uint32_t eeprom_size(eeprom_t const * e);

/** Determine the size of separately writeable EEPROM regions, in bytes
 *
 * @return  The minimum size of EEPROM writes
 */
uint32_t eeprom_write_size(eeprom_t const * e);

/** Erases all data on the EEPROM
 *
 * @param[in] e:        Instance handle
 *
 * @return  0 on success, nonzero if the data could not be erased or if any
 *          parameter was invalid
 */
int eeprom_erase(eeprom_t * e);

/** Read some data from @p e
 *
 * @param[in] e:        Instance handle
 * @param[in] address:  Address to access
 * @param[out] data:    Location to store data. Must be at least @p len long
 * @param[in] len:      Number of bytes to read
 *
 * @return  0 on success, nonzero if the data could not be read or if any
 *          parameter was invalid
 */
int eeprom_read(eeprom_t * e,
                uint32_t address,
                void * data,
                size_t len);

/** Write some data to @p e
 *
 * @param[in] e:        Instance handle
 * @param[in] address:  Address to access
 * @param[in] data:     Data to write
 * @param[in] len:      Number of bytes to write
 *
 * @return  0 on success, nonzero if the data could not be written or if any
 *          parameter was invalid
 */
int eeprom_write(eeprom_t * e,
                 uint32_t address,
                 void const * data,
                 size_t len);

/** @} defgroup EEPROM */

#endif /* ifndef EEPROM_H */
