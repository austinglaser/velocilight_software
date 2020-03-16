/**@file    i2c_al_port.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   I2C_ALPort Source
 *
 * @addtogroup I2C_AL_PORT
 * @{
 *
 * @defgroup I2C_AL_PORT_PRIVATE I2C_AL ChibiOS Port Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

#include "i2c_al_port.h"

#include "i2c_al.h"
#include "ensure.h"
#include "error.h"
#include "util.h"

#include "pal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */

/** I2C errors we classify as hardware errors */
#define I2C_AL_HW_ERROR_MASK   (I2C_BUS_ERROR \
                                 | I2C_OVERRUN)

/** I2C errors we classify as communication errors */
#define I2C_AL_COMM_ERROR_MASK (I2C_ARBITRATION_LOST \
                                 | I2C_ACK_FAILURE    \
                                 | I2C_PEC_ERROR      \
                                 | I2C_TIMEOUT)


/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */

/** Handle a possible error condition after an i2c operation.
 *
 * @note    If bus sharing is enabled, this must be called before releasing the
 *          bus from the operation.
 *
 * @param[in] i2c:      The instance handle on which the operation ocurred
 * @param[in] result:   The result code from the operation
 *
 * @return      An error code
 * @retval  ERROR_NONE:     No error ocurred
 * @retval  ERROR_HW:       Something went wrong with hardware peripheral
 * @retval  ERROR_COMM:     Communication. Caused when receiving an unexpected
 *                          NACK from a slave, or possibly by other conditions
 * @retval  ERROR_TIMEOUT:  Timed out waiting for data
 */
static err_t _i2c_al_detect_error(i2c_al_t * i2c, msg_t result);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

err_t i2c_al_init(i2c_al_t * i2c, i2c_al_config_t const * config)
{
    ensure(i2c    != NULL);
    ensure(config != NULL);

    i2c->config = config;

    if (!i2c->config->share_bus) {
        i2cStart(i2c->config->hw_driver, i2c->config->hw_config);
    }

    /* Unconditional success because i2cStart returns no error code */
    return ERROR_NONE;
}

err_t i2c_al_transfer(i2c_al_t * i2c,
                      uint8_t dev_addr,
                      uint8_t const * write_data,
                      size_t write_len,
                      uint8_t * read_data,
                      size_t read_len)
{
    return i2c_al_transfer_timeout(i2c, dev_addr,
                                   write_data, write_len,
                                   read_data,  read_len,
                                   TIME_INFINITE);
}

err_t i2c_al_transfer_timeout(i2c_al_t * i2c,
                              uint8_t dev_addr,
                              uint8_t const * write_data,
                              size_t write_len,
                              uint8_t * read_data,
                              size_t read_len,
                              uint32_t timeout)
{
    ensure(i2c != NULL);
    ensure(write_data != NULL);
    ensure(write_len > 0);
    ensure(read_len == 0 || read_data != NULL);

    if (i2c->config->share_bus) {
        i2cAcquireBus(i2c->config->hw_driver);
        i2cStart(i2c->config->hw_driver, i2c->config->hw_config);
    }

    msg_t result = i2cMasterTransmitTimeout(i2c->config->hw_driver,
                                            dev_addr,
                                            write_data, write_len,
                                            read_data,  read_len,
                                            timeout);

    err_t error = _i2c_al_detect_error(i2c, result);

    if (i2c->config->share_bus) {
        i2cReleaseBus(i2c->config->hw_driver);
    }

    return error;
}

err_t i2c_al_read(i2c_al_t * i2c,
                  uint8_t dev_addr,
                  uint8_t * read_data,
                  size_t read_len)
{
    return i2c_al_read_timeout(i2c, dev_addr,
                                read_data, read_len,
                                TIME_INFINITE);
}

err_t i2c_al_read_timeout(i2c_al_t * i2c,
                         uint8_t dev_addr,
                         uint8_t * read_data,
                         size_t read_len,
                         uint32_t timeout)
{
    ensure(i2c != NULL);
    ensure(read_data != NULL);
    ensure(read_len > 0);

    if (i2c->config->share_bus) {
        i2cAcquireBus(i2c->config->hw_driver);
        i2cStart(i2c->config->hw_driver, i2c->config->hw_config);
    }

    msg_t result = i2cMasterReceiveTimeout(i2c->config->hw_driver,
                                           dev_addr,
                                           read_data, read_len,
                                           timeout);

    err_t error = _i2c_al_detect_error(i2c, result);

    if (i2c->config->share_bus) {
        i2cReleaseBus(i2c->config->hw_driver);
    }

    return error;
}

err_t i2c_al_write(i2c_al_t * i2c,
                   uint8_t dev_addr,
                   uint8_t const * write_data,
                   size_t write_len)
{
    return i2c_al_transfer(i2c, dev_addr, write_data, write_len, NULL, 0);;
}

err_t i2c_al_write_timeout(i2c_al_t * i2c,
                           uint8_t dev_addr,
                           uint8_t const * write_data,
                           size_t write_len,
                           uint32_t timeout)
{
    return i2c_al_transfer_timeout(i2c, dev_addr,
                                   write_data, write_len,
                                   NULL, 0,
                                   timeout);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static err_t _i2c_al_detect_error(i2c_al_t * i2c, msg_t result)
{
    if (result == MSG_TIMEOUT) {
        return ERROR_TIMEOUT;
    } else if (result != MSG_OK) {
        i2cflags_t err_flags = i2cGetErrors(i2c->config->hw_driver);

        if (err_flags & I2C_AL_HW_ERROR_MASK) {
            return ERROR_HW;
        } else if (err_flags & I2C_AL_COMM_ERROR_MASK) {
            return ERROR_COMM;
        }
    }

    return ERROR_NONE;
}

/** @} defgroup I2C_AL_PORT_PRIVATE */
/** @} addtogroup I2C_AL_PORT */
