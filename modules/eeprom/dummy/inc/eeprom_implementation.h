/**@file    eeprom_implementation.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   EepromImplementation Interface
 */

#ifndef EEPROM_IMPLEMENTATION_H
#define EEPROM_IMPLEMENTATION_H

/**@defgroup EEPROM_IMPLEMENTATION EepromImplementation
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/** Size of fake eeprom region */
#define EEPROM_MEMORY_SIZE  2048

/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** EEPROM structure when using fake eeprom */
struct _eeprom {
    uint8_t memory[EEPROM_MEMORY_SIZE];
    uint32_t size;
};

/** Dummy eeprom instance */
typedef struct _eeprom eeprom_t;

/** Dummy eeprom configuration*/
typedef uint32_t eeprom_config_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** @} defgroup EEPROM_IMPLEMENTATION */

#endif /* ifndef EEPROM_IMPLEMENTATION_H */
