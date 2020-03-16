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
#include "error.h"
#include "mpu9250_registers.h"
#include "util.h"

/* Mocks, fakes, test support */
#include "mock_mpu9250_port.h"
#include "fake_mpu9250_port.h"

/* Source dependencies (present only to make Ceedling include the right
 * objects)
 */
#include "ensure_c_exception.h"

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

static mpu9250_t _imu;

static mpu9250_config_t _config;

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void setUp(void)
{
    fake_mpu9250_port_setup(&_imu.port);

    memset(&_config, 0, sizeof(_config));
}

void tearDown(void)
{
    fake_mpu9250_port_teardown(&_imu.port);
}

/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_mpu9250_init_initializes_port(void)
{
    err_t err = mpu9250_init(&_imu, &_config);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);

    TEST_ASSERT(fake_mpu9250_port_was_initialized(&_imu.port));
    TEST_ASSERT_EQUAL_PTR(&_config.port_config,
                          fake_mpu9250_port_config(&_imu.port));
}

void test_mpu9250_init_reads_whoami(void)
{
    fake_mpu9250_port_set_reg(&_imu.port,
                              MPU9250_WHO_AM_I,
                              MPU9250_WHO_AM_I_VALUE);

    err_t err = mpu9250_init(&_imu, &_config);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
}

void test_mpu9250_init_detects_invalid_whoami(void)
{
    uint8_t bad_values[] = {
        0x00,
        0x31,
        0x68,
        MPU9250_WHO_AM_I_VALUE - 1,
        MPU9250_WHO_AM_I_VALUE + 1,
        0xFF,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(bad_values); i++) {
        fake_mpu9250_port_set_reg(&_imu.port, MPU9250_WHO_AM_I, bad_values[i]);

        err_t err = mpu9250_init(&_imu, &_config);
        TEST_ASSERT_EQUAL(ERROR_HW, err);
    }
}

/*
 * The module should detect failed reads/writes at any point. However, that's
 * harder to test without imposing arbitrary order restrictions on register
 * read/write order.
 *
 * Testing the error handling for the whoami access is good for a couple
 * reasons:
 *
 * - This access must come first, so we know we're actually talking to an
 *   MPU9250 and not some other device on the bus. This means enforcing an
 *   order here is not only OK, but desired.
 * - Because this access must be first, it's the most likely place we'll
 *   encounter an error with serial comm to the IMU, and therefore critical to
 *   get right.
 */
void test_mpu9250_init_detects_failed_whoami_read(void)
{
    /* To get rid of common callback */
    mock_mpu9250_port_Destroy();
    mock_mpu9250_port_Init();

    mpu9250_port_init_Ignore();
    mpu9250_port_read_reg_ExpectAndReturn(&_imu.port, MPU9250_WHO_AM_I, NULL,
                                          ERROR_COMM);
    mpu9250_port_read_reg_IgnoreArg_value();

    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_COMM, err);
}

void test_mpu9250_init_resets_imu(void)
{
    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_MESSAGE(fake_mpu9250_port_was_reset(&_imu.port),
                        "MPU9250 was not reset");
}

void test_mpu9250_init_sets_accel_full_scale_range(void)
{
    struct accel_full_scale {
        mpu9250_accel_fs_t config;
        uint8_t reg;
    };
    const struct accel_full_scale full_scales[] = {
        {
            .config = MPU9250_ACCEL_FS_2,
            .reg = MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_2G,
        },

        {
            .config = MPU9250_ACCEL_FS_4,
            .reg = MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_4G,
        },

        {
            .config = MPU9250_ACCEL_FS_8,
            .reg = MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_8G,
        },

        {
            .config = MPU9250_ACCEL_FS_16,
            .reg = MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_16G,
        },
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(full_scales); i++) {
        _config.accel_fs = full_scales[i].config;

        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(MPU9250_ACCEL_CONFIG_ACCEL_FS_SEL_MASK,
                         full_scales[i].reg,
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_ACCEL_CONFIG));
    }
}

void test_mpu9250_init_sets_accel_sample_rate(void)
{
    struct accel_samplerate {
        mpu9250_accel_samplerate_t config;
        uint8_t reg;
        uint8_t mask;
    };
    const struct accel_samplerate samplerates[] = {
        { .config = MPU9250_ACCEL_SAMPLERATE_1k_5Hz
        , .reg    = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_5HZ
        , .mask   = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_MASK
        },

        { .config = MPU9250_ACCEL_SAMPLERATE_1k_10Hz
        , .reg    = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_10HZ
        , .mask   = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_MASK
        },

        { .config = MPU9250_ACCEL_SAMPLERATE_1k_20Hz
        , .reg    = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_20HZ
        , .mask   = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_MASK
        },

        { .config = MPU9250_ACCEL_SAMPLERATE_1k_41Hz
        , .reg    = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_41HZ
        , .mask   = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_MASK
        },

        { .config = MPU9250_ACCEL_SAMPLERATE_1k_92Hz
        , .reg    = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_92HZ
        , .mask   = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_MASK
        },

        { .config = MPU9250_ACCEL_SAMPLERATE_1k_184Hz
        , .reg    = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_184HZ
        , .mask   = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_MASK
        },

        { .config = MPU9250_ACCEL_SAMPLERATE_1k_460Hz
        , .reg    = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_A_DLPFCFG
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_460HZ
        , .mask   = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK
                  | MPU9250_ACCEL_CONFIG_2_A_DLPFCFG_MASK
        },

        { .config = MPU9250_ACCEL_SAMPLERATE_4k_1130Hz
        , .reg    = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_1130Hz
        , .mask   = MPU9250_ACCEL_CONFIG_2_ACCEL_FCHOICE_B_MASK
        },
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(samplerates); i++) {
        _config.accel_samplerate = samplerates[i].config;

        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(samplerates[i].mask,
                         samplerates[i].reg,
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_ACCEL_CONFIG_2));
    }
}

void test_mpu9250_init_sets_gyro_full_scale_range(void)
{
    struct gyro_full_scale {
        mpu9250_gyro_fs_t config;
        uint8_t reg;
    };
    struct gyro_full_scale full_scales[] = {
        { .config = MPU9250_GYRO_FS_250
        , .reg = MPU9250_GYRO_CONFIG_GYRO_FS_SEL_250DPS
        },

        { .config = MPU9250_GYRO_FS_500
        , .reg = MPU9250_GYRO_CONFIG_GYRO_FS_SEL_500DPS
        },

        { .config = MPU9250_GYRO_FS_1000
        , .reg = MPU9250_GYRO_CONFIG_GYRO_FS_SEL_1000DPS
        },

        { .config = MPU9250_GYRO_FS_2000
        , .reg = MPU9250_GYRO_CONFIG_GYRO_FS_SEL_2000DPS
        },
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(full_scales); i++) {
        _config.gyro_fs = full_scales[i].config;

        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(MPU9250_GYRO_CONFIG_GYRO_FS_SEL_MASK,
                         full_scales[i].reg,
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_GYRO_CONFIG));
    }
}

void test_mpu9250_sets_gyro_sample_rate(void)
{
    struct gyro_samplerate {
        mpu9250_gyro_samplerate_t config;
        uint8_t reg_config;
        uint8_t reg_gyro_config;
        bool care_about_config;
    };
    struct gyro_samplerate samplerates[] = {
        { .config            = MPU9250_GYRO_SAMPLERATE_1k_5Hz
        , .reg_config        = MPU9250_CONFIG_DLPF_CFG_5HZ
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG
        , .care_about_config = true,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_1k_10Hz
        , .reg_config        = MPU9250_CONFIG_DLPF_CFG_10HZ
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG
        , .care_about_config = true,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_1k_20Hz
        , .reg_config        = MPU9250_CONFIG_DLPF_CFG_20HZ
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG
        , .care_about_config = true,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_1k_41Hz
        , .reg_config        = MPU9250_CONFIG_DLPF_CFG_41HZ
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG
        , .care_about_config = true,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_1k_92Hz
        , .reg_config        = MPU9250_CONFIG_DLPF_CFG_92HZ
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG
        , .care_about_config = true,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_1k_184Hz
        , .reg_config        = MPU9250_CONFIG_DLPF_CFG_184HZ
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG
        , .care_about_config = true,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_8k_250Hz
        , .reg_config        = MPU9250_CONFIG_DLPF_CFG_250HZ
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG
        , .care_about_config = true,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_8k_3600Hz
        , .reg_config        = MPU9250_CONFIG_DLPF_CFG_3600HZ
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_DLPF_CFG
        , .care_about_config = true,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_32k_3600Hz
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_3600HZ
        , .care_about_config = false,
        },

        { .config            = MPU9250_GYRO_SAMPLERATE_32k_8800Hz
        , .reg_gyro_config   = MPU9250_GYRO_CONFIG_FCHOICE_B_8800HZ
        , .care_about_config = false,
        },
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(samplerates); i++) {
        _config.config = 0xFF;
        _config.gyro_samplerate = samplerates[i].config;

        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(MPU9250_GYRO_CONFIG_FCHOICE_B_MASK,
                         samplerates[i].reg_gyro_config,
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_GYRO_CONFIG));

        if (samplerates[i].care_about_config) {
            TEST_ASSERT_BITS(MPU9250_CONFIG_DLPF_CFG_MASK,
                             samplerates[i].reg_config,
                             fake_mpu9250_port_get_reg(&_imu.port, MPU9250_CONFIG));
        }
    }
}

void test_mpu9250_init_sets_smplrt_div(void)
{
    uint8_t smplrt_div_values[] = {
        0,
        255,
        99,
        200,
        5
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(smplrt_div_values); i++) {
        _config.smplrt_div = smplrt_div_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_EQUAL_UINT8(smplrt_div_values[i],
                                fake_mpu9250_port_get_reg(&_imu.port, MPU9250_SMPLRT_DIV));
    }
}

void test_mpu9250_init_writes_nonreserved_config_bits(void)
{
    uint8_t config_values[] = {
        0x00,
        MPU9250_CONFIG_FIFO_MODE_MASK | MPU9250_CONFIG_EXT_SYNC_SET_MASK,
        0x08,
        0x10,
        0x20,
        0x40
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(config_values); i++) {
        _config.config = config_values[i];

        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(MPU9250_CONFIG_FIFO_MODE_MASK
                         | MPU9250_CONFIG_EXT_SYNC_SET_MASK,
                         config_values[i],
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_CONFIG));
    }
}

void test_mpu9250_init_clears_reserved_config_bits(void)
{
    _config.config = 0xFF;
    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_BITS(MPU9250_CONFIG_RESERVED_MASK,
                     0,
                     fake_mpu9250_port_get_reg(&_imu.port, MPU9250_CONFIG));
}

void test_mpu9250_init_sets_lp_accel_odr(void)
{
    uint8_t odr_values[] = {
        0,
        11,
        5
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(odr_values); i++) {
        _config.lp_accel_odr = odr_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_EQUAL_UINT8(odr_values[i],
                               fake_mpu9250_port_get_reg(&_imu.port, MPU9250_LP_ACCEL_ODR));
    }
}

void test_mpu9250_init_reduces_lp_accel_odr_when_too_big(void)
{
    uint8_t odr_values[] = {
        12,
        255,
        109,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(odr_values); i++) {
        _config.lp_accel_odr = odr_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_EQUAL_UINT8(11, fake_mpu9250_port_get_reg(&_imu.port, MPU9250_LP_ACCEL_ODR));
    }
}

void test_mpu9250_init_sets_wom_thr(void)
{
    uint8_t wom_thr_values[] = {
        0,
        255,
        23,
        89,
        190
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(wom_thr_values); i++) {
        _config.wom_thr = wom_thr_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_EQUAL_HEX8(wom_thr_values[i],
                               fake_mpu9250_port_get_reg(&_imu.port, MPU9250_WOM_THR));
    }
}

void test_mpu9250_init_sets_fifo_en(void)
{
    uint8_t fifo_en_values[] = {
        0x00,
        0xFF,
        0x01,
        0x02,
        0x04,
        0x08,
        0x10,
        0x20,
        0x40,
        0x80
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(fifo_en_values); i++) {
        _config.fifo_en = fifo_en_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_EQUAL_HEX8(fifo_en_values[i],
                               fake_mpu9250_port_get_reg(&_imu.port, MPU9250_FIFO_EN));
    }
}

void test_mpu9250_init_sets_int_pin_cfg_nonreserved_bits(void)
{
    uint8_t int_pin_cfg_values[] = {
        0x00,
        0xFE,
        MPU9250_INT_PIN_CFG_ACTL,
        MPU9250_INT_PIN_CFG_OPEN,
        MPU9250_INT_PIN_CFG_LATCH_INT_EN,
        MPU9250_INT_PIN_CFG_INT_ANYRD_2CLEAR,
        MPU9250_INT_PIN_CFG_ACTL_FSYNC,
        MPU9250_INT_PIN_CFG_FSYNC_INT_MODE_EN,
        MPU9250_INT_PIN_CFG_BYPASS_EN,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(int_pin_cfg_values); i++) {
        _config.int_pin_cfg = int_pin_cfg_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(~MPU9250_INT_PIN_CFG_RESERVED_MASK & 0xFF,
                         int_pin_cfg_values[i],
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_INT_PIN_CFG));
    }
}

void test_mpu9250_init_clears_int_pin_cfg_reserved_bits(void)
{
    _config.int_pin_cfg = 0xFF;
    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_BITS(MPU9250_INT_PIN_CFG_RESERVED_MASK,
                     0,
                     fake_mpu9250_port_get_reg(&_imu.port, MPU9250_INT_PIN_CFG));
}

void test_mpu9250_init_sets_int_enable_nonreserved_bits(void)
{
    uint8_t int_enable_values[] = {
        0x00,
        0x59,
        MPU9250_INT_ENABLE_WOM_EN,
        MPU9250_INT_ENABLE_FIFO_OVERFLOW_EN,
        MPU9250_INT_ENABLE_FSYNC_INT_EN,
        MPU9250_INT_ENABLE_RAW_RDY_EN,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(int_enable_values); i++) {
        _config.int_enable = int_enable_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(~MPU9250_INT_ENABLE_RESERVED_MASK & 0xFF,
                         int_enable_values[i],
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_INT_ENABLE));
    }
}

void test_mpu9250_init_clears_int_enable_reserved_bits(void)
{
    _config.int_enable = 0xFF;
    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_BITS(MPU9250_INT_ENABLE_RESERVED_MASK,
                     0,
                     fake_mpu9250_port_get_reg(&_imu.port, MPU9250_INT_ENABLE));
}

void test_mpu9250_init_sets_mot_detect_ctrl_nonreserved_bits(void)
{
    uint8_t mot_detect_ctrl_values[] = {
        0x00,
        0xC0,
        MPU9250_MOT_DETECT_CTRL_ACCEL_INTEL_EN,
        MPU9250_MOT_DETECT_CTRL_ACCEL_INTEL_MODE,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(mot_detect_ctrl_values); i++) {
        _config.mot_detect_ctrl = mot_detect_ctrl_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(~MPU9250_MOT_DETECT_CTRL_RESERVED_MASK & 0xFF,
                         mot_detect_ctrl_values[i],
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_MOT_DETECT_CTRL));
    }
}

void test_mpu9250_init_clears_mot_detect_ctrl_reserved_bits(void)
{
    _config.mot_detect_ctrl = 0xFF;
    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_BITS(MPU9250_MOT_DETECT_CTRL_RESERVED_MASK,
                     0,
                     fake_mpu9250_port_get_reg(&_imu.port, MPU9250_MOT_DETECT_CTRL));
}

void test_mpu9250_init_sets_user_ctrl_nonreserved_bits(void)
{
    uint8_t user_ctrl_values[] = {
        0x00,
        0x60,
        0x20,
        0x40,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(user_ctrl_values); i++) {
        _config.user_ctrl = user_ctrl_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(~(MPU9250_USER_CTRL_RESERVED_MASK
                           | MPU9250_USER_CTRL_I2C_IF_DIS
                           | MPU9250_USER_CTRL_FIFO_RST
                           | MPU9250_USER_CTRL_I2C_MST_RST
                           | MPU9250_USER_CTRL_SIG_COND_RST)
                         & 0xFF,
                         user_ctrl_values[i],
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_USER_CTRL));
    }
}

void test_mpu9250_init_clears_user_ctrl_reserved_bits(void)
{
    _config.user_ctrl = 0xFF;
    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_BITS(MPU9250_USER_CTRL_RESERVED_MASK
                     | MPU9250_USER_CTRL_I2C_IF_DIS
                     | MPU9250_USER_CTRL_FIFO_RST
                     | MPU9250_USER_CTRL_I2C_MST_RST
                     | MPU9250_USER_CTRL_SIG_COND_RST,
                     0,
                     fake_mpu9250_port_get_reg(&_imu.port, MPU9250_USER_CTRL));
}

void test_mpu9250_init_sets_pwr_mgmt_1_clksel_field(void)
{
    uint8_t pwr_mgmt_1_values[] = {
        0x00,
        0x07,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(pwr_mgmt_1_values); i++) {
        _config.pwr_mgmt_1 = pwr_mgmt_1_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(MPU9250_PWR_MGMT_1_CLKSEL_MASK,
                         pwr_mgmt_1_values[i],
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_PWR_MGMT_1));
    }
}

void test_mpu9250_init_clears_pwr_mgmt_1_reserved_bits(void)
{
    _config.pwr_mgmt_1 = 0xFF;
    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_BITS(~MPU9250_PWR_MGMT_1_CLKSEL_MASK & 0xFF,
                     0,
                     fake_mpu9250_port_get_reg(&_imu.port, MPU9250_PWR_MGMT_1));
}

void test_mpu9250_init_sets_pwr_mgmt_2_nonreserved_bits(void)
{
    uint8_t pwr_mgmt_2_values[] = {
        0x00,
        0x3F,
        MPU9250_PWR_MGMT_2_DISABLE_XA,
        MPU9250_PWR_MGMT_2_DISABLE_YA,
        MPU9250_PWR_MGMT_2_DISABLE_ZA,
        MPU9250_PWR_MGMT_2_DISABLE_XG,
        MPU9250_PWR_MGMT_2_DISABLE_YG,
        MPU9250_PWR_MGMT_2_DISABLE_ZG,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(pwr_mgmt_2_values); i++) {
        _config.pwr_mgmt_2 = pwr_mgmt_2_values[i];
        err_t err = mpu9250_init(&_imu, &_config);

        TEST_ASSERT_EQUAL(ERROR_NONE, err);
        TEST_ASSERT_BITS(~MPU9250_PWR_MGMT_2_RESERVED_MASK & 0xFF,
                         pwr_mgmt_2_values[i],
                         fake_mpu9250_port_get_reg(&_imu.port, MPU9250_PWR_MGMT_2));
    }
}

void test_mpu9250_init_clears_pwr_mgmt_2_reserved_bits(void)
{
    _config.pwr_mgmt_2 = 0xFF;
    err_t err = mpu9250_init(&_imu, &_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_BITS(MPU9250_PWR_MGMT_2_RESERVED_MASK,
                     0,
                     fake_mpu9250_port_get_reg(&_imu.port, MPU9250_PWR_MGMT_2));
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup MPU9250_TEST */
/** @} addtogroup MPU9250 */
