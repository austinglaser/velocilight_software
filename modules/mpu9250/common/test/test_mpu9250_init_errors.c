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

/* Mocks, fakes, test support */
#include "ensure_support.h"
#include "mock_mpu9250_port.h"
#include "util.h"

/* Source dependencies (present only to make Ceedling include the right
 * objects)
 */
#include "ensure_c_exception.h"
#include "unity_util.h"

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */

static void _mpu9250_init_null_handle(void);

static void _mpu9250_init_null_config(void);

static void _mpu9250_init_shared_config(void);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

static mpu9250_config_t _shared_config;

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void setUp(void)
{
    memset(&_shared_config, 0, sizeof(_shared_config));
}

/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_mpu9250_init_detects_bad_handle(void)
{
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_init_null_handle);
}

void test_mpu9250_init_detects_null_config(void)
{
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_init_null_config);
}

void test_mpu9250_init_detects_invalid_accel_full_scale_range(void)
{
    mpu9250_accel_fs_t bad_accel_fs[] = {
        MPU9250_ACCEL_FS_2 - 1,
        MPU9250_ACCEL_FS_16 + 1,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(bad_accel_fs); i++) {
        _shared_config.accel_fs = bad_accel_fs[i];
        TEST_ASSERT_FAILS_ENSURE(_mpu9250_init_shared_config);
    }
}

void test_mpu9250_init_detects_invalid_accel_samplerate(void)
{
    mpu9250_accel_fs_t bad_accel_samplerate[] = {
        MPU9250_ACCEL_SAMPLERATE_1k_5Hz - 1,
        MPU9250_ACCEL_SAMPLERATE_4k_1130Hz + 1,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(bad_accel_samplerate); i++) {
        _shared_config.accel_samplerate = bad_accel_samplerate[i];
        TEST_ASSERT_FAILS_ENSURE(_mpu9250_init_shared_config);
    }
}

void test_mpu9250_init_detects_invalid_gyro_full_scale_range(void)
{
    mpu9250_accel_fs_t bad_gyro_fs[] = {
        MPU9250_GYRO_FS_250 - 1,
        MPU9250_GYRO_FS_2000 + 1,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(bad_gyro_fs); i++) {
        _shared_config.gyro_fs = bad_gyro_fs[i];
        TEST_ASSERT_FAILS_ENSURE(_mpu9250_init_shared_config);
    }
}

void test_mpu9250_init_detects_invalid_gyro_samplerate(void)
{
    mpu9250_gyro_fs_t bad_gyro_samplerate[] = {
        MPU9250_GYRO_SAMPLERATE_1k_5Hz - 1,
        MPU9250_GYRO_SAMPLERATE_32k_8800Hz + 1,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(bad_gyro_samplerate); i++) {
        _shared_config.gyro_samplerate = bad_gyro_samplerate[i];
        TEST_ASSERT_FAILS_ENSURE(_mpu9250_init_shared_config);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _mpu9250_init_null_handle(void)
{
    static mpu9250_config_t config;

    mpu9250_init(NULL, &config);
}

static void _mpu9250_init_null_config(void)
{
    mpu9250_t imu;

    mpu9250_init(&imu, NULL);
}

static void _mpu9250_init_shared_config(void)
{
    mpu9250_t imu;

    mpu9250_init(&imu, &_shared_config);
}

/** @} defgroup MPU9250_TEST */
/** @} addtogroup MPU9250 */
