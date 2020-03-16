/**@file    mpu9250_port_types.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Mpu9250PortTypes Interface
 */

#ifndef MPU9250_PORT_TYPES_H
#define MPU9250_PORT_TYPES_H

/**@defgroup MPU9250_PORT_TYPES Mpu9250PortTypes
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */

/* Third-party headers */
#include "hal.h"

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */

/** Configuration for an ChibiOS MPU9250 hardware port */
typedef struct {
    SPIDriver * spid;   /**< SPI driver to use */
} mpu9250_port_config_t;

/** MPU9250 ChibiOS port handle */
typedef struct {
    mpu9250_port_config_t const * config;   /**< This port's config */
} mpu9250_port_t;

/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** @} defgroup MPU9250_PORT_TYPES */

#endif /* ifndef MPU9250_PORT_TYPES_H */
