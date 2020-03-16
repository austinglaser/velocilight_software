/**@file    mpu9250_port.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Mpu9250Port Source
 *
 * @addtogroup MPU9250_PORT
 * @{
 *
 * @defgroup MPU9250_PORT_PRIVATE Mpu9250Port Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "mpu9250_port.h"
#include "mpu9250_registers.h"

/* Supporting modules */
#include "ensure.h"

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */

/** A single MPU9250 register access */
typedef struct {
    uint8_t addr;       /**< Address to read/write */
    uint8_t value;      /**< Value read/to write */
} __attribute__((packed)) mpu9250_reg_access_t;

/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void mpu9250_port_init(mpu9250_port_t * port,
                       mpu9250_port_config_t const * config)
{
    ensure(port != NULL);
    ensure(config != NULL);

    port->config = config;
}

err_t mpu9250_port_read_reg(mpu9250_port_t const * port,
                            uint8_t addr,
                            uint8_t * value)
{
    ensure(port != NULL);
    ensure(port->config != NULL);
    ensure(addr < MPU9250_REGISTER_COUNT);
    ensure(value != NULL);

    mpu9250_reg_access_t read;
    mpu9250_reg_access_t write = {
        .addr  = addr | MPU9250_READ,
        .value = 0x00,
    };

    spiSelect(port->config->spid);
    spiExchange(port->config->spid, sizeof(write), &write, &read);
    spiUnselect(port->config->spid);

    *value = read.value;

    return ERROR_NONE;
}

err_t mpu9250_port_write_reg(mpu9250_port_t const * port,
                             uint8_t addr,
                             uint8_t value)
{
    ensure(port != NULL);
    ensure(port->config != NULL);
    ensure(addr < MPU9250_REGISTER_COUNT);

    mpu9250_reg_access_t write = {
        .addr = addr,
        .value = value,
    };

    spiSelect(port->config->spid);
    spiSend(port->config->spid, sizeof(write), &write);
    spiUnselect(port->config->spid);

    return ERROR_NONE;
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup MPU9250_PORT_PRIVATE */
/** @} addtogroup MPU9250_PORT */
