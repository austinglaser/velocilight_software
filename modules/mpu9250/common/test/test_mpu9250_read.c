/**@file    test_mpu9250.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Mpu9250 Test Source
 *
 * @addtogroup MPU9250
 * @{
 *
 * @defgroup MPU9250_TEST Mpu9250 Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* Test framework */
#include "unity.h"

/* Module under test */
#include "mpu9250.h"

/* Supporting modules */
#include "mpu9250_registers.h"

/* Mocks, fakes, test support */
#include "ensure_support.h"
#include "fake_mpu9250_port.h"
#include "mock_mpu9250_port.h"

/* Source dependencies (present only to make Ceedling include the right
 * objects)
 */
#include "ensure_c_exception.h"
#include "unity_util.h"

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */

static void _mpu9250_read_null_handle(void);
static void _mpu9250_read_static_uninit_handle(void);
static void _mpu9250_read_null_sample(void);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

static mpu9250_t _imu;

static mpu9250_config_t _config;

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void setUp(void)
{
    fake_mpu9250_port_setup(&_imu.port);
}

void tearDown(void)
{
    fake_mpu9250_port_teardown(&_imu.port);
}

/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_mpu9250_read_reads_all_data_when_all_enabled(void)
{
    /* No axes disabled -> all axes enabled */
    _config.pwr_mgmt_1 = 0x00;
    _config.pwr_mgmt_2 = 0x00;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_XOUT_H, 0x10);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_XOUT_L, 0x11);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_YOUT_H, 0x12);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_YOUT_L, 0x13);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_ZOUT_H, 0x14);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_ZOUT_L, 0x15);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_XOUT_H,  0x20);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_XOUT_L,  0x21);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_YOUT_H,  0x22);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_YOUT_L,  0x23);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_ZOUT_H,  0x24);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_ZOUT_L,  0x25);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_TEMP_OUT_H,   0x30);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_TEMP_OUT_L,   0x31);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_INT32(0x1011, sample.accel.x);
    TEST_ASSERT_EQUAL_INT32(0x1213, sample.accel.y);
    TEST_ASSERT_EQUAL_INT32(0x1415, sample.accel.z);
    TEST_ASSERT_EQUAL_INT32(0x2021, sample.gyro.x);
    TEST_ASSERT_EQUAL_INT32(0x2223, sample.gyro.y);
    TEST_ASSERT_EQUAL_INT32(0x2425, sample.gyro.z);
    TEST_ASSERT_EQUAL_INT32(0x3031, sample.temp);
}

void test_mpu9250_read_sign_extends(void)
{
    /* No axes disabled -> all axes enabled */
    _config.pwr_mgmt_1 = 0x00;
    _config.pwr_mgmt_2 = 0x00;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_XOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_XOUT_L, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_YOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_YOUT_L, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_ZOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_ZOUT_L, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_XOUT_H,  0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_XOUT_L,  0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_YOUT_H,  0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_YOUT_L,  0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_ZOUT_H,  0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_ZOUT_L,  0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_TEMP_OUT_H,   0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_TEMP_OUT_L,   0xFF);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_INT32(0xFFFFFFFF, sample.accel.x);
    TEST_ASSERT_EQUAL_INT32(0xFFFFFFFF, sample.accel.y);
    TEST_ASSERT_EQUAL_INT32(0xFFFFFFFF, sample.accel.z);
    TEST_ASSERT_EQUAL_INT32(0xFFFFFFFF, sample.gyro.x);
    TEST_ASSERT_EQUAL_INT32(0xFFFFFFFF, sample.gyro.y);
    TEST_ASSERT_EQUAL_INT32(0xFFFFFFFF, sample.gyro.z);
    TEST_ASSERT_EQUAL_INT32(0xFFFFFFFF, sample.temp);
}

void test_mpu9250_read_doesnt_read_temp_sensor_when_disabled(void)
{
    _config.pwr_mgmt_1 = MPU9250_PWR_MGMT_1_PD_PTAT;
    _config.pwr_mgmt_2 = 0x00;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_TEMP_OUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_TEMP_OUT_L, 0xFF);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX16(0x0000, sample.temp);
}

void test_mpu9250_read_doesnt_read_accelerometer_x_axis_when_disabled(void)
{
    _config.pwr_mgmt_1 = 0x00;
    _config.pwr_mgmt_2 = MPU9250_PWR_MGMT_2_DISABLE_XA;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_XOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_XOUT_L, 0xFF);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX16(0x0000, sample.accel.x);
}

void test_mpu9250_read_doesnt_read_accelerometer_y_axis_when_disabled(void)
{
    _config.pwr_mgmt_1 = 0x00;
    _config.pwr_mgmt_2 = MPU9250_PWR_MGMT_2_DISABLE_YA;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_YOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_YOUT_L, 0xFF);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX16(0x0000, sample.accel.y);
}

void test_mpu9250_read_doesnt_read_accelerometer_z_axis_when_disabled(void)
{
    _config.pwr_mgmt_1 = 0x00;
    _config.pwr_mgmt_2 = MPU9250_PWR_MGMT_2_DISABLE_ZA;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_ZOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_ACCEL_ZOUT_L, 0xFF);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX16(0x0000, sample.accel.z);
}

void test_mpu9250_read_doesnt_read_gyroscope_x_axis_when_disabled(void)
{
    _config.pwr_mgmt_1 = 0x00;
    _config.pwr_mgmt_2 = MPU9250_PWR_MGMT_2_DISABLE_XG;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_XOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_XOUT_L, 0xFF);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX16(0x0000, sample.gyro.x);
}

void test_mpu9250_read_doesnt_read_gyroscope_y_axis_when_disabled(void)
{
    _config.pwr_mgmt_1 = 0x00;
    _config.pwr_mgmt_2 = MPU9250_PWR_MGMT_2_DISABLE_YG;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_YOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_YOUT_L, 0xFF);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX16(0x0000, sample.gyro.y);
}

void test_mpu9250_read_doesnt_read_gyroscope_z_axis_when_disabled(void)
{
    _config.pwr_mgmt_1 = 0x00;
    _config.pwr_mgmt_2 = MPU9250_PWR_MGMT_2_DISABLE_ZG;

    mpu9250_init(&_imu, &_config);

    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_ZOUT_H, 0xFF);
    fake_mpu9250_port_set_reg(&_imu.port, MPU9250_GYRO_ZOUT_L, 0xFF);

    mpu9250_sample_t sample = { 0 };
    err_t err = mpu9250_read(&_imu, &sample);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX16(0x0000, sample.gyro.z);
}

void test_mpu9250_read_detects_invalid_handle(void)
{
    mpu9250_init(&_imu, &_config);

    TEST_ASSERT_FAILS_ENSURE(_mpu9250_read_null_handle);
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_read_static_uninit_handle);
}

void test_mpu9250_read_detects_invalid_sample(void)
{
    mpu9250_init(&_imu, &_config);

    TEST_ASSERT_FAILS_ENSURE(_mpu9250_read_null_sample);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _mpu9250_read_null_handle(void)
{
    mpu9250_sample_t sample;

    mpu9250_read(NULL, &sample);
}

static void _mpu9250_read_static_uninit_handle(void)
{
    static const mpu9250_t imu;
    mpu9250_sample_t sample;

    mpu9250_read(&imu, &sample);
}

static void _mpu9250_read_null_sample(void)
{
    mpu9250_read(&_imu, NULL);
}

/** @} defgroup MPU9250_TEST */
/** @} addtogroup MPU9250 */
