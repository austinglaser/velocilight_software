/**@file    test_i2c_al_port.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   I2C_ALPort Test Source
 *
 * @addtogroup I2C_AL_PORT
 * @{
 *
 * @defgroup I2C_AL_PORT_TEST I2C_ALPort Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* Test framework */
#include "unity.h"

/* Module under test */
#include "i2c_al_port.h"

/* Supporting modules */
#include "i2c_al.h"
#include "error.h"
#include "util.h"

/* Mocks, fakes, test support */
#include "ensure_support.h"
#include "hal.h"
#include "mock_i2c.h"

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

/** Call @ref i2c_al_read with a null i2c parameter */
static void _i2c_al_read_null_handle(void);

/** Call @ref i2c_al_read with a null output buffer */
static void _i2c_al_read_null_read_data(void);

/** Call @ref i2c_al_read with a zero read length */
static void _i2c_al_read_zero_read_len(void);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

/** Fake hardware driver instance */
static I2CDriver i2c_hw_driver;

/** Fake hardware driver config */
static I2CConfig i2c_hw_config;

/** I2C handle for testing */
static i2c_al_t i2c;

/** Hardware configuration */
static i2c_al_config_t i2c_config = {
    .hw_driver = &i2c_hw_driver,
    .hw_config = &i2c_hw_config,
    .share_bus = false,
};

/** Flags which driver should consider hardware errors
 *
 * TODO: Maybe add more granularity to error reporting
 */
static const i2cflags_t hardware_err_flags[] = {
    I2C_BUS_ERROR,
    I2C_OVERRUN,
};

/** Flags which driver should consider communication errors
 *
 * TODO: Maybe add more granularity to error reporting
 */
static const i2cflags_t comm_err_flags[] = {
    I2C_ARBITRATION_LOST,
    I2C_ACK_FAILURE,
    I2C_PEC_ERROR,
    I2C_TIMEOUT,
};

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void setUp(void)
{
    i2cStart_Expect(&i2c_hw_driver, &i2c_hw_config);

    i2c_al_init(&i2c, &i2c_config);
}

/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_i2c_al_read_receives(void)
{
    uint8_t dev_addr = 0x03;
    uint8_t read_data[] = {0x84, 0x99, 0xF8, 0x32};
    uint8_t read_len = ARRAY_ELEMENTS(read_data);
    i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                            dev_addr,
                                            NULL, read_len,
                                            TIME_INFINITE,
                                            MSG_OK);
    i2cMasterReceiveTimeout_IgnoreArg_rxbuf();
    i2cMasterReceiveTimeout_ReturnArrayThruPtr_rxbuf(read_data, read_len);

    uint8_t read_buf[read_len];
    err_t err;
    err = i2c_al_read(&i2c, dev_addr, read_buf, read_len);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(read_data, read_buf, read_len);
}

void test_i2c_al_read_timeout_receives(void)
{
    uint8_t dev_addr = 0x03;
    uint8_t read_data[] = {0x84, 0x99, 0xF8, 0x32};
    uint8_t read_len = ARRAY_ELEMENTS(read_data);
    uint32_t timeout = 2500;
    i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                            dev_addr,
                                            NULL, read_len,
                                            timeout,
                                            MSG_OK);
    i2cMasterReceiveTimeout_IgnoreArg_rxbuf();
    i2cMasterReceiveTimeout_ReturnArrayThruPtr_rxbuf(read_data, read_len);

    uint8_t read_buf[read_len];
    err_t err;
    err = i2c_al_read_timeout(&i2c, dev_addr, read_buf, read_len, timeout);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(read_data, read_buf, read_len);
}

void test_i2c_al_read_detects_invalid_parameters(void)
{
    /* Ignoring i2cMasterReceiveTimeout gives more descriptive failure
     * messages */
    i2cMasterReceiveTimeout_IgnoreAndReturn(MSG_OK);

    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_read_null_handle,
                                     "Should catch NULL i2c handle.");
    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_read_null_read_data,
                                     "Should catch NULL read buffer.");
    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_read_zero_read_len,
                                     "Should catch zero-length read.");
}

void test_i2c_al_read_detects_i2c_hardware_errors(void)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(hardware_err_flags); i++) {
        uint8_t dev_addr = 0x31;
        size_t read_len = 5;
        i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                                dev_addr,
                                                NULL,       read_len,
                                                TIME_INFINITE,
                                                MSG_RESET);
        i2cMasterReceiveTimeout_IgnoreArg_rxbuf();

        i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, hardware_err_flags[i]);

        err_t err;
        uint8_t read_buf[read_len];
        err = i2c_al_read(&i2c, dev_addr, read_buf, read_len);
        TEST_ASSERT_EQUAL(ERROR_HW, err);
    }
}

void test_i2c_al_read_detects_i2c_communication_errors(void)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(comm_err_flags); i++) {
        uint8_t dev_addr = 0x31;
        size_t read_len = 5;
        i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                                dev_addr,
                                                NULL,       read_len,
                                                TIME_INFINITE,
                                                MSG_RESET);
        i2cMasterReceiveTimeout_IgnoreArg_rxbuf();

        i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, comm_err_flags[i]);

        err_t err;
        uint8_t read_buf[read_len];
        err = i2c_al_read(&i2c, dev_addr, read_buf, read_len);
        TEST_ASSERT_EQUAL(ERROR_COMM, err);
    }
}

void test_i2c_al_read_timeout_detects_i2c_hardware_errors(void)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(hardware_err_flags); i++) {
        uint8_t dev_addr = 0x31;
        size_t read_len = 5;
        uint32_t timeout = 89;
        i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                                dev_addr,
                                                NULL,       read_len,
                                                timeout,
                                                MSG_RESET);
        i2cMasterReceiveTimeout_IgnoreArg_rxbuf();

        i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, hardware_err_flags[i]);

        err_t err;
        uint8_t read_buf[read_len];
        err = i2c_al_read_timeout(&i2c, dev_addr,
                                  read_buf, read_len,
                                  timeout);
        TEST_ASSERT_EQUAL(ERROR_HW, err);
    }
}

void test_i2c_al_read_timeout_detects_i2c_communication_errors(void)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(comm_err_flags); i++) {
        uint8_t dev_addr = 0x31;
        size_t read_len = 5;
        uint32_t timeout = 50;
        i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                                dev_addr,
                                                NULL,       read_len,
                                                timeout,
                                                MSG_RESET);
        i2cMasterReceiveTimeout_IgnoreArg_rxbuf();

        i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, comm_err_flags[i]);

        err_t err;
        uint8_t read_buf[read_len];
        err = i2c_al_read_timeout(&i2c, dev_addr,
                                   read_buf, read_len,
                                   timeout);
        TEST_ASSERT_EQUAL(ERROR_COMM, err);
    }
}

void test_i2c_al_read_timeout_detects_timeout(void)
{
    uint8_t dev_addr = 0x89;
    size_t read_len = 3;
    uint32_t timeout = 50;
    i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                            dev_addr,
                                            NULL,       read_len,
                                            timeout,
                                            MSG_TIMEOUT);
    i2cMasterReceiveTimeout_IgnoreArg_rxbuf();

    err_t err;
    uint8_t read_buf[read_len];
    err = i2c_al_read_timeout(&i2c, dev_addr,
                               read_buf, read_len,
                               timeout);
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, err);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _i2c_al_read_null_handle(void)
{
    uint8_t read_data;
    i2c_al_read(NULL, 0x30, &read_data, 1);
}

static void _i2c_al_read_null_read_data(void)
{
    i2c_al_read(&i2c, 0x40, NULL, 1);
}

static void _i2c_al_read_zero_read_len(void)
{
    uint8_t read_data;
    i2c_al_read(&i2c, 0x50, &read_data, 0);
}

/** @} defgroup I2C_AL_PORT_TEST */
/** @} addtogroup I2C_AL_PORT */
