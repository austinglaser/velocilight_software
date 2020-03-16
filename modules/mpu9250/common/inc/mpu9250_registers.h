/**@file    mpu9250_registers.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   MPU9250 Register Definition
 */

#ifndef MPU9250_REGISTERS_H
#define MPU9250_REGISTERS_H

/**@addtogroup MPU9250
 * @{
 */

/**@defgroup MPU9250_REGISTERS MPU9250 Registers
 * @{
 *
 * @brief Register definition for MPU9250
 *
 * For details, see the MPU9250 Register Map
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */

/** I2C address (in lowest 7 bits, and with AD0 cleared) */
#define MPU9250_I2C_ADDR                                0x68

/** Bit set in address to indicate a read to a register */
#define MPU9250_READ                                    0x80

/** Size of MPU9250's register file */
#define MPU9250_REGISTER_COUNT                          128

/** @defgroup MPU9250_SELF_TEST_GYRO SELF_TEST_GYRO registers
 * @{
 *
 * @brief   Used to perform self tests of the gyroscope system
 */

/** SELF_TEST_X_GYRO address */
#define MPU9250_SELF_TEST_X_GYRO                        0x00

/** SELF_TEST_Y_GYRO address */
#define MPU9250_SELF_TEST_Y_GYRO                        0x01

/** SELF_TEST_Z_GYRO address */
#define MPU9250_SELF_TEST_Z_GYRO                        0x02

/** @} */

/** @defgroup MPU9250_SELF_TEST_ACCEL SELF_TEST_ACCEL registers
 * @{
 *
 * @brief   Used to perform self-tests of the accelerometer system
 */

/** SELF_TEST_X_ACCEL address */
#define MPU9250_SELF_TEST_X_ACCEL                       0x0D

/** SELF_TEST_Y_ACCEL address */
#define MPU9250_SELF_TEST_Y_ACCEL                       0x0E

/** SELF_TEST_Z_ACCEL address */
#define MPU9250_SELF_TEST_Z_ACCEL                       0x0F

/** @} */

/** @defgroup MPU9250_GYRO_OFFSET GYRO_OFFSET registers
 * @{
 *
 * @brief   Used to set an offset on the gyroscope axes
 *
 * Each axis is broken into a high and a low byte
 *
 * @note All offsets are in raw gyroscope units
 */

/** XG_OFFSET_H address */
#define MPU9250_XG_OFFSET_H                             0x13

/** XG_OFFSET_L address */
#define MPU9250_XG_OFFSET_L                             0x14

/** YG_OFFSET_H address */
#define MPU9250_YG_OFFSET_H                             0x15

/** YG_OFFSET_L address */
#define MPU9250_YG_OFFSET_L                             0x16

/** ZG_OFFSET_H address */
#define MPU9250_ZG_OFFSET_H                             0x17

/** ZG_OFFSET_L address */
#define MPU9250_ZG_OFFSET_L                             0x18

/** @} */

/** @defgroup MPU9250_SMPLRT_DIV SMPLRT_DIV register
 * @{
 *
 * @brief Divides the internal sample rate to produce the output rate
 */

/** SMPLRT_DIV address */
#define MPU9250_SMPLRT_DIV                              0x19

/** @} */

/** @defgroup MPU9250_CONFIG CONFIG registers
 * @{
 *
 * @brief   General configuration options
 */

/** CONFIG address */
#define MPU9250_CONFIG                                  0x1A

/** Reserved bits in CONFIG */
#define MPU9250_CONFIG_RESERVED_MASK                    0x80

/** @name Whether to overwrite FIFO data in case of an overrun
 * @{
 */

/** Mask for FIFO_MODE bit */
#define MPU9250_CONFIG_FIFO_MODE_MASK                   0x40
/** Discard data on overrun */
#define MPU9250_CONFIG_FIFO_MODE_OVERWRITE              0x00
/** Preserve data on overrun */
#define MPU9250_CONFIG_FIFO_MODE_PRESERVE               0x40

/** @} */

/** @name Location for FSYNC bit latching, if enabled
 * @{
 */

/** Mask for EXT_SYNC_SET bits */
#define MPU9250_CONFIG_EXT_SYNC_SET_MASK                0x38
/** Don't activate the EXT_SYNC feature */
#define MPU9250_CONFIG_EXT_SYNC_SET_OFF                 0x00
/** Store the latched FSYNC value in TEMP_OUT_L[0]  */
#define MPU9250_CONFIG_EXT_SYNC_SET_TEMP_OUT_L0         0x08
/** Store the latched FSYNC value in GYRO_XOUT_L[0]  */
#define MPU9250_CONFIG_EXT_SYNC_SET_GYRO_XOUT_L0        0x10
/** Store the latched FSYNC value in GYRO_YOUT_L[0]  */
#define MPU9250_CONFIG_EXT_SYNC_SET_GYRO_YOUT_L0        0x18
/** Store the latched FSYNC value in GYRO_ZOUT_L[0]  */
#define MPU9250_CONFIG_EXT_SYNC_SET_GYRO_ZOUT_L0        0x20
/** Store the latched FSYNC value in ACCEL_XOUT_L[0]  */
#define MPU9250_CONFIG_EXT_SYNC_SET_ACCEL_XOUT_L0       0x28
/** Store the latched FSYNC value in ACCEL_YOUT_L[0]  */
#define MPU9250_CONFIG_EXT_SYNC_SET_ACCEL_YOUT_L0       0x30
/** Store the latched FSYNC value in ACCEL_ZOUT_L[0]  */
#define MPU9250_CONFIG_EXT_SYNC_SET_ACCEL_ZOUT_L0       0x38

/** @} */

/** @name Gyroscope digital low-pass filter configuration
 * @{
 *
 * @note    The value in this field is only used if FCHOICE_B is 2'b00
 */

/** Mask for DLPF_CFG bits */
#define MPU9250_CONFIG_DLPF_CFG_MASK                    0x07
/** Set the gyro's digital low-pass filter bandwidth to 250 Hz (4000 Hz for
 * temperature sensor) */
#define MPU9250_CONFIG_DLPF_CFG_250HZ                   0x00
/** Set the gyro's digital low-pass filter bandwidth to 184 Hz (188 Hz for
 * temperature sensor) */
#define MPU9250_CONFIG_DLPF_CFG_184HZ                   0x01
/** Set the gyro's digital low-pass filter bandwidth to 92 Hz (98 Hz for
 * temperature sensor) */
#define MPU9250_CONFIG_DLPF_CFG_92HZ                    0x02
/** Set the gyro's digital low-pass filter bandwidth to 41 Hz (42 Hz for
 * temperature sensor) */
#define MPU9250_CONFIG_DLPF_CFG_41HZ                    0x03
/** Set the gyro's digital low-pass filter bandwidth to 20 Hz (20 Hz for
 * temperature sensor) */
#define MPU9250_CONFIG_DLPF_CFG_20HZ                    0x04
/** Set the gyro's digital low-pass filter bandwidth to 10 Hz (10 Hz for
 * temp sensor) */
#define MPU9250_CONFIG_DLPF_CFG_10HZ                    0x05
/** Set the gyro's digital low-pass filter bandwidth to 5 Hz (5 Hz for temp
 * sensor) */
#define MPU9250_CONFIG_DLPF_CFG_5HZ                     0x06
/** Set the gyro's digital low-pass filter bandwidth to 3600 Hz (4000 Hz
 * for temp sensor) */
#define MPU9250_CONFIG_DLPF_CFG_3600HZ                  0x07

/** @} */

/** GYRO_CONFIG address */
#define MPU9250_GYRO_CONFIG                             0x1B

/** @name Gyro self-test enable
 * @{
 */

/** Enable self-test on the X axis of the gyro */
#define MPU9250_GYRO_CONFIG_XGYRO_CTEN                  0x80
/** Enable self-test on the Y axis of the gyro */
#define MPU9250_GYRO_CONFIG_YGYRO_CTEN                  0x40
/** Enable self-test on the Z axis of the gyro */
#define MPU9250_GYRO_CONFIG_ZGYRO_CTEN                  0x20

/** @} */

/** @name Gyroscope full-scale range configuration
 * @{
 */

/** Mask for GYRO_FS_SEL field */
#define MPU9250_GYRO_CONFIG_GYRO_FS_SEL_MASK            0x18
/** Set full-scall range to +/-250 degrees/second */
#define MPU9250_GYRO_CONFIG_GYRO_FS_SEL_250DPS          0x00
/** Set full-scall range to +/-500 degrees/second */
#define MPU9250_GYRO_CONFIG_GYRO_FS_SEL_500DPS          0x08
/** Set full-scall range to +/-1000 degrees/second */
#define MPU9250_GYRO_CONFIG_GYRO_FS_SEL_1000DPS         0x10
/** Set full-scall range to +/-2000 degrees/second */
#define MPU9250_GYRO_CONFIG_GYRO_FS_SEL_2000DPS         0x18

/** @} */

/** @name Gyroscope filter frequency bypass
 * @{
 *
 * @note    In some places in the documentation, a value called FCHOICE is
 * called out, which is a bit-inverted version of FCHOICE_B (the value which
 * actually appears in the GYRO_CONFIG register)
 */

/** Mask for FCHOICE_B bits */
#define MPU9250_GYRO_CONFIG_FCHOICE_B_MASK              0x03
/** Digital low-pass filter bandwidth set by CONFIG::DLPF_CFG */
#define MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG          0x00
/** Digital low-pass filter bandwidth of 8800 Hz (4000 Hz for temp sensor),
 * regardless of CONFIG::DLPF_CFG */
#define MPU9250_GYRO_CONFIG_FCHOICE_B_8800HZ            0x01
/** Digital low-pass filter bandwidth of 3600 Hz (4000 Hz for temp sensor),
 * regardless of CONFIG::DLPF_CFG */
#define MPU9250_GYRO_CONFIG_FCHOICE_B_3600HZ            0x02

/** @} */

/** ACCEL_CONFIG address */
#define MPU9250_ACCEL_CONFIG                            0x1C

/** Accelerometer self-test enable flags
 * @{
 */

/** Enable self-test on the X axis of the accelerometer */
#define MPU9250_ACCEL_CONFIG_AX_ST_EN                   0x80
/** Enable self-test on the Y axis of the accelerometer */
#define MPU9250_ACCEL_CONFIG_AY_ST_EN                   0x40
/** Enable self-test on the Z axis of the accelerometer */
#define MPU9250_ACCEL_CONFIG_AZ_ST_EN                   0x20

/** @} */

/** Full-scale range configuration for accelerometer
 * @{
 */

/** Mask for ACCEL_FS_SEL bits */
#define MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_MASK          0x18
/** Set accelerometer full-scale range to +/-2 G */
#define MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_2G            0x00
/** Set accelerometer full-scale range to +/-4 G */
#define MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_4G            0x08
/** Set accelerometer full-scale range to +/-8 G */
#define MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_8G            0x10
/** Set accelerometer full-scale range to +/-16 G */
#define MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_16G           0x18

/** @} */

/** ACCEL_CONFIG_2 address */
#define MPU9250_ACCEL_CONFIG_2                          0x1D

/** @name Frequency override selection for accelerometer digital low-pass filter
 * @{
 *
 * @note    In some places in the documentation, a value called ACCEL_FCHOICE
 * is called out, which is a bit-inverted version of ACCEL_FCHOICE_B
 */

/** Mask for ACCEL_FCHOICE_B */
#define MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK     0x08
/** Select filter bandwidth based on ACCEL_CONFIG_2::A_DLPFCFG */
#define MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG 0x00
/** Force digital low-pass filter to 1130 Hz bandwidth */
#define MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_1130Hz   0x08

/** @} */

/** @name Frequency selection for accelerometer digital low-pass filter
 * @{
 *
 * @note    Only valid if ACCEL_FCHOICE_B is 1'b1
 */

/** Mask for A_DLPFCFG */
#define MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_MASK           0x07
/** Set accelerometer digital low-pass filter bandwidth to 460 Hz */
#define MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_460HZ          0x00
/** Set accelerometer digital low-pass filter bandwidth to 184 Hz */
#define MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_184HZ          0x01
/** Set accelerometer digital low-pass filter bandwidth to 92 Hz */
#define MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_92HZ           0x02
/** Set accelerometer digital low-pass filter bandwidth to 41 Hz */
#define MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_41HZ           0x03
/** Set accelerometer digital low-pass filter bandwidth to 20 Hz */
#define MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_20HZ           0x04
/** Set accelerometer digital low-pass filter bandwidth to 10 Hz */
#define MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_10HZ           0x05
/** Set accelerometer digital low-pass filter bandwidth to 5 Hz */
#define MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_5HZ            0x06

/** @} */

/** @} */

/** @defgroup MPU9250_LP_ACCEL_ODR LP_ACCEL_ODR register
 * @{
 *
 * @brief   Controls output data rate in low-power mode
 */

/** LP_ACCEL_ODR address */
#define MPU9250_LP_ACCEL_ODR                            0x1E

/** @name Select the output data rate in low-power mode
 * @{
 */

/** Maximum value allowed to be programed to LP_ACCEL_ODR */
#define MPU9250_LP_ACCEL_ODR_MAX                        0x0B
/** Mask for LPOSC_CLKSEL bitfield */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_MASK          0x0F
/** Sets the output data rate in low-power mode to 0.24 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_0p24HZ        0x00
/** Sets the output data rate in low-power mode to 0.49 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_0p49HZ        0x01
/** Sets the output data rate in low-power mode to 0.98 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_0p98HZ        0x02
/** Sets the output data rate in low-power mode to 1.95 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_1p95HZ        0x03
/** Sets the output data rate in low-power mode to 3.91 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_3p91HZ        0x04
/** Sets the output data rate in low-power mode to 7.81 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_7p81HZ        0x05
/** Sets the output data rate in low-power mode to 15.63 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_15p63HZ       0x06
/** Sets the output data rate in low-power mode to 31.25 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_31p25HZ       0x07
/** Sets the output data rate in low-power mode to 62.50 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_62p50HZ       0x08
/** Sets the output data rate in low-power mode to 125 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_125HZ         0x09
/** Sets the output data rate in low-power mode to 250 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_250HZ         0x0A
/** Sets the output data rate in low-power mode to 500 Hz */
#define MPU9250_LP_ACCEL_ODR_LPOSC_CLKSEL_500HZ         0x0B

/** @} */

/** @} */

/** @defgroup MPU9250_WOM_THR WOM_THR  register
 * @{
 *
 * @brief Controls the threshold for the wake-on-motion functionality
 *
 * LSB has value of 4 mG, regardless of accelerometer full-scale range
 */

/** WOM_THR address */
#define MPU9250_WOM_THR                                 0x1F

/** @} */

/** @defgroup MPU9250_FIFO_EN FIFO_EN register
 * @{
 *
 * @brief   Controls what data is written to the chip's hardware FIFO
 */

/** FIFO_EN address */
#define MPU9250_FIFO_EN                                 0x23

/** FIFO data configuration
 * @{
 */

/** Include TEMP_OUT_[HL] in FIFO data */
#define MPU9250_FIFO_EN_TEMP_OUT                        0x80
/** Include GYRO_XOUT_[HL] in FIFO data */
#define MPU9250_FIFO_EN_GYRO_XOUT                       0x40
/** Include GYRO_YOUT_[HL] in FIFO data */
#define MPU9250_FIFO_EN_GYRO_YOUT                       0x20
/** Include GYRO_ZOUT_[HL] in FIFO data */
#define MPU9250_FIFO_EN_GYRO_ZOUT                       0x10
/** Include ACCEL_[XYZ]OUT_[HL] in FIFO data */
#define MPU9250_FIFO_EN_ACCEL                           0x08
/** Write external sensor data from slave 2 to the FIFO */
#define MPU9250_FIFO_EN_SLV_2                           0x04
/** Write external sensor data from slave 1 to the FIFO */
#define MPU9250_FIFO_EN_SLV_1                           0x02
/** Write external sensor data from slave 0 to the FIFO */
#define MPU9250_FIFO_EN_SLV_0                           0x01

/** @} */

/** @} */

/* TODO: Add I2C slave control registers */

/** @defgroup MPU9250_INTERRUPT Interrupt registers
 * @{
 *
 * @brief   Configure the interrupt pin functionality
 */

/** INT_PIN_CFG address */
#define MPU9250_INT_PIN_CFG                             0x37

/** @name Bits in INT_PIN_CFG
 * @{
 */

/** Rserved bits in INT_PIN_CFG */
#define MPU9250_INT_PIN_CFG_RESERVED_MASK               0x01

/** INT pin assertion polarity
 *
 * When set, INT pin is active low -- otherwise, it's active high.
 */
#define MPU9250_INT_PIN_CFG_ACTL                        0x80
/** INT pin drive mode
 *
 * When set, the INT pin is open-drain. Otherwise, it's push-pull.
 */
#define MPU9250_INT_PIN_CFG_OPEN                        0x40
/** INT pin latch status
 *
 * When set, INT pin is asserted for the entire duration of an active
 * interrupt. Otherwise, it's a 50 us pulse.
 */
#define MPU9250_INT_PIN_CFG_LATCH_INT_EN                0x20
/** How to clear an interrupt
 *
 * When set, any read clears INT status. Otherwise, a read to INT_STATUS is
 * required to clear it.
 */
#define MPU9250_INT_PIN_CFG_INT_ANYRD_2CLEAR            0x10
/** FSYNC pin polarity
 *
 * When set, FSYNC is active low -- otherwise, it's active high.
 */
#define MPU9250_INT_PIN_CFG_ACTL_FSYNC                  0x08
/** Configure the FSYNC pin to cause an interrupt */
#define MPU9250_INT_PIN_CFG_FSYNC_INT_MODE_EN           0x04
/** Enable "bypass mode" on the i2c master pins  */
#define MPU9250_INT_PIN_CFG_BYPASS_EN                   0x02

/** @} */

/** INT_ENABLE address */
#define MPU9250_INT_ENABLE                              0x38

/** @name Control which interrupts propogate to the interrupt pin
 * @{
 */

#define MPU9250_INT_ENABLE_RESERVED_MASK                0xA6

/** Enable the Wake-on-Motion interrupt */
#define MPU9250_INT_ENABLE_WOM_EN                       0x40
/** Enable FIFO overflow interrupt */
#define MPU9250_INT_ENABLE_FIFO_OVERFLOW_EN             0x10
/** Enable FSYNC interrupt */
#define MPU9250_INT_ENABLE_FSYNC_INT_EN                 0x08
/** Enable interrupt when raw data is ready from slave sensor */
#define MPU9250_INT_ENABLE_RAW_RDY_EN                   0x01

/** @} */

/** INT_STATUS address */
#define MPU9250_INT_STATUS                              0x3A

/** @name Current interrupt status
 * @{
 */

/** Status of the Wake-on-Motion interrupt */
#define MPU9250_INT_STATUS_WOM_INT                      0x40
/** Status of the FIFO overflow interrupt */
#define MPU9250_INT_STATUS_FIFO_OVERFLOW_INT            0x10
/** Status of the FSYNC interrupt */
#define MPU9250_INT_STATUS_FSYNC_INT                    0x08
/** Status of the raw-data ready interrupt */
#define MPU9250_INT_STATUS_RAW_RDY_INT                  0x01

/** @} */

/** @} */

/** @defgroup MPU9250_DATA_OUT MPU9250 Data registers
 * @{
 *
 * @brief   Direct reads to these registers retrieve the latest measured values
 */

/** ACCEL_XOUT_H address */
#define MPU9250_ACCEL_XOUT_H                            0x3B

/** ACCEL_XOUT_L address */
#define MPU9250_ACCEL_XOUT_L                            0x3C

/** ACCEL_YOUT_H address */
#define MPU9250_ACCEL_YOUT_H                            0x3D

/** ACCEL_YOUT_L address */
#define MPU9250_ACCEL_YOUT_L                            0x3E

/** ACCEL_ZOUT_H address */
#define MPU9250_ACCEL_ZOUT_H                            0x3F

/** ACCEL_ZOUT_L address */
#define MPU9250_ACCEL_ZOUT_L                            0x40

/** TEMP_OUT_H address */
#define MPU9250_TEMP_OUT_H                              0x41

/** TEMP_OUT_L address */
#define MPU9250_TEMP_OUT_L                              0x42

/** GYRO_XOUT_H address */
#define MPU9250_GYRO_XOUT_H                             0x43

/** GYRO_XOUT_L address */
#define MPU9250_GYRO_XOUT_L                             0x44

/** GYRO_YOUT_H address */
#define MPU9250_GYRO_YOUT_H                             0x45

/** GYRO_YOUT_L address */
#define MPU9250_GYRO_YOUT_L                             0x46

/** GYRO_ZOUT_H address */
#define MPU9250_GYRO_ZOUT_H                             0x47

/** GYRO_ZOUT_L address */
#define MPU9250_GYRO_ZOUT_L                             0x48

/** @} */

/** @defgroup MPU9250_SIGNAL_PATH_RESET MPU9250 SIGNAL_PATH_RESET register
 * @{
 *
 * @brief Reset the individual portions of the digital signal path
 */

/** SIGNAL_PATH_RESET address */
#define MPU9250_SIGNAL_PATH_RESET                       0x68

/** @name Reset certain portions of the signal path
 * @{
 */

/** Resets gyroscope's digital signal path */
#define MPU9250_SIGNAL_PATH_RESET_GYRO_RST              0x04
/** Resets accelerometer's digital signal path */
#define MPU9250_SIGNAL_PATH_RESET_ACCEL_RST             0x02
/** Resets temperature sensor's digital signal path */
#define MPU9250_SIGNAL_PATH_RESET_TEMP_RST              0x01

/** @} */

/** @} */

/** @defgroup MPU9250_MOT_DETECT_CTRL MPU9250 MOT_DETECT_CTRL register
 * @{
 *
 * @brief   Control wake-on-motion configuration
 *
 * @note    This register is misnamed in the register map as
 *          "ACCEL_INTEL_CTRL."
 */
/** MOT_DETECT_CTRL address */
#define MPU9250_MOT_DETECT_CTRL                         0x69

/** @name Accelerometer interrupt control settings
 * @{
 */

#define MPU9250_MOT_DETECT_CTRL_RESERVED_MASK           0x3F
/** Enable wake-on-motion detection */
#define MPU9250_MOT_DETECT_CTRL_ACCEL_INTEL_EN          0x80
/** When set, compares the current sample with the previous one for WOM
 * thresholding */
#define MPU9250_MOT_DETECT_CTRL_ACCEL_INTEL_MODE        0x40

/** @} */

/** @} */

/** @defgroup MPU9250_USER_CTRL MPU9250 USER_CTRL register
 * @{
 *
 * @brief   General enable and reset control
 */

/** USER_CTRL address */
#define MPU9250_USER_CTRL                               0x6A

/** @name USER_CTRL bits
 * @{
 */

/** Reserved bits in USER_CTRL */
#define MPU9250_USER_CTRL_RESERVED_MASK                 0x88
/** Enable the sample FIFO */
#define MPU9250_USER_CTRL_FIFO_EN                       0x40
/** Enable the internal I2C master module
 *
 * When enabled, it takes control of the ES_DA and ES_SCL pins. Otherwise,
 * these are logically driven by the SDA/SCL input pins of the device
 */
#define MPU9250_USER_CTRL_I2C_MST_EN                    0x20
/** Disable the I2C slave interface
 *
 * This puts the chip in SPI-only mode until the next reset
 */
#define MPU9250_USER_CTRL_I2C_IF_DIS                    0x10
/** Reset the FIFO */
#define MPU9250_USER_CTRL_FIFO_RST                      0x04
/** Reset the I2C master interface */
#define MPU9250_USER_CTRL_I2C_MST_RST                   0x02
/** Reset the entire digital signal path
 *
 * Also clears sensor registers
 */
#define MPU9250_USER_CTRL_SIG_COND_RST                  0x01

/** @} */

/** @} */

/** @defgroup MPU9250_PWR_MGMT MPU9250 PWR_MGMT registers
 * @{
 */

/** PWR_MGMT_1 address */
#define MPU9250_PWR_MGMT_1                              0x6B

/** @name PWR_MGMT_1 miscellaneous bits
 * @{
 */

/** Reset, as if using the reset pin */
#define MPU9250_PWR_MGMT_1_H_RESET                      0x80
/** Put the chip to sleep */
#define MPU9250_PWR_MGMT_1_SLEEP                        0x40
/** Enables cycling between sleep and wake states
 *
 * At each wakeup, the system will take a single sample. The sample rate is
 * defined by the LP_ACCEL_ODR register.
 */
#define MPU9250_PWR_MGMT_1_CYCLE                        0x20
/** Put gyro in a disabled, but quickly enableable, mode */
#define MPU9250_PWR_MGMT_1_GYRO_STANDBY                 0x10
/** Disable the temperature sensor
 *
 * @note The documentation is horribly unclear about this particular bit. As
 *       near as I can tell, this is an alternate name for the TEMP_DIS bit --
 *       but this is yet to be verified!
 */
#define MPU9250_PWR_MGMT_1_PD_PTAT                      0x08

/** @} */

/** @name PWR_MGMT_1 CLKSEL
 * @{
 */

/** Mask for CLKSEL bitfield */
#define MPU9250_PWR_MGMT_1_CLKSEL_MASK                  0x07
/** Use the internal (20MHz) oscillator */
#define MPU9250_PWR_MGMT_1_CLKSEL_INTOSC                0x00
/** Automatically select the clock source
 *
 * Clock source will be the PLL if it's ready, otherwise the internal
 * oscillator
 */
#define MPU9250_PWR_MGMT_1_CLKSEL_AUTO                  0x01
/** Entirely stop the clock, keeping timing generator in reset */
#define MPU9250_PWR_MGMT_1_CLKSEL_DISABLE               0x07

/** @} */

/** PWR_MGMT_2 address */
#define MPU9250_PWR_MGMT_2                              0x6C

/** @name PWR_MGMT_2 bits
 * @{
 */

/** Reserved bits of PWR_MGMT_2 */
#define MPU9250_PWR_MGMT_2_RESERVED_MASK                0xC0
/** Disable X axis of accelerometer */
#define MPU9250_PWR_MGMT_2_DISABLE_XA                   0x20
/** Disable Y axis of accelerometer */
#define MPU9250_PWR_MGMT_2_DISABLE_YA                   0x10
/** Disable Z axis of accelerometer */
#define MPU9250_PWR_MGMT_2_DISABLE_ZA                   0x08
/** Disable X axis of gyroscope */
#define MPU9250_PWR_MGMT_2_DISABLE_XG                   0x04
/** Disable Y axis of gyroscope */
#define MPU9250_PWR_MGMT_2_DISABLE_YG                   0x02
/** Disable Z axis of gyroscope */
#define MPU9250_PWR_MGMT_2_DISABLE_ZG                   0x01

/** @} */

/** @} */

/** @defgroup MPU9250_FIFO MPU9250 FIFO registers
 * @{
 *
 * @brief   Read from and write to the hardware FIFO
 */

/** FIFO_COUNTH address */
#define MPU9250_FIFO_COUNTH                             0x72

/** FIFO_COUNTL address */
#define MPU9250_FIFO_COUNTL                             0x73

/** FIFO_R_W address */
#define MPU9250_FIFO_R_W                                0x74

/** @} */

/** @defgroup MPU9250_WHO_AM_I MPU9250 WHO_AM_I register
 * @{
 *
 * @brief   Read a fixed value to verify MPU9250 presence
 */

/** WHO_AM_I address */
#define MPU9250_WHO_AM_I                                0x75

/** Value that should be in the WHO_AM_I register */
#define MPU9250_WHO_AM_I_VALUE                          0x71

/** @} */

/** @defgroup MPU9250_ACCEL_OFFSET MPU9250 ACCEL_OFFSET registers
 * @{
 *
 * @brief   Set a constant offset for accelerometer readings
 */

/** XA_OFFSET_H address */
#define MPU9250_XA_OFFSET_H                             0x77

/** XA_OFFSET_L address */
#define MPU9250_XA_OFFSET_L                             0x78

/** YA_OFFSET_H address */
#define MPU9250_YA_OFFSET_H                             0x79

/** YA_OFFSET_L address */
#define MPU9250_YA_OFFSET_L                             0x7A

/** ZA_OFFSET_H address */
#define MPU9250_ZA_OFFSET_H                             0x7B

/** ZA_OFFSET_L address */
#define MPU9250_ZA_OFFSET_L                             0x7C

/** @} */

/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** @} defgroup MPU9250_REGISTERS */
/** @} addtogroup MPU9250 */

#endif /* ifndef MPU9250_REGISTERS_H */
