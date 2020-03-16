/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   MPU9250 nRF5 port implementation
///
/// @addtogroup MPU9250_PORT
/// @{
///
/// @defgroup MPU9250_PORT_PRIVATE MPU9250Port Private Members
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// This module
#include "mpu9250_port.h"
#include "mpu9250_registers.h"

// Supporting modules
#include "ensure.h"
#include "util.h"

// Third-party headers

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //
// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //
// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

void mpu9250_port_init(
    mpu9250_port_t * port,
    mpu9250_port_config_t const * config
) {
    ensure(port != NULL);
    ensure(config != NULL);
    ensure(config->twi != NULL);

    port->twi = config->twi;
    port->i2c_addr = MPU9250_I2C_ADDR | config->ad0;
}

err_t mpu9250_port_read_reg(
    mpu9250_port_t const * port,
    uint8_t addr,
    uint8_t * value
) {
    ensure(port != NULL);
    ensure(port->twi != NULL);
    ensure(addr < MPU9250_REGISTER_COUNT);
    ensure(value != NULL);

    ret_code_t err;
    err = nrf_drv_twi_tx(port->twi, port->i2c_addr, &addr, 1, true);
    if (err != NRF_SUCCESS) {
        return ERROR_COMM;
    }

    err = nrf_drv_twi_rx(port->twi, port->i2c_addr, value, 1);
    if (err != NRF_SUCCESS) {
        return ERROR_COMM;
    }

    return ERROR_NONE;
}

err_t mpu9250_port_write_reg(
    mpu9250_port_t const * port,
    uint8_t addr,
    uint8_t value
) {
    ensure(port != NULL);
    ensure(port->twi != NULL);
    ensure(addr < MPU9250_REGISTER_COUNT);

    uint8_t tx[] = {
        [0] = addr,
        [1] = value,
    };

    ret_code_t err = nrf_drv_twi_tx(
        port->twi,
        port->i2c_addr,
        tx,
        ARRAY_ELEMENTS(tx),
        false
    );

    return err == NRF_SUCCESS ? ERROR_NONE : ERROR_COMM;
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

/// @} defgroup MPU9250_PORT_PRIVATE
/// @} addtogroup MPU9250_PORT
