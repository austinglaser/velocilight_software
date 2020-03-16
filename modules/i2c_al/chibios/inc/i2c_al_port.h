/**@file    i2c_al_port.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   I2C_ALPort Interface
 */

#ifndef I2C_AL_PORT_H
#define I2C_AL_PORT_H

/**@defgroup I2C_AL_PORT I2C_AL ChibOS Port
 * @{
 *
 * @brief   Implementaton of @ref I2C_AL for use on ChibiOS platforms.
 *
 * Basically just a wrapper around ChibiOS-HAL's I2C module.
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

#include "hal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */

/** An I2C handle's configuration
 *
 * Since this port basically just wraps the ChibiOS hal, the configuration
 * specifies which  i2c driver to use, and how to configure it.
 */
typedef struct {
    I2CDriver *       hw_driver;    /**< Backing hardware driver */
    I2CConfig const * hw_config;    /**< That driver's config */
    bool              share_bus;    /**< Whether this bus is accessed by
                                     *   multiple threads which need
                                     *   syncronization
                                     */
} i2c_al_config_t;

/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** @} defgroup I2C_AL_PORT */

#endif /* ifndef I2C_AL_PORT_H */
