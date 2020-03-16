/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   Mpu9250Port Test Source
///
/// @addtogroup MPU9250_PORT
/// @{
///
/// @defgroup MPU9250_PORT_TEST Mpu9250Port Tests
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// Test framework
#include "unity.h"

// Module under test
#include "mpu9250_port.h"
#include "mpu9250_registers.h"

// Supporting modules

// Mocks, fakes, test support
#include "mock_nrf_drv_twi.h"

// Source dependencies (present only to make Ceedling include the right
// objects)
#include "ensure_c_exception.h"

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //
// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //
// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //
// --- PUBLIC TESTS -------------------------------------------------------- //

void test_mpu9250_port_read_reg_uses_ad0_low_address(void)
{
    nrf_drv_twi_t twi;
    mpu9250_port_config_t config = {
        .twi = &twi,
        .ad0 = false,
    };
    mpu9250_port_t port;

    mpu9250_port_init(&port, &config);

    nrf_drv_twi_tx_ExpectAndReturn(
        &twi,
        MPU9250_I2C_ADDR,
        NULL,
        0,
        true,

        NRF_SUCCESS
    );
    nrf_drv_twi_tx_IgnoreArg_p_data();
    nrf_drv_twi_tx_IgnoreArg_length();

    nrf_drv_twi_rx_ExpectAndReturn(
        &twi,
        MPU9250_I2C_ADDR,
        NULL,
        0,

        NRF_SUCCESS
    );
    nrf_drv_twi_rx_IgnoreArg_p_data();
    nrf_drv_twi_rx_IgnoreArg_length();

    uint8_t val;
    TEST_ASSERT_EQUAL(ERROR_NONE, mpu9250_port_read_reg(&port, 0, &val));
}

void test_mpu9250_port_read_reg_uses_ad0_high_address(void)
{
    nrf_drv_twi_t twi;
    mpu9250_port_config_t config = {
        .twi = &twi,
        .ad0 = true,
    };
    mpu9250_port_t port;

    mpu9250_port_init(&port, &config);

    nrf_drv_twi_tx_ExpectAndReturn(
        &twi,
        MPU9250_I2C_ADDR | 1,
        NULL,
        0,
        true,

        NRF_SUCCESS
    );
    nrf_drv_twi_tx_IgnoreArg_p_data();
    nrf_drv_twi_tx_IgnoreArg_length();

    nrf_drv_twi_rx_ExpectAndReturn(
        &twi,
        MPU9250_I2C_ADDR | 1,
        NULL,
        0,

        NRF_SUCCESS
    );
    nrf_drv_twi_rx_IgnoreArg_p_data();
    nrf_drv_twi_rx_IgnoreArg_length();

    uint8_t val;
    TEST_ASSERT_EQUAL(ERROR_NONE, mpu9250_port_read_reg(&port, 0, &val));
}

void test_mpu9250_port_write_reg_uses_ad0_low_address(void)
{
    nrf_drv_twi_t twi;
    mpu9250_port_config_t config = {
        .twi = &twi,
        .ad0 = false,
    };
    mpu9250_port_t port;

    mpu9250_port_init(&port, &config);

    nrf_drv_twi_tx_ExpectAndReturn(
        &twi,
        MPU9250_I2C_ADDR,
        NULL,
        0,
        false,

        NRF_SUCCESS
    );
    nrf_drv_twi_tx_IgnoreArg_p_data();
    nrf_drv_twi_tx_IgnoreArg_length();

    TEST_ASSERT_EQUAL(ERROR_NONE, mpu9250_port_write_reg(&port, 0, 0));
}

void test_mpu9250_port_write_reg_uses_ad0_high_address(void)
{
    nrf_drv_twi_t twi;
    mpu9250_port_config_t config = {
        .twi = &twi,
        .ad0 = true,
    };
    mpu9250_port_t port;

    mpu9250_port_init(&port, &config);

    nrf_drv_twi_tx_ExpectAndReturn(
        &twi,
        MPU9250_I2C_ADDR | 1,
        NULL,
        0,
        false,

        NRF_SUCCESS
    );
    nrf_drv_twi_tx_IgnoreArg_p_data();
    nrf_drv_twi_tx_IgnoreArg_length();

    TEST_ASSERT_EQUAL(ERROR_NONE, mpu9250_port_write_reg(&port, 0, 0));
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

/// @} defgroup MPU9250_PORT_TEST
/// @} addtogroup MPU9250_PORT
