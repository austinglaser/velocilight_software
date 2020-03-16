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
#include "util.h"

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

static void _mpu9250_convert_null_handle(void);
static void _mpu9250_convert_static_uninit_handle(void);
static void _mpu9250_convert_null_sample(void);

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

void test_mpu9250_convert_zero(void)
{
    mpu9250_init(&_imu, &_config);

    mpu9250_sample_t sample = { 0 };
    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_EQUAL_INT32(0,     sample.accel.x);
    TEST_ASSERT_EQUAL_INT32(0,     sample.accel.y);
    TEST_ASSERT_EQUAL_INT32(0,     sample.accel.z);
    TEST_ASSERT_EQUAL_INT32(0,     sample.gyro.x);
    TEST_ASSERT_EQUAL_INT32(0,     sample.gyro.y);
    TEST_ASSERT_EQUAL_INT32(0,     sample.gyro.z);
    TEST_ASSERT_EQUAL_INT32(21000, sample.temp);
}

void test_mpu9250_convert_uses_accel_full_scale_range(void)
{
    mpu9250_sample_t sample;

    _config.accel_fs = MPU9250_ACCEL_FS_2;
    mpu9250_init(&_imu, &_config);

    sample.accel.x =  5000;
    sample.accel.y = 10000;
    sample.accel.z = 15000;

    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_INT32_WITHIN(3, 305, sample.accel.x);
    TEST_ASSERT_INT32_WITHIN(6, 610, sample.accel.y);
    TEST_ASSERT_INT32_WITHIN(9, 915, sample.accel.z);

    _config.accel_fs = MPU9250_ACCEL_FS_4;
    mpu9250_init(&_imu, &_config);

    sample.accel.x =  5000;
    sample.accel.y = 10000;
    sample.accel.z = 15000;

    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_INT32_WITHIN(6,   610, sample.accel.x);
    TEST_ASSERT_INT32_WITHIN(12, 1220, sample.accel.y);
    TEST_ASSERT_INT32_WITHIN(18, 1831, sample.accel.z);

    _config.accel_fs = MPU9250_ACCEL_FS_8;
    mpu9250_init(&_imu, &_config);

    sample.accel.x =  5000;
    sample.accel.y = 10000;
    sample.accel.z = 15000;

    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_INT32_WITHIN(12, 1220, sample.accel.x);
    TEST_ASSERT_INT32_WITHIN(24, 2441, sample.accel.y);
    TEST_ASSERT_INT32_WITHIN(36, 3662, sample.accel.z);

    _config.accel_fs = MPU9250_ACCEL_FS_16;
    mpu9250_init(&_imu, &_config);

    sample.accel.x =  5000;
    sample.accel.y = 10000;
    sample.accel.z = 15000;

    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_INT32_WITHIN(24, 2441, sample.accel.x);
    TEST_ASSERT_INT32_WITHIN(48, 4882, sample.accel.y);
    TEST_ASSERT_INT32_WITHIN(73, 7324, sample.accel.z);
}

void test_mpu9250_convert_uses_gyro_full_scale_range(void)
{
    mpu9250_sample_t sample;

    _config.gyro_fs = MPU9250_GYRO_FS_250;
    mpu9250_init(&_imu, &_config);

    sample.gyro.x =  5000;
    sample.gyro.y = -5000;
    sample.gyro.z = 15000;

    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_INT32_WITHIN( 38,  38146, sample.gyro.x);
    TEST_ASSERT_INT32_WITHIN( 38, -38146, sample.gyro.y);
    TEST_ASSERT_INT32_WITHIN(114, 114441, sample.gyro.z);

    _config.gyro_fs = MPU9250_GYRO_FS_500;
    mpu9250_init(&_imu, &_config);

    sample.gyro.x =  5000;
    sample.gyro.y = -5000;
    sample.gyro.z = 15000;

    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_INT32_WITHIN( 76,  76294, sample.gyro.x);
    TEST_ASSERT_INT32_WITHIN( 76, -76294, sample.gyro.y);
    TEST_ASSERT_INT32_WITHIN(229, 228881, sample.gyro.z);

    _config.gyro_fs = MPU9250_GYRO_FS_1000;
    mpu9250_init(&_imu, &_config);

    sample.gyro.x =  5000;
    sample.gyro.y = -5000;
    sample.gyro.z = 15000;

    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_INT32_WITHIN(153,  152588, sample.gyro.x);
    TEST_ASSERT_INT32_WITHIN(153, -152588, sample.gyro.y);
    TEST_ASSERT_INT32_WITHIN(458,  457764, sample.gyro.z);

    _config.gyro_fs = MPU9250_GYRO_FS_2000;
    mpu9250_init(&_imu, &_config);

    sample.gyro.x =  5000;
    sample.gyro.y = -5000;
    sample.gyro.z = 15000;

    mpu9250_convert(&_imu, &sample);

    TEST_ASSERT_INT32_WITHIN(305,  305176, sample.gyro.x);
    TEST_ASSERT_INT32_WITHIN(305, -305176, sample.gyro.y);
    TEST_ASSERT_INT32_WITHIN(916,  915527, sample.gyro.z);
}

void test_mpu9250_converts_temp(void)
{
    struct temp_count_pairs {
        int32_t count;
        int32_t temp;
    };

    static const struct temp_count_pairs pairs[] = {
        { .count = 0,      .temp =  21000 },
        { .count = 6344,   .temp =  40001 },
        { .count = -20366, .temp = -39999 },
    };

    mpu9250_init(&_imu, &_config);

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(pairs); i++) {
        mpu9250_sample_t sample;
        sample.temp = pairs[i].count;

        mpu9250_convert(&_imu, &sample);

        int32_t temp = pairs[i].temp;
        TEST_ASSERT_INT32_WITHIN(temp/1000,  temp, sample.temp);
    }
}

void test_mpu9250_convert_detects_invalid_handle(void)
{
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_convert_null_handle);
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_convert_static_uninit_handle);
}

void test_mpu9250_convert_detects_invalid_sample(void)
{
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_convert_null_sample);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _mpu9250_convert_null_handle(void)
{
    mpu9250_sample_t sample;

    mpu9250_convert(NULL, &sample);
}

static void _mpu9250_convert_static_uninit_handle(void)
{
    static mpu9250_t imu;
    mpu9250_sample_t sample;

    mpu9250_convert(&imu, &sample);
}

static void _mpu9250_convert_null_sample(void)
{
    mpu9250_convert(&_imu, NULL);
}

/** @} defgroup MPU9250_TEST */
/** @} addtogroup MPU9250 */
