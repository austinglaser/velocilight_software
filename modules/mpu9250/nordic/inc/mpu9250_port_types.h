/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   MPU9250 nRF5 port datatypes

#ifndef MPU9250_PORT_TYPES_H
#define MPU9250_PORT_TYPES_H

/// @defgroup MPU9250_PORT_TYPES MPU9250 Port Types
/// @{
///
/// @brief Datatypes for MPU9250 hardware port

// --- PUBLIC DEPENDENCIES ------------------------------------------------- //

// Supporting modules

// Third-party headers
#include "nrf_drv_twi.h"

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PUBLIC CONSTANTS ---------------------------------------------------- //
// --- PUBLIC DATATYPES ---------------------------------------------------- //

/// Configuration for an nRF5 MPU9250 hardware port.
typedef struct {
    /// Pre-initialized and enabled TWI driver on which to find IMU.
    nrf_drv_twi_t const * twi;

    /// Logical state of the AD0 pin.
    ///
    /// Effects the I2C address at which the IMU responds.
    bool ad0;
} mpu9250_port_config_t;

/// nRF5 MPU9250 port handle.
typedef struct {
    /// Pre-initialized and enabled TWI driver on which to find IMU.
    nrf_drv_twi_t const * twi;

    /// I2C address at which to find the IMU.
    uint8_t i2c_addr;
} mpu9250_port_t;

// --- PUBLIC MACROS ------------------------------------------------------- //
// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

/// @} defgroup MPU9250_PORT_TYPES

#endif // ifndef MPU9250_PORT_TYPES_H
