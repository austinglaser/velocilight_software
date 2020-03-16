/**@file    mpu9250.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Mpu9250 Source
 *
 * @addtogroup MPU9250
 * @{
 *
 * @defgroup MPU9250_PRIVATE Mpu9250 Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "mpu9250.h"
#include "mpu9250_port.h"
#include "mpu9250_registers.h"

/* Supporting modules */
#include "ensure.h"
#include "error.h"
#include "util.h"

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */

/** Initialization for a single register */
typedef struct {
    /** Gets an init value for this register
     *
     * @param[in] config: Configuration to implement
     *
     * @return This registers initialization
     */
    uint8_t (*get_value)(mpu9250_config_t const * config);

    /** Address of register to initialize */
    uint8_t addr;
} mpu9250_reg_init_t;

/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */

#if ENSURE_MODE != ENSURE_MODE_OFF
/** Verify that @p config is valid
 *
 * Checks that all the enum options are in a valid range. Does not check
 * register initial values -- reserved bits in that case are silently cleared.
 *
 * We could change this behavior, which would make it more explicit at the top
 * level when settings were invalid.
 *
 * @param[in] config:       Configuration to check
 *
 * @return      Whether @p config is valid
 */
static bool _is_valid_config(mpu9250_config_t const * config);
#endif

/** Verifies that the IMU described by @p config exists and talks
 *
 * @param[in] imu:   IMU to reset
 *
 * @retval      ERROR_NONE: The IMU exists and talks
 * @retval      ERROR_COMM: No device is responding
 * @retval      ERROR_HW:   A device is responding, but it doesn't appear to be
 *                          an MPU9250
 */
static err_t _validate_communication(mpu9250_t const * imu);

/** Reset the IMU
 *
 * @param[in] imu:   IMU to reset
 *
 * @retval      ERROR_NONE: The IMU was reset
 * @retval      ERROR_COMM: The device couldn't be reset
 */
static err_t _do_reset(mpu9250_t const * imu);

/** Initialize all registers according to @ref _reg_init
 *
 * @param[in] imu:          IMU to write
 *
 * @retval      ERROR_NONE: The registers were initialized
 * @retval      ERROR_COMM: The device couldn't be initialized
 */
static err_t _initialize_registers(mpu9250_t const * imu);

/** Read an instantaneous acceleration vector from @p imu
 *
 * Reads each axis conditionally, based on whether it's enabled (@ref
 * MPU9250_PWR_MGMT_2, @ref mpu9250_config_t.pwr_mgmt_2). This means it's
 * possible for this function to effectively be a no-op if no acceleration axes
 * are enabled.
 *
 * @param[in] imu:      IMU to read from
 * @param[out] accel:   Acceleration vector
 *
 * @retval      ERROR_NONE:     The read was successful
 * @retval      ERROR_COMM:     The device couldn't be read
 */
static err_t _read_accel(mpu9250_t const * imu, mpu9250_axes_t * accel);

/** Read an instantaneous gyroscope vector from @p imu
 *
 * Reads each axis conditionally, based on whether it's enabled (@ref
 * MPU9250_PWR_MGMT_2, @ref mpu9250_config_t.pwr_mgmt_2). This means it's
 * possible for this function to effectively be a no-op if no gyroscope axes
 * are enabled.
 *
 * @param[in] imu:      IMU to read from
 * @param[out] gyro:    Gyroscope vector
 *
 * @retval      ERROR_NONE:     The read was successful
 * @retval      ERROR_COMM:     The device couldn't be read
 */
static err_t _read_gyro(mpu9250_t const * imu, mpu9250_axes_t * gyro);

/** Read an instantaneous temperature value from @p imu
 *
 * Reads the temperature conditionally, based on whether it's enabled (@ref
 * MPU9250_PWR_MGMT_1, @ref mpu9250_config_t.pwr_mgmt_1). This means it's
 * possible for this function to effectively be a no-op if the temperature
 * sensor is disabled
 *
 * @param[in] imu:      IMU to read from
 * @param[out] temp:    Temperature reading
 *
 * @retval      ERROR_NONE:     The read was successful
 * @retval      ERROR_COMM:     The device couldn't be read
 */
static err_t _read_temp(mpu9250_t const * imu, int32_t * temp);

/** Converts the axes in @p accel from raw counts to mG
 *
 * Takes into account the full-scale range setting for @p imu
 *
 * @param[in] imu:          IMU
 * @param[in,out] accel:    Acceleration vector
 */
static void _convert_accel(mpu9250_t const * imu, mpu9250_axes_t * accel);

/** Converts the axes in @p gyro from raw counts to mDPS
 *
 * Takes into account the full-scale range setting for @p imu
 *
 * @param[in] imu:          IMU
 * @param[in,out] gyro:     Rotation vector
 */
static void _convert_gyro(mpu9250_t const * imu, mpu9250_axes_t * gyro);

/** Read a two-register value from the IMU
 *
 * Takes the lower register address, which is the high-byte of the two-byte
 * value.
 *
 * Sign-extends the result into the 32-bit @p value.
 *
 * @param[in] imu:      IMU to read
 * @param[in] addr:     The lower of the two addresses to read
 * @param[out] value:   The value read, sign-extended
 *
 * @retval  ERROR_NONE:     The read was successful
 * @retval  ERROR_COMM:     The device could not be read. @p value was not
 *                          modified.
 */
static err_t _read_tworeg_value(mpu9250_t const * imu,
                                uint8_t addr,
                                int32_t * value);

/** Converts @p temp from raw counts to mC
 *
 * @param[in,out] temp:     Temperature reading
 */
static void _convert_temp(int32_t * temp);

/** Compute a value for the SMPLRT_DIV register
 *
 * Simply retrieves the user-supplied init value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _smplrt_div_value(mpu9250_config_t const * config);

/** Compute a value for the CONFIG register
 *
 * Accounts for both the user-supplied initialization value, and the desired
 * gyro sample rate and digital low-pass filter cutoff
 *
 * Clears reserved fields
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _config_value(mpu9250_config_t const * config);

/** Compute a value for the GYRO_CONFIG register
 *
 * Accounts for both the the desired gyro sample rate and full range
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _gyro_config_value(mpu9250_config_t const * config);

/** Compute a value for the ACCEL_CONFIG register
 *
 * Accounts for the desired full-scale range
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _accel_config_value(mpu9250_config_t const * config);

/** Compute a value for the ACCEL_CONFIG_2 register
 *
 * Generates the appropriate sample rate and digital low-pass value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _accel_config_2_value(mpu9250_config_t const * config);

/** Compute a value for the LP_ACCEL_ODR register
 *
 * Simply retrieves the user-supplied init value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _lp_accel_odr_value(mpu9250_config_t const * config);

/** Compute a value for the WOM_THR register
 *
 * Simply retrieves the user-supplied init value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _wom_thr_value(mpu9250_config_t const * config);

/** Compute a value for the FIFO_EN register
 *
 * Simply retrieves the user-supplied init value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _fifo_en_value(mpu9250_config_t const * config);

/** Compute avalue for the INT_PIN_CFG register
 *
 * Clears reserved fields from the user-supplied initialization value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _int_pin_cfg_value(mpu9250_config_t const * config);

/** Compute avalue for the INT_ENABLE register
 *
 * Clears reserved fields from the user-supplied initialization value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _int_enable_value(mpu9250_config_t const * config);

/** Compute avalue for the MOT_DETECT_CTRL register
 *
 * Clears reserved fields from the user-supplied initialization value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _mot_detect_ctrl_value(mpu9250_config_t const * config);

/** Compute avalue for the USER_CTRL register
 *
 * Clears reserved fields and reset bits from the user-supplied initialization
 * value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _user_ctrl_value(mpu9250_config_t const * config);

/** Compute avalue for the PWR_MGMT_1 register
 *
 * Clears reserved fields from the user-supplied initialization value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _pwr_mgmt_1_value(mpu9250_config_t const * config);

/** Compute avalue for the PWR_MGMT_2 register
 *
 * Clears reserved fields from the user-supplied initialization value
 *
 * @param[in]   config:     Configuration to implement
 */
static uint8_t _pwr_mgmt_2_value(mpu9250_config_t const * config);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

/** Initializations for all registers */
static const mpu9250_reg_init_t _reg_init[] = {
    { .get_value = _smplrt_div_value,      .addr = MPU9250_SMPLRT_DIV      },
    { .get_value = _config_value,          .addr = MPU9250_CONFIG          },
    { .get_value = _gyro_config_value,     .addr = MPU9250_GYRO_CONFIG     },
    { .get_value = _accel_config_value,    .addr = MPU9250_ACCEL_CONFIG    },
    { .get_value = _accel_config_2_value,  .addr = MPU9250_ACCEL_CONFIG_2  },
    { .get_value = _lp_accel_odr_value,    .addr = MPU9250_LP_ACCEL_ODR    },
    { .get_value = _wom_thr_value,         .addr = MPU9250_WOM_THR         },
    { .get_value = _fifo_en_value,         .addr = MPU9250_FIFO_EN         },
    { .get_value = _int_pin_cfg_value,     .addr = MPU9250_INT_PIN_CFG     },
    { .get_value = _int_enable_value,      .addr = MPU9250_INT_ENABLE      },
    { .get_value = _mot_detect_ctrl_value, .addr = MPU9250_MOT_DETECT_CTRL },
    { .get_value = _user_ctrl_value,       .addr = MPU9250_USER_CTRL       },
    { .get_value = _pwr_mgmt_1_value,      .addr = MPU9250_PWR_MGMT_1      },
    { .get_value = _pwr_mgmt_2_value,      .addr = MPU9250_PWR_MGMT_2      },
};

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

err_t mpu9250_init(mpu9250_t * imu, mpu9250_config_t const * config)
{
    ensure(imu != NULL);
    ensure(_is_valid_config(config));

    imu->config = config;

    mpu9250_port_init(&imu->port, &config->port_config);

    err_t err = ERROR_NONE;
    err = ERROR_OR(err, _validate_communication(imu));
    err = ERROR_OR(err, _do_reset(imu));
    err = ERROR_OR(err, _initialize_registers(imu));

    return err;
}

err_t mpu9250_read(mpu9250_t const * imu, mpu9250_sample_t * sample)
{
    ensure(imu != NULL);
    ensure(_is_valid_config(imu->config));
    ensure(sample != NULL);

    err_t err = ERROR_NONE;
    err = ERROR_OR(err, _read_accel(imu, &sample->accel));
    err = ERROR_OR(err, _read_gyro(imu,  &sample->gyro));
    err = ERROR_OR(err, _read_temp(imu,  &sample->temp));

    return err;
}

void mpu9250_convert(mpu9250_t * imu, mpu9250_sample_t * sample)
{
    ensure(imu != NULL);
    ensure(_is_valid_config(imu->config));
    ensure(sample != NULL);

    _convert_accel(imu, &sample->accel);
    _convert_gyro(imu, &sample->gyro);
    _convert_temp(&sample->temp);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

#if ENSURE_MODE != ENSURE_MODE_OFF
static bool _is_valid_config(mpu9250_config_t const * config)
{
    if (config == NULL) {
        return false;
    }

    if (config->accel_fs > MPU9250_ACCEL_FS_16) {
        return false;
    }

    if (config->accel_samplerate > MPU9250_ACCEL_SAMPLERATE_4k_1130Hz) {
        return false;
    }

    if (config->gyro_fs > MPU9250_GYRO_FS_2000) {
        return false;
    }

    if (config->gyro_samplerate > MPU9250_GYRO_SAMPLERATE_32k_8800Hz) {
        return false;
    }

    return true;
}
#endif

static err_t _validate_communication(mpu9250_t const * imu)
{
    uint8_t who_am_i;
    err_t err;
    err = mpu9250_port_read_reg(&imu->port, MPU9250_WHO_AM_I, &who_am_i);
    if (err != ERROR_NONE) {
        return err;
    }

    return (who_am_i == 0x71)
                ? ERROR_NONE
                : ERROR_HW;
}

static err_t _do_reset(mpu9250_t const * imu)
{
    err_t err =  mpu9250_port_write_reg(
        &imu->port,
        MPU9250_PWR_MGMT_1,
        MPU9250_PWR_MGMT_1_H_RESET
    );

    if (err != ERROR_NONE) {
        return err;
    }

    int32_t tries = 100;
    do {
        err = _validate_communication(imu);
        tries -= 1;
    } while (err != ERROR_NONE && tries > 0);

    return err;
}

static err_t _initialize_registers(mpu9250_t const * imu)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(_reg_init); i++) {
        uint8_t value = _reg_init[i].get_value(imu->config);
        uint8_t addr  = _reg_init[i].addr;
        err_t err = mpu9250_port_write_reg(&imu->port, addr, value);
        if (err != ERROR_NONE) {
            return err;
        }
    }

    return ERROR_NONE;
}

static err_t _read_accel(mpu9250_t const * imu, mpu9250_axes_t * accel)
{
    err_t err = ERROR_NONE;

    if (!(imu->config->pwr_mgmt_2 & MPU9250_PWR_MGMT_2_DISABLE_XA)) {
        err = _read_tworeg_value(imu, MPU9250_ACCEL_XOUT_H, &accel->x);
        if (err != ERROR_NONE) {
            return err;
        }
    }

    if (!(imu->config->pwr_mgmt_2 & MPU9250_PWR_MGMT_2_DISABLE_YA)) {
        err = _read_tworeg_value(imu, MPU9250_ACCEL_YOUT_H, &accel->y);
        if (err != ERROR_NONE) {
            return err;
        }
    }

    if (!(imu->config->pwr_mgmt_2 & MPU9250_PWR_MGMT_2_DISABLE_ZA)) {
        err = _read_tworeg_value(imu, MPU9250_ACCEL_ZOUT_H, &accel->z);
    }

    return err;
}

static err_t _read_gyro(mpu9250_t const * imu, mpu9250_axes_t * gyro)
{
    err_t err = ERROR_NONE;

    if (!(imu->config->pwr_mgmt_2 & MPU9250_PWR_MGMT_2_DISABLE_XG)) {
        err = _read_tworeg_value(imu, MPU9250_GYRO_XOUT_H, &gyro->x);
        if (err != ERROR_NONE) {
            return err;
        }
    }

    if (!(imu->config->pwr_mgmt_2 & MPU9250_PWR_MGMT_2_DISABLE_YG)) {
        err = _read_tworeg_value(imu, MPU9250_GYRO_YOUT_H, &gyro->y);
        if (err != ERROR_NONE) {
            return err;
        }
    }

    if (!(imu->config->pwr_mgmt_2 & MPU9250_PWR_MGMT_2_DISABLE_ZG)) {
        err = _read_tworeg_value(imu, MPU9250_GYRO_ZOUT_H, &gyro->z);
    }

    return err;
}

static err_t _read_temp(mpu9250_t const * imu, int32_t * temp)
{
    err_t err = ERROR_NONE;
    if (!(imu->config->pwr_mgmt_1 & MPU9250_PWR_MGMT_1_PD_PTAT)) {
        err = _read_tworeg_value(imu, MPU9250_TEMP_OUT_H, temp);
    }

    return err;
}

static void _convert_accel(mpu9250_t const * imu, mpu9250_axes_t * accel)
{
    static const int32_t accel_lsb_per_g[] = {
        [MPU9250_ACCEL_FS_2]  = 16384,
        [MPU9250_ACCEL_FS_4]  =  8192,
        [MPU9250_ACCEL_FS_8]  =  4096,
        [MPU9250_ACCEL_FS_16] =  2048,
    };

    int32_t accel_factor = accel_lsb_per_g[imu->config->accel_fs];

    accel->x = accel->x * 1000 / accel_factor;
    accel->y = accel->y * 1000 / accel_factor;
    accel->z = accel->z * 1000 / accel_factor;
}

static void _convert_gyro(mpu9250_t const * imu, mpu9250_axes_t * gyro)
{
    static const int32_t gyro_lsb_per_tendps[] = {
        [MPU9250_GYRO_FS_250]  = 1311,
        [MPU9250_GYRO_FS_500]  =  655,
        [MPU9250_GYRO_FS_1000] =  328,
        [MPU9250_GYRO_FS_2000] =  164,
    };

    int32_t gyro_factor = gyro_lsb_per_tendps[imu->config->gyro_fs];

    gyro->x = gyro->x * 10 * 1000 / gyro_factor;
    gyro->y = gyro->y * 10 * 1000 / gyro_factor;
    gyro->z = gyro->z * 10 * 1000 / gyro_factor;
}

static void _convert_temp(int32_t * temp)
{
    static const int32_t temp_sensitivity_100lsb_per_c = 33387;
    static const int32_t temp_offset_mC = 21000;

    *temp *= 100 * 1000;
    *temp /= temp_sensitivity_100lsb_per_c;
    *temp += temp_offset_mC;
}

static err_t _read_tworeg_value(mpu9250_t const * imu,
                                uint8_t addr,
                                int32_t * value)
{
    uint8_t high;
    uint8_t low;

    err_t err = ERROR_NONE;

    err = ERROR_OR(err, mpu9250_port_read_reg(&imu->port, addr, &high));
    err = ERROR_OR(err, mpu9250_port_read_reg(&imu->port, addr + 1, &low));
    if (err != ERROR_NONE) {
        return err;
    }

    /*
     * The assignment to an int16_t first gives us sign extension in the final
     * assignment
     */
    int16_t svalue = (high << 8) | low;
    *value = svalue;

    return ERROR_NONE;
}

static uint8_t _smplrt_div_value(mpu9250_config_t const * config)
{
    return config->smplrt_div;
}

static uint8_t _config_value(mpu9250_config_t const * config)
{
    uint8_t config_reg = config->config;
    config_reg &= ~MPU9250_CONFIG_RESERVED_MASK;

    config_reg &= ~MPU9250_CONFIG_DLPF_CFG_MASK;
    switch (config->gyro_samplerate) {
    case MPU9250_GYRO_SAMPLERATE_1k_5Hz:
        config_reg |= MPU9250_CONFIG_DLPF_CFG_5HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_1k_10Hz:
        config_reg |= MPU9250_CONFIG_DLPF_CFG_10HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_1k_20Hz:
        config_reg |= MPU9250_CONFIG_DLPF_CFG_20HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_1k_41Hz:
        config_reg |= MPU9250_CONFIG_DLPF_CFG_41HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_1k_92Hz:
        config_reg |= MPU9250_CONFIG_DLPF_CFG_92HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_1k_184Hz:
        config_reg |= MPU9250_CONFIG_DLPF_CFG_184HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_8k_250Hz:
        config_reg |= MPU9250_CONFIG_DLPF_CFG_250HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_8k_3600Hz:
        config_reg |= MPU9250_CONFIG_DLPF_CFG_3600HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_32k_3600Hz:
    case MPU9250_GYRO_SAMPLERATE_32k_8800Hz:
        /* These sample rates don't care about the DLPF_CFG field; instead,
         * they're selected by FCHOICE_B in GYRO_CONFIG */
        break;
    }

    return config_reg;
}

static uint8_t _gyro_config_value(mpu9250_config_t const * config)
{
    uint8_t gyro_config_reg = 0;
    switch (config->gyro_fs) {
    case MPU9250_GYRO_FS_250:
        gyro_config_reg |= MPU9250_GYRO_CONFIG_GYRO_FS_SEL_250DPS;
        break;

    case MPU9250_GYRO_FS_500:
        gyro_config_reg |= MPU9250_GYRO_CONFIG_GYRO_FS_SEL_500DPS;
        break;

    case MPU9250_GYRO_FS_1000:
        gyro_config_reg |= MPU9250_GYRO_CONFIG_GYRO_FS_SEL_1000DPS;
        break;

    case MPU9250_GYRO_FS_2000:
        gyro_config_reg |= MPU9250_GYRO_CONFIG_GYRO_FS_SEL_2000DPS;
        break;
    }

    switch (config->gyro_samplerate) {
    case MPU9250_GYRO_SAMPLERATE_32k_3600Hz:
        gyro_config_reg |= MPU9250_GYRO_CONFIG_FCHOICE_B_3600HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_32k_8800Hz:
        gyro_config_reg |= MPU9250_GYRO_CONFIG_FCHOICE_B_8800HZ;
        break;

    case MPU9250_GYRO_SAMPLERATE_1k_5Hz:
    case MPU9250_GYRO_SAMPLERATE_1k_10Hz:
    case MPU9250_GYRO_SAMPLERATE_1k_20Hz:
    case MPU9250_GYRO_SAMPLERATE_1k_41Hz:
    case MPU9250_GYRO_SAMPLERATE_1k_92Hz:
    case MPU9250_GYRO_SAMPLERATE_1k_184Hz:
    case MPU9250_GYRO_SAMPLERATE_8k_250Hz:
    case MPU9250_GYRO_SAMPLERATE_8k_3600Hz:
        /* Selection delegated to CONFIG register */
        gyro_config_reg |= MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG;
        break;
    }

    return gyro_config_reg;
}

static uint8_t _accel_config_value(mpu9250_config_t const * config)
{
    uint8_t accel_config_reg = 0;
    switch (config->accel_fs) {
    case MPU9250_ACCEL_FS_2:
        accel_config_reg |= MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_2G;
        break;

    case MPU9250_ACCEL_FS_4:
        accel_config_reg |= MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_4G;
        break;

    case MPU9250_ACCEL_FS_8:
        accel_config_reg |= MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_8G;
        break;

    case MPU9250_ACCEL_FS_16:
        accel_config_reg |= MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_16G;
        break;
    }

    return accel_config_reg;
}

static uint8_t _accel_config_2_value(mpu9250_config_t const * config)
{
    uint8_t accel_config_2_reg = 0;
    switch (config->accel_samplerate) {
    case MPU9250_ACCEL_SAMPLERATE_1k_5Hz:
        accel_config_2_reg = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                             | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_5HZ;
        break;

    case MPU9250_ACCEL_SAMPLERATE_1k_10Hz:
        accel_config_2_reg = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                             | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_10HZ;
        break;

    case MPU9250_ACCEL_SAMPLERATE_1k_20Hz:
        accel_config_2_reg = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                             | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_20HZ;
        break;

    case MPU9250_ACCEL_SAMPLERATE_1k_41Hz:
        accel_config_2_reg = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                             | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_41HZ;
        break;

    case MPU9250_ACCEL_SAMPLERATE_1k_92Hz:
        accel_config_2_reg = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                             | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_92HZ;
        break;

    case MPU9250_ACCEL_SAMPLERATE_1k_184Hz:
        accel_config_2_reg = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                             | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_184HZ;
        break;

    case MPU9250_ACCEL_SAMPLERATE_1k_460Hz:
        accel_config_2_reg = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                             | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_460HZ;
        break;

    case MPU9250_ACCEL_SAMPLERATE_4k_1130Hz:
        accel_config_2_reg = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_1130Hz;
        break;
    }

    return accel_config_2_reg;
}

static uint8_t _lp_accel_odr_value(mpu9250_config_t const * config)
{
    if (config->lp_accel_odr > MPU9250_LP_ACCEL_ODR_MAX) {
        return MPU9250_LP_ACCEL_ODR_MAX;
    }

    return config->lp_accel_odr;
}

static uint8_t _wom_thr_value(mpu9250_config_t const * config)
{
    return config->wom_thr;
}

static uint8_t _fifo_en_value(mpu9250_config_t const * config)
{
    return config->fifo_en;
}

static uint8_t _int_pin_cfg_value(mpu9250_config_t const * config)
{
    return config->int_pin_cfg & ~MPU9250_INT_PIN_CFG_RESERVED_MASK;
}

static uint8_t _int_enable_value(mpu9250_config_t const * config)
{
    return config->int_enable & ~MPU9250_INT_ENABLE_RESERVED_MASK;
}

static uint8_t _mot_detect_ctrl_value(mpu9250_config_t const * config)
{
    return config->mot_detect_ctrl & ~MPU9250_MOT_DETECT_CTRL_RESERVED_MASK;
}

static uint8_t _user_ctrl_value(mpu9250_config_t const * config)
{
    return config->user_ctrl & ~(MPU9250_USER_CTRL_RESERVED_MASK
                                 | MPU9250_USER_CTRL_I2C_IF_DIS
                                 | MPU9250_USER_CTRL_FIFO_RST
                                 | MPU9250_USER_CTRL_I2C_MST_RST
                                 | MPU9250_USER_CTRL_SIG_COND_RST);
}

static uint8_t _pwr_mgmt_1_value(mpu9250_config_t const * config)
{
    return config->pwr_mgmt_1 & MPU9250_PWR_MGMT_1_CLKSEL_MASK;
}

static uint8_t _pwr_mgmt_2_value(mpu9250_config_t const * config)
{
    return config->pwr_mgmt_2 & ~MPU9250_PWR_MGMT_2_RESERVED_MASK;
}

/** @} defgroup MPU9250_PRIVATE */
/** @} addtogroup MPU9250 */
