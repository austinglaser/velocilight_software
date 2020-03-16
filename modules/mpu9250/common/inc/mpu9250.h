/**@file    mpu9250.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   MPU9250 Driver Interface
 */

#ifndef MPU9250_H
#define MPU9250_H

/**@defgroup MPU9250 MPU9250 Driver
 * @{
 *
 * @brief Portable driver for InvenSense's MPU9250 IMU
 *
 * The MPU9250 incorporates a 3-axis accelerometer, gyroscope, and
 * magnetometer.
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */
#include "error.h"
#include "mpu9250_port.h"

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */

/** Possible full-scale range configurations for accelerometer */
typedef enum {
    MPU9250_ACCEL_FS_2,     /**< +/- 2G */
    MPU9250_ACCEL_FS_4,     /**< +/- 4G */
    MPU9250_ACCEL_FS_8,     /**< +/- 8G */
    MPU9250_ACCEL_FS_16,    /**< +/- 16G */
} mpu9250_accel_fs_t;

/** Accelerometer sample rates and filter bandwidths */
typedef enum {
    /** Sample rate: 1k samples/second. Bandwidth: 5 Hz */
    MPU9250_ACCEL_SAMPLERATE_1k_5Hz,

    /** Sample rate: 1k samples/second. Bandwidth: 10 Hz */
    MPU9250_ACCEL_SAMPLERATE_1k_10Hz,

    /** Sample rate: 1k samples/second. Bandwidth: 20 Hz */
    MPU9250_ACCEL_SAMPLERATE_1k_20Hz,

    /** Sample rate: 1k samples/second. Bandwidth: 41 Hz */
    MPU9250_ACCEL_SAMPLERATE_1k_41Hz,

    /** Sample rate: 1k samples/second. Bandwidth: 92 Hz */
    MPU9250_ACCEL_SAMPLERATE_1k_92Hz,

    /** Sample rate: 1k samples/second. Bandwidth: 184 Hz */
    MPU9250_ACCEL_SAMPLERATE_1k_184Hz,

    /** Sample rate: 1k samples/second. Bandwidth: 460 Hz */
    MPU9250_ACCEL_SAMPLERATE_1k_460Hz,

    /** Sample rate: 4k samples/second. Bandwidth: 1.13 kHz */
    MPU9250_ACCEL_SAMPLERATE_4k_1130Hz,
} mpu9250_accel_samplerate_t;

/** Possible full-scale range configurations for gyroscope */
typedef enum {
    MPU9250_GYRO_FS_250,    /**< +/- 250 degrees/sec */
    MPU9250_GYRO_FS_500,    /**< +/- 500 degrees/sec */
    MPU9250_GYRO_FS_1000,   /**< +/- 1000 degrees/sec */
    MPU9250_GYRO_FS_2000,   /**< +/- 2000 degrees/sec */
} mpu9250_gyro_fs_t;

/** Gyroscope sample rates and low-pass filter cutoffs */
typedef enum {
    /** Sample rate: 1k samples/second. Filter cutoff: 5 Hz */
    MPU9250_GYRO_SAMPLERATE_1k_5Hz,

    /** Sample rate: 1k samples/second. Filter cutoff: 10 Hz */
    MPU9250_GYRO_SAMPLERATE_1k_10Hz,

    /** Sample rate: 1k samples/second. Filter cutoff: 20 Hz */
    MPU9250_GYRO_SAMPLERATE_1k_20Hz,

    /** Sample rate: 1k samples/second. Filter cutoff: 41 Hz */
    MPU9250_GYRO_SAMPLERATE_1k_41Hz,

    /** Sample rate: 1k samples/second. Filter cutoff: 92 Hz */
    MPU9250_GYRO_SAMPLERATE_1k_92Hz,

    /** Sample rate: 1k samples/second. Filter cutoff: 184 Hz */
    MPU9250_GYRO_SAMPLERATE_1k_184Hz,

    /** Sample rate: 8k samples/second. Filter cutoff: 250 Hz */
    MPU9250_GYRO_SAMPLERATE_8k_250Hz,

    /** Sample rate: 8k samples/second. Filter cutoff: 3.6 kHz */
    MPU9250_GYRO_SAMPLERATE_8k_3600Hz,

    /** Sample rate: 32k samples/second. Filter cutoff: 3.6 kHz */
    MPU9250_GYRO_SAMPLERATE_32k_3600Hz,

    /** Sample rate: 32k samples/second. Filter cutoff: 8.8 kHz */
    MPU9250_GYRO_SAMPLERATE_32k_8800Hz,
} mpu9250_gyro_samplerate_t;

/* --- PUBLIC DATATYPES ---------------------------------------------------- */

/** MPU9250 handle
 *
 * This forward declaration is necessary to allow definition of the callback
 * type.
 */
typedef struct mpu9250 mpu9250_t;

/** INT pin callback function signature */
typedef void (* mpu9250_intcb_t)(mpu9250_t *);

/** A structure encoding a 3-axis set of measurements */
typedef struct {
    int32_t x;  /**< X-axis value */
    int32_t y;  /**< Y-axis value */
    int32_t z;  /**< Z-axis value */
} mpu9250_axes_t;

/** A single reading from the IMU
 *
 * @note    Depending on the system settings, not all fields will be used
 */
typedef struct {
    mpu9250_axes_t accel; /**< Acceleration */
    mpu9250_axes_t gyro;  /**< Gyroscope */
    int32_t temp;         /**< Temperature */
} mpu9250_sample_t;

/** Configuration for the MPU9250 */
typedef struct {
    /** Set accelerometer full-scale range */
    mpu9250_accel_fs_t          accel_fs;

    /** Set the gyroscope's sample rate and filter cutoff frequency
     *
     * @note    This is an internal sample rate, controlling how often the
     *          sensor's are actually read. The output data rate may be
     *          different depending on the value in SMPLRT_DIV.
     */
    mpu9250_accel_samplerate_t  accel_samplerate;

    /** Set gyroscope full-scale range */
    mpu9250_gyro_fs_t           gyro_fs;

    /** Set the gyroscope's sample rate and filter cutoff frequency */
    mpu9250_gyro_samplerate_t   gyro_samplerate;

    /** Callback to use for INT assertions
     *
     * This callback will be called in an interrupt context -- if the system
     * needs to use any blocking functions, it should transfer control to a
     * thread-context function before doing so.
     *
     * Can be NULL if unused
     */
    mpu9250_intcb_t             int_cb;

    /** Initial setting for SMPLRT_DIV
     *
     * Will divide the output data rate (see accel_samplerate and
     * gyro_samplerate), but ONLY if a 1k sample/second sample rate is selected
     * for both the accelerometer and the gyroscope.
     *
     * The output sample rate can be calculated using the following formula:
     *
     * output_sample_rate = internal_sample_rate / (1 + SMPLRT_DIV)
     *
     * The internal sample rate is configured using @ref
     * mpu9250_config_t.accel_samplerate and @ref
     * mpu9250_config.gyro_samplerate.
     *
     * @see MPU9250_SMPLRT_DIV
     */
    uint8_t                     smplrt_div;

    /** Initial setting for CONFIG
     *
     * The DLPF_CFG field is protected for use internal to the driver
     *
     * @see MPU9250_CONFIG
     */
    uint8_t                     config;

    /** Initial setting for LP_ACCEL_ODR
     *
     * Must be <= 11
     *
     * @see MPU9250_LP_ACCEL_ODR
     */
    uint8_t                     lp_accel_odr;

    /** Initial setting for WOM_THR
     *
     * LSB is 4 mG
     *
     * More details can be found in the product specification (section 6.1)
     *
     * @see MPU9250_WOM_THR
     */
    uint8_t                     wom_thr;

    /** Initial setting for FIFO_EN
     *
     * Controls what data is written to the FIFO
     *
     * @see MPU9250_FIFO_EN
     */
    uint8_t                     fifo_en;

    /** Initial setting for INT_PIN_CFG register
     *
     *
     * @see MPU9250_INTERRUPT
     */
    uint8_t                     int_pin_cfg;

    /** Initial setting for INT_ENABLE register
     *
     *
     * @see MPU9250_INTERRUPT
     */
    uint8_t                     int_enable;

    /** Initial setting for MOT_DETECT_CTRL
     *
     * Activates wake-on-motion functionality
     *
     * @see MPU9250_MOT_DETECT_CTRL
     */
    uint8_t                     mot_detect_ctrl;

    /** Initial setting for USER_CTRL
     *
     * All *_RST (FIFO_RST, I2C_MST_RST, and SIG_COND_RST) bits are protected
     * for internal driver use, along with the I2C_IF_DIS bit.
     *
     * @see MPU9250_USER_CTRL
     */
    uint8_t                     user_ctrl;

    /** Initial setting for PWR_MGMT_1
     *
     * All fields except CLKSEL are protected for internal driver use.
     *
     * @see MPU9250_PWR_MGMT
     */
    uint8_t                     pwr_mgmt_1;

    /** Initial setting for PWR_MGMT_2
     *
     * This controls which sensing elements (which axes of the
     * accelerometer/gyro) are enabled.
     *
     * @see MPU9250_PWR_MGMT
     */
    uint8_t                     pwr_mgmt_2;

    /** Platform-specific configuration */
    mpu9250_port_config_t       port_config;
} mpu9250_config_t;

/** Handle for an MPU9250 */
struct mpu9250 {
    /** This IMU's configuration */
    mpu9250_config_t const * config;

    /** A port handle for this IMU */
    mpu9250_port_t port;
};

/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Initialize an mpu9250 instance and the corresponding hardware
 *
 * @param[out] imu:     MPU9250 handle to initialize
 * @param[in] config:   IMU configuration
 *
 * @return An error code
 */
err_t mpu9250_init(mpu9250_t * imu, mpu9250_config_t const * config);

/** Perform a self-test on the MPU9250
 *
 * @note    Uses the registers SELF_TEST_[XYZ]_(GYRO|ACCEL), which are not
 *          otherwise available for user access
 *
 * @param[in] imu:      MPU9250 to test
 *
 * @retval ERROR_NONE:  The test succeeded
 * @retval ERROR_HW:    The test failed
 * @retval ERROR_COMM:  The test could not be performed
 */
err_t mpu9250_self_test(mpu9250_t * imu);

/** Reset the onboard hardware FIFO
 *
 * @param[in] imu:      Which IMU to operate on
 *
 * @retval ERROR_NONE:  The FIFO was reset
 * @retval ERROR_COMM:  The FIFO could not be reset
 */
err_t mpu9250_fifo_reset(mpu9250_t * imu);

/** Set the hardware offset values on the IMU
 *
 * The values in @p offset are treated differently based on the device. This
 * behavior boils down the MPU9250 hardware design.
 *
 * For accelerometer values, only the least-significant 15 bits are used.
 * Offsets are in the range +/- 16 G -- each LSB has a value of 0.98 mG.
 *
 * For the gyroscope values, only the least-significant 16 bits are used. The
 * offset depends on the configured full-scale range of the gyroscope --
 * effectively, the offsets are in raw gyroscope units.
 *
 * The value for temperature is ignored by this function.
 *
 * @param[in] imu:      IMU to offset
 * @param[in] offset:   Structure containing the offset values
 *
 * @retval  ERROR_NONE  The offsets were set
 * @retval  ERROR_COMM  The offsets could not be set
 * @retval  ERROR_PARAM One or more of the offsets was outside the allowable
 *                      range (TODO: should this just be done with ensure()?)
 */
err_t mpu9250_set_offsets(mpu9250_t * imu, mpu9250_sample_t const * offset);

/** Get the current, instantaneous accelerometer reading
 *
 * Only the enabled axes/sensors from the MPU9250 will be set in @p sample. All
 * other fields will be left unchanged after a call to this function
 *
 * TODO: Reference where to go to enable/disable axes and sensors.
 *
 * @param[in] imu:      Accelerometer from which to read
 * @param[out] sample:  Returns the sample value
 *
 * @retval ERROR_NONE:  The sample was read
 * @retval ERROR_COMM:  The sample could not be retrieved
 */
err_t mpu9250_read(mpu9250_t const * imu, mpu9250_sample_t * sample);

/** Drains the FIFO on the IMU
 *
 * Reads samples from the hardware FIFO into the @p samples array. Reads the
 * minimum of @p n and the number of samples present in the FIFO. Sets @p n to
 * the number of samples actually read.
 *
 * The MPU9250 only supports a FIFO-overflow interrupt. This means that an
 * application relying on interrupts for reading the FIFO will always drop at
 * least one sample -- which may be acceptable, depending on the particular
 * use-case. The FIFO can also be configured to overwrite old samples,
 * providing the application a simple way to read a short history of motion
 * based on some external triggering event.
 *
 * However, in use-cases where this is *not* acceptable, the application should
 * periodically drain the FIFO, at an interval where the FIFO should be
 * approximately half full (this can be calculated based on the sample rate).
 * It should also enable the FIFO-overflow interrupt, so it can be notified
 * when samples are lost and take appropriate action.
 *
 * @param[in] imu:      IMU from which to read
 * @param[out] samples: Buffer for read samples
 * @param[in,out] n:    In: space in @p samples. Out: how many samples were
 *                      written.
 *
 * @retval ERROR_NONE:  The samples were read
 * @retval ERROR_NOENT: No samples were available (also n will be set to 0)
 * @retval ERROR_COMM:  The samples could not be retrieved
 */
err_t mpu9250_read_fifo(mpu9250_t * imu, mpu9250_sample_t * samples, size_t * n);

/** Converts @p sample into real-world units
 *
 * Converts the values in @p sample from raw ADC counts into mG (for
 * accel.[xyz]), mDegree/second (for gyro.[xyz]), or mC (for temp),
 *
 * This conversion is done based on the full-scale values in @p imu's config.
 *
 * @param[in] imu:          IMU to use
 * @param[in,out] sample:   Sample to convert
 */
void mpu9250_convert(mpu9250_t * imu, mpu9250_sample_t * sample);

/** Read the INT_STATUS register
 *
 * A read to this register clears the status. Additionally, the status may be
 * cleared by ANY read to the IMU if INT_ANYRD_2CLEAR is set in the INT_PIN_CFG
 * register. This functionality can be used when, for instance, only one
 * interrupt source is enabled, obviating the need to check the source before
 * acting on an interrupt.
 *
 * Because of the above, however, it's generally advisable for this to be the
 * first call in an INT-handling callback, when the callback does need to
 * discriminate between sources.
 *
 * @param[in] imu:          IMU to read status from
 * @param[out] status;      Interrupt status flags (the value in the INT_STATUS
 *                          register)
 *
 * @return ERROR_NONE:      Status was read successfully
 * @return ERROR_COMM:      Status could not be read
 */
err_t mpu9250_int_status(mpu9250_t * imu, uint8_t * int_status);

/** @} defgroup MPU9250 */

#endif /* ifndef MPU9250_H */
