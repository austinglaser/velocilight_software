/**@file    fake_mpu9250_port.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Mpu9250PortFake Interface
 */

#ifndef MPU9250_PORT_FAKE_H
#define MPU9250_PORT_FAKE_H

/**@defgroup MPU9250_PORT_FAKE Mpu9250PortFake
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */
#include "mpu9250_port.h"

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

/** Sets up the fake port
 *
 * Should be used to re-configure the port in between tests
 *
 * Resets "registers" to datasheet initial values
 *
 * Installs callbacks as the apporpriate stubs
 *
 * @param[out] port:    Fake to setup
 */
void fake_mpu9250_port_setup(mpu9250_port_t * port);

/** Cleans up @p port
 *
 * Releases resources used by @p port
 *
 * @param[in] port:     Port to clean up
 */
void fake_mpu9250_port_teardown(mpu9250_port_t * port);

/** Determine whether @p port was initialized since the last setup
 *
 * @param[in] port:     Fake port to check
 *
 * @return      Whether @ref mpu9250_port_init has been called
 */
bool fake_mpu9250_port_was_initialized(mpu9250_port_t const * port);

/** Determine whether @p port was reset since the last setup
 *
 * @param[in] port:     Fake port to check
 *
 * @return      Whether PWR_MGMT_1.H_RESET was written high at any point
 */
bool fake_mpu9250_port_was_reset(mpu9250_port_t const * port);

/** Get a reference to this port's config struct
 *
 * @param[in] port:     Fake port to check
 *
 * @return      The config struct that was passed to @ref mpu9250_port_init
 */
mpu9250_port_config_t const *
fake_mpu9250_port_config(mpu9250_port_t const * port);

/** Get the current value of a fake register
 *
 * @param[in] port:     Fake port to read
 * @param[in] addr:     Address to get
 *
 * @return      Value of reg[addr]
 */
uint8_t fake_mpu9250_port_get_reg(mpu9250_port_t const * port, uint8_t addr);

/** Set the current value of a fake register
 *
 * @param[in] port:     Fake port to write
 * @param[in] addr:     Address to set
 * @param[in] value:    Data to write
 */
void fake_mpu9250_port_set_reg(mpu9250_port_t const * port,
                               uint8_t addr,
                               uint8_t value);

/** @} defgroup MPU9250_PORT_FAKE */

#endif /* ifndef MPU9250_PORT_FAKE_H */
