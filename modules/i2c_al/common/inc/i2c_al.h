/**@file    i2c_al.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   I2C_AL Interface
 */

#ifndef I2C_AL_H
#define I2C_AL_H

/**@defgroup I2C_AL I2C Abstraction Layer
 * @{
 *
 * @brief   Abstraction layer for I2C implementations.
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

#include "i2c_al_port.h"

#include "error.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */

/** A top-level I2C handle */
typedef struct {
    i2c_al_config_t const * config;    /**< Determines the I2C's operation */
} i2c_al_t;

/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Initializes @p i2c
 *
 * @param[in,out] i2c:      Driver handle to initialize
 * @param[in] config:       Implementation-specific configuration
 *
 * After a call to this function, the i2c peripheral will be configured for
 * transfers.
 *
 * @param[in,out] i2c:      Handle to initialize
 * @parampin] config:       Configuration for driver
 *
 * @return      An error code
 * @retval      ERROR_NONE: Success
 * @retval      ERROR_HW:   The peripheral could not be initialized.
 */
err_t i2c_al_init(i2c_al_t * i2c, i2c_al_config_t const * config);

/** Transfers values on i2c bus, performing a write followed by a read
 *
 * Transmits all @p write_len bytes from @p write_data. Then reads @p read_len
 * bytes into @p read_data, if read_len is greater than zero.
 *
 * @p read_data may be NULL if @p read_data is zero. It is an error to set @p
 * read_data to NULL if @p read_data is > 0, or vice versa. In other words,
 * either both must be zero/NULL, or neither.
 *
 * Communicates with the device at @p dev_addr
 *
 * Waiting is accomplished using OS sleep (if the system is being run with an
 * RTOS), or with a spin-wait (assuming a non-OS system). In other words, if an
 * RTOS is present, other threads can progress while this function is blocking.
 *
 * @param[in] i2c:          I2C handle for the communication
 * @param[in] dev_addr:     Device address to access
 * @param[in] write_data:   Data to write
 * @param[in] write_len:    Length of @p write_data
 * @param[out] read_data:   Buffer to store read data, or NULL
 * @param[in] read_len:     Number of bytes to read into @p read_data
 *
 * @return      An error code
 * @retval  ERROR_NONE:     No error occurred
 * @retval  ERROR_HW:       Something went wrong with hardware peripheral
 * @retval  ERROR_COMM:     Communication. Caused when receiving an unexpected
 *                          NACK from a slave, or possibly by other conditions
 */
err_t i2c_al_transfer(i2c_al_t * i2c,
                      uint8_t dev_addr,
                      uint8_t const * write_data,
                      size_t write_len,
                      uint8_t * read_data,
                      size_t read_len);

/** Transfers values on i2c bus, failing if we wait too long
 *
 * Transmits all @p write_len bytes from @p write_data. Then reads @p read_len
 * bytes into @p read_data, if read_len is greater than zero.
 *
 * @p read_data may be NULL if @p read_data is zero. It is an error to set @p
 * read_data to NULL if @p read_data is > 0.
 *
 * Communicates with the device at @p dev_addr
 *
 * Waiting is accomplished using OS sleep (if the system is being run with an
 * RTOS), or with a spin-wait (assuming a non-OS system). In other words, if an
 * RTOS is present, other threads can progress while this function is blocking.
 *
 * @param[in] i2c:          I2C handle for the communication
 * @param[in] dev_addr:     Device address to access
 * @param[in] write_data:   Data to write
 * @param[in] write_len:    Length of @p write_data
 * @param[out] read_data:   Buffer to store read data, or NULL
 * @param[in] read_len:     Number of bytes to read into @p read_data
 * @param[in] timeout:      Time (in system ticks) to wait for data
 *
 * @return      An error code
 * @retval  ERROR_NONE:     No error occurred
 * @retval  ERROR_HW:       Something went wrong with hardware peripheral
 * @retval  ERROR_COMM:     Communication. Caused when receiving an unexpected
 *                          NACK from a slave, or possibly by other conditions
 * @retval  ERROR_TIMEOUT:  Timed out waiting for data
 */
err_t i2c_al_transfer_timeout(i2c_al_t * i2c,
                              uint8_t dev_addr,
                              uint8_t const * write_data,
                              size_t write_len,
                              uint8_t * read_data,
                              size_t read_len,
                              uint32_t timeout);

/** Reads values from i2c bus
 *
 * Reads @p read_len bytes into @p read_data.
 *
 * Communicates with the device at @p dev_addr
 *
 * Waiting is accomplished using OS sleep (if the system is being run with an
 * RTOS), or with a spin-wait (assuming a non-OS system). In other words, if an
 * RTOS is present, other threads can progress while this function is blocking.
 *
 * @param[in] i2c:          I2C handle for the communication
 * @param[in] dev_addr:     Device address to access
 * @param[out] read_data:   Buffer to store read data, or NULL
 * @param[in] read_len:     Number of bytes to read into @p read_data
 *
 * @return      An error code
 * @retval  ERROR_NONE:     No error occurred
 * @retval  ERROR_HW:       Something went wrong with hardware peripheral
 * @retval  ERROR_COMM:     Communication. Caused when receiving an unexpected
 *                          NACK from a slave, or possibly by other conditions
 */
err_t i2c_al_read(i2c_al_t * i2c,
                  uint8_t dev_addr,
                  uint8_t * read_data,
                  size_t read_len);

/** Reads values from i2c bus, timing out if we wait too long
 *
 * Reads @p read_len bytes into @p read_data.
 *
 * Communicates with the device at @p dev_addr
 *
 * Waiting is accomplished using OS sleep (if the system is being run with an
 * RTOS), or with a spin-wait (assuming a non-OS system). In other words, if an
 * RTOS is present, other threads can progress while this function is blocking.
 *
 * @param[in] i2c:          I2C handle for the communication
 * @param[in] dev_addr:     Device address to access
 * @param[out] read_data:   Buffer to store read data
 * @param[in] read_len:     Number of bytes to read into @p read_data
 *
 * @return      An error code
 * @retval  ERROR_NONE:     No error occurred
 * @retval  ERROR_HW:       Something went wrong with hardware peripheral
 * @retval  ERROR_COMM:     Communication. Caused when receiving an unexpected
 *                          NACK from a slave, or possibly by other conditions
 * @retval  ERROR_TIMEOUT:  Timed out waiting for data
 */
err_t i2c_al_read_timeout(i2c_al_t * i2c,
                         uint8_t dev_addr,
                         uint8_t * read_data,
                         size_t read_len,
                         uint32_t timeout);

/** Writes values to i2c bus, timing out after some period
 *
 * Waiting is accomplished using OS sleep (if the system is being run with an
 * RTOS), or with a spin-wait (assuming a non-OS system). In other words, if an
 * RTOS is present, other threads can progress while this function is blocking.
 *
 * @param[in] i2c:         I2C handle for the communication
 * @param[in] dev_addr:    Device address to access
 * @param[in] write_data:  Data to write data
 * @param[in] write_len:   Number of bytes to read into @p read_data
 *
 * @return      An error code
 * @retval  ERROR_NONE:     No error occurred
 * @retval  ERROR_HW:       Something went wrong with hardware peripheral
 * @retval  ERROR_COMM:     Communication. Caused when receiving an unexpected
 *                          NACK from a slave, or possibly by other conditions
 * @retval  ERROR_TIMEOUT:  Timed out waiting for data
 */
err_t i2c_al_write_timeout(i2c_al_t * i2c,
                           uint8_t dev_addr,
                           uint8_t const * write_data,
                           size_t write_len,
                           uint32_t timeout);

/** Writes values to i2c bus
 *
 * Waiting is accomplished using OS sleep (if the system is being run with an
 * RTOS), or with a spin-wait (assuming a non-OS system). In other words, if an
 * RTOS is present, other threads can progress while this function is blocking.
 *
 * @param[in] i2c:         I2C handle for the communication
 * @param[in] dev_addr:    Device address to access
 * @param[in] write_data:  Data to write data
 * @param[in] write_len:   Number of bytes to read into @p read_data
 *
 * @return      An error code
 * @retval  ERROR_NONE:     No error occurred
 * @retval  ERROR_HW:       Something went wrong with hardware peripheral
 * @retval  ERROR_COMM:     Communication. Caused when receiving an unexpected
 *                          NACK from a slave, or possibly by other conditions
 */
err_t i2c_al_write(i2c_al_t * i2c,
                   uint8_t dev_addr,
                   uint8_t const * write_data,
                   size_t write_len);

/** @} defgroup I2C_AL */

#endif /* ifndef I2C_AL_H */
