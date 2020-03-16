/**@file    mpu9250_port.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Mpu9250 Port Interface
 */

#ifndef MPU9250_PORT_H
#define MPU9250_PORT_H

/**@defgroup MPU9250_PORT Mpu9250 ChibiOS Port
 * @{
 *
 * @brief Platform-dependent functions for interfacing with an MPU9250
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */
#include "error.h"
#include "mpu9250_port_types.h"

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Initialize @p port according to @p config */
void mpu9250_port_init(mpu9250_port_t * port,
                       mpu9250_port_config_t const * config);

/** Read a single register from an MPU9250
 *
 * @param[in] port:     Hardware on which to find MPU9250
 * @param[in] addr:     Register address to use
 * @param[out] value:   Value of the register
 *
 * @retval ERROR_NONE:  Register was read, value in @p value
 * @retval ERROR_COMM:  Could not communicate with MPU9250
 */
err_t mpu9250_port_read_reg(mpu9250_port_t const * port,
                            uint8_t addr,
                            uint8_t * value);

/** Write a single register on an MPU9250
 *
 * @param[in] port:     Hardware on which to find MPU9250
 * @param[in] addr:     Register address to use
 * @param[in] value:    New Value of the register
 *
 * @retval ERROR_NONE:  Register was written
 * @retval ERROR_COMM:  Could not communicate with MPU9250
 */
err_t mpu9250_port_write_reg(mpu9250_port_t const * port,
                             uint8_t addr,
                             uint8_t value);

/** @} defgroup MPU9250_PORT */

#endif /* ifndef MPU9250_PORT_H */
