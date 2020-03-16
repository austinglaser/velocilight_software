/**@file    test_i2c_al_port_write.c
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

/** Call @ref i2c_al_transfer() with the i2c parameter null  */
static void _i2c_al_transfer_null_handle(void);

/** Call @ref i2c_al_transfer() with the data parameter null  */
static void _i2c_al_transfer_null_write_data(void);

/** Call @ref i2c_al_transfer() with a zero write length  */
static void _i2c_al_transfer_zero_write_length(void);

/** Call @ref i2c_al_transfer() with NULL read parameter, but nonzero read
 * length.
 */
static void _i2c_al_transfer_null_read_data_nonzero_read_len(void);

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

void test_i2c_al_transfer_transmits(void)
{
    uint8_t dev_addr = 0x70;
    uint8_t write_data[] = {0x01, 0x02, 0xFF};
    size_t write_len = ARRAY_ELEMENTS(write_data);
    i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                             dev_addr,
                                             write_data, write_len,
                                             NULL,       0,
                                             TIME_INFINITE,
                                             MSG_OK);

    err_t err;
    err = i2c_al_transfer(&i2c, dev_addr, write_data, write_len, NULL, 0);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
}

void test_i2c_al_transfer_detects_invalid_parameters(void)
{
    /* Ignoring i2cMasterTransmitTimeout gives more descriptive failure
     * messages */
    i2cMasterTransmitTimeout_IgnoreAndReturn(MSG_OK);

    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_transfer_null_handle,
                                     "Should catch null i2c handle.");
    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_transfer_null_write_data,
                                     "Should catch null write buffer.");
    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_transfer_zero_write_length,
                                     "Should catch zero-length write.");
    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_transfer_null_read_data_nonzero_read_len,
                                     "Should catch attempt to read into null buffer.");
}

void test_i2c_al_transfer_classifies_hardware_errors(void)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(hardware_err_flags); i++) {
        uint8_t dev_addr = 0x31;
        uint8_t write_data[] = {0x80, 0x2F, 0x3E, 0xF1, 0x00};
        size_t write_len = ARRAY_ELEMENTS(write_data);
        i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                                 dev_addr,
                                                 write_data, write_len,
                                                 NULL,       0,
                                                 TIME_INFINITE,
                                                 MSG_RESET);
        i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, hardware_err_flags[i]);

        err_t err;
        err = i2c_al_transfer(&i2c, dev_addr, write_data, write_len, NULL, 0);
        TEST_ASSERT_EQUAL(ERROR_HW, err);
    }
}

void test_i2c_al_transfer_classifies_communication_errors(void)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(comm_err_flags); i++) {
        uint8_t dev_addr = 0x31;
        uint8_t write_data[] = {0x80, 0x2F, 0x3E, 0xF1, 0x00};
        size_t write_len = ARRAY_ELEMENTS(write_data);
        i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                                 dev_addr,
                                                 write_data, write_len,
                                                 NULL,       0,
                                                 TIME_INFINITE,
                                                 MSG_RESET);
        i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, comm_err_flags[i]);

        err_t err;
        err = i2c_al_transfer(&i2c, dev_addr, write_data, write_len, NULL, 0);
        TEST_ASSERT_EQUAL(ERROR_COMM, err);
    }
}

void test_i2c_al_transfer_can_write_then_read(void)
{
    uint8_t dev_addr = 0x22;
    uint8_t write_data[] = {0x01, 0xFF};
    size_t write_len = ARRAY_ELEMENTS(write_data);
    uint8_t read_data[] = {0x05, 0x04, 0x03, 0x02};
    size_t read_len = ARRAY_ELEMENTS(read_data);
    i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                             dev_addr,
                                             write_data, write_len,
                                             NULL,  read_len,
                                             TIME_INFINITE,
                                             MSG_OK);
    i2cMasterTransmitTimeout_IgnoreArg_rxbuf();
    i2cMasterTransmitTimeout_ReturnArrayThruPtr_rxbuf(read_data, read_len);

    err_t err;
    uint8_t read_buf[read_len];
    err = i2c_al_transfer(&i2c, dev_addr,
                        write_data, write_len,
                        read_buf, read_len);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(read_data, read_buf, read_len);
}

void test_i2c_al_transfer_timeout_transmits(void)
{
    uint8_t dev_addr = 0x64;
    uint8_t write_data[] = {0x01, 0x02, 0xFF, 0x88, 0x88, 0xAA};
    size_t write_len = ARRAY_ELEMENTS(write_data);
    uint32_t timeout = 3000;
    i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                             dev_addr,
                                             write_data, write_len,
                                             NULL,       0,
                                             timeout,
                                             MSG_RESET);

    i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, I2C_NO_ERROR);

    err_t err;
    err = i2c_al_transfer_timeout(&i2c,
                                  dev_addr,
                                  write_data, write_len,
                                  NULL, 0,
                                  timeout);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
}

void test_i2c_al_transfer_detects_timeout(void)
{
    uint8_t dev_addr = 0x64;
    uint8_t write_data[] = {0x01, 0x02, 0xFF, 0x88, 0x88, 0xAA};
    size_t write_len = ARRAY_ELEMENTS(write_data);
    uint32_t timeout = 3000;
    i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                             dev_addr,
                                             write_data, write_len,
                                             NULL,       0,
                                             timeout,
                                             MSG_TIMEOUT);

    err_t err;
    err = i2c_al_transfer_timeout(&i2c,
                                  dev_addr,
                                  write_data, write_len,
                                  NULL, 0,
                                  timeout);
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, err);
}

void test_i2c_al_transfer_timeout_classifies_hardware_errors(void)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(hardware_err_flags); i++) {
        uint8_t dev_addr = 0x31;
        uint8_t write_data[] = {0x80, 0x2F, 0x3E, 0xF1, 0x00};
        size_t write_len = ARRAY_ELEMENTS(write_data);
        uint32_t timeout = 8000;
        i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                                 dev_addr,
                                                 write_data, write_len,
                                                 NULL,       0,
                                                 timeout,
                                                 MSG_RESET);
        i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, hardware_err_flags[i]);

        err_t err;
        err = i2c_al_transfer_timeout(&i2c, dev_addr,
                                      write_data, write_len,
                                      NULL, 0,
                                      timeout);
        TEST_ASSERT_EQUAL(ERROR_HW, err);
    }
}

void test_i2c_al_transfer_timeout_classifies_communication_errors(void)
{
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(comm_err_flags); i++) {
        uint8_t dev_addr = 0x31;
        uint8_t write_data[] = {0x80, 0x2F, 0x3E, 0xF1, 0x00};
        size_t write_len = ARRAY_ELEMENTS(write_data);
        uint32_t timeout = 200;
        i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                                 dev_addr,
                                                 write_data, write_len,
                                                 NULL,       0,
                                                 timeout,
                                                 MSG_RESET);
        i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, comm_err_flags[i]);

        err_t err;
        err = i2c_al_transfer_timeout(&i2c, dev_addr,
                                      write_data, write_len,
                                      NULL, 0,
                                      timeout);
        TEST_ASSERT_EQUAL(ERROR_COMM, err);
    }
}

void test_i2c_al_transfer_timeout_can_write_then_read(void)
{
    uint8_t dev_addr = 0x22;
    uint8_t write_data[] = {0x01, 0xFF};
    size_t write_len = ARRAY_ELEMENTS(write_data);
    uint8_t read_data[] = {0x05, 0x04, 0x03, 0x02};
    size_t read_len = ARRAY_ELEMENTS(read_data);
    uint32_t timeout = 3;
    i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                             dev_addr,
                                             write_data, write_len,
                                             NULL,  read_len,
                                             timeout,
                                             MSG_OK);
    i2cMasterTransmitTimeout_IgnoreArg_rxbuf();
    i2cMasterTransmitTimeout_ReturnArrayThruPtr_rxbuf(read_data, read_len);

    err_t err;
    uint8_t read_buf[read_len];
    err = i2c_al_transfer_timeout(&i2c, dev_addr,
                                  write_data, write_len,
                                  read_buf, read_len,
                                  timeout);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(read_data, read_buf, read_len);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _i2c_al_transfer_null_handle(void)
{
    uint8_t data;
    i2c_al_transfer(NULL, 0x10, &data, 1, NULL, 0);
}

static void _i2c_al_transfer_null_write_data(void)
{
    i2c_al_transfer(&i2c, 0x10, NULL, 1, NULL, 0);
}

static void _i2c_al_transfer_zero_write_length(void)
{
    uint8_t data;
    i2c_al_transfer(&i2c, 0x10, &data, 0, NULL, 0);
}

static void _i2c_al_transfer_null_read_data_nonzero_read_len(void)
{
    uint8_t data;
    i2c_al_transfer(&i2c, 0x10, &data, 1, NULL, 1);
}

/** @} defgroup I2C_AL_PORT_TEST */
/** @} addtogroup I2C_AL_PORT */
