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
    .share_bus = true,
};

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void setUp(void)
{
    i2c_al_init(&i2c, &i2c_config);
}

void test_i2c_al_read_acquires_and_releases_bus(void)
{
    uint8_t dev_addr = 0x33;
    uint8_t read_data[] = {0x01};
    size_t read_len = ARRAY_ELEMENTS(read_data);


    i2cAcquireBus_Expect(&i2c_hw_driver);
    i2cStart_Expect(&i2c_hw_driver, &i2c_hw_config);
    i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                            dev_addr,
                                            NULL, read_len,
                                            TIME_INFINITE,
                                            MSG_OK);
    i2cMasterReceiveTimeout_IgnoreArg_rxbuf();
    i2cMasterReceiveTimeout_ReturnArrayThruPtr_rxbuf(read_data, read_len);
    i2cReleaseBus_Expect(&i2c_hw_driver);

    uint8_t read_buf[read_len];
    err_t err;
    err = i2c_al_read(&i2c, dev_addr, read_buf, read_len);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(read_data, read_buf, read_len);
}

void test_i2c_al_read_acquires_and_releases_bus_when_error(void)
{
    uint8_t dev_addr = 0x33;
    uint8_t read_data[] = {0x01};
    size_t read_len = ARRAY_ELEMENTS(read_data);


    i2cAcquireBus_Expect(&i2c_hw_driver);
    i2cStart_Expect(&i2c_hw_driver, &i2c_hw_config);
    i2cMasterReceiveTimeout_ExpectAndReturn(&i2c_hw_driver,
                                            dev_addr,
                                            NULL, read_len,
                                            TIME_INFINITE,
                                            MSG_RESET);
    i2cMasterReceiveTimeout_IgnoreArg_rxbuf();
    i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, I2C_ACK_FAILURE);
    i2cReleaseBus_Expect(&i2c_hw_driver);

    uint8_t read_buf[read_len];
    err_t err;
    err = i2c_al_read(&i2c, dev_addr, read_buf, read_len);
    TEST_ASSERT_EQUAL(ERROR_COMM, err);
}

void test_i2c_al_transfer_acquires_and_releases_bus(void)
{
    uint8_t dev_addr = 0x33;
    uint8_t write_data[] = {0x01};
    size_t write_len = ARRAY_ELEMENTS(write_data);
    uint8_t read_data[] = {0x01, 0x50};
    size_t read_len = ARRAY_ELEMENTS(read_data);


    i2cAcquireBus_Expect(&i2c_hw_driver);
    i2cStart_Expect(&i2c_hw_driver, &i2c_hw_config);
    i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                             dev_addr,
                                             write_data, write_len,
                                             NULL, read_len,
                                             TIME_INFINITE,
                                             MSG_OK);
    i2cMasterTransmitTimeout_IgnoreArg_rxbuf();
    i2cMasterTransmitTimeout_ReturnArrayThruPtr_rxbuf(read_data, read_len);
    i2cReleaseBus_Expect(&i2c_hw_driver);

    uint8_t read_buf[read_len];
    err_t err;
    err = i2c_al_transfer(&i2c, dev_addr,
                        write_data, write_len,
                        read_buf, read_len);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(read_data, read_buf, read_len);
}

void test_i2c_al_transfer_acquires_and_releases_bus_when_error(void)
{
    uint8_t dev_addr = 0x33;
    uint8_t write_data[] = {0x01};
    size_t write_len = ARRAY_ELEMENTS(write_data);
    uint8_t read_data[] = {0x01, 0x50};
    size_t read_len = ARRAY_ELEMENTS(read_data);


    i2cAcquireBus_Expect(&i2c_hw_driver);
    i2cStart_Expect(&i2c_hw_driver, &i2c_hw_config);
    i2cMasterTransmitTimeout_ExpectAndReturn(&i2c_hw_driver,
                                             dev_addr,
                                             write_data, write_len,
                                             NULL, read_len,
                                             TIME_INFINITE,
                                             MSG_RESET);
    i2cMasterTransmitTimeout_IgnoreArg_rxbuf();
    i2cGetErrors_ExpectAndReturn(&i2c_hw_driver, I2C_OVERRUN);
    i2cReleaseBus_Expect(&i2c_hw_driver);

    uint8_t read_buf[read_len];
    err_t err;
    err = i2c_al_transfer(&i2c, dev_addr,
                        write_data, write_len,
                        read_buf, read_len);
    TEST_ASSERT_EQUAL(ERROR_HW, err);
}

/* --- PUBLIC TESTS -------------------------------------------------------- */
/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup I2C_AL_PORT_TEST */
/** @} addtogroup I2C_AL_PORT */
