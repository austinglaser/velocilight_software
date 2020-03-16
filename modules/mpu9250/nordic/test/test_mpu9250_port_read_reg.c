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
#include "ensure_support.h"
#include "mock_nrf_drv_twi.h"
#include "unity_util.h"

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

static void _mpu9250_port_read_register_port(void * port);
static void _mpu9250_port_read_register_addr(void * addr);
static void _mpu9250_port_read_register_value(void * value);

// --- PUBLIC VARIABLES ---------------------------------------------------- //

const nrf_drv_twi_t _twi;

mpu9250_port_t _port;
mpu9250_port_config_t _config = {
    .twi = &_twi,
    .ad0 = false,
};

// --- PRIVATE VARIABLES --------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

void setUp(void)
{
    mpu9250_port_init(&_port, &_config);
}

// --- PUBLIC TESTS -------------------------------------------------------- //
//
TEST_VALUE(0x00, 0x00)
TEST_VALUE(0x01, 0x00)
TEST_VALUE(0x00, 0x01)
TEST_VALUE(0x32, 0x50)
TEST_VALUE(0x7E, 0xFF)
void test_mpu9250_port_read_reg_reads(uint8_t addr, uint8_t val)
{
    nrf_drv_twi_tx_ExpectWithArrayAndReturn(
        &_twi, 1,
        MPU9250_I2C_ADDR,
        &addr, 1,
        1,
        true,

        NRF_SUCCESS
    );

    nrf_drv_twi_rx_ExpectAndReturn(
        &_twi,
        MPU9250_I2C_ADDR,
        NULL,
        1,

        NRF_SUCCESS
    );
    nrf_drv_twi_rx_IgnoreArg_p_data();
    nrf_drv_twi_rx_ReturnThruPtr_p_data(&val);

    uint8_t rval;
    TEST_ASSERT_EQUAL(ERROR_NONE, mpu9250_port_read_reg(&_port, addr, &rval));
    TEST_ASSERT_EQUAL_HEX8(val, rval);
}

TEST_VALUE(NRF_ERROR_BUSY)
TEST_VALUE(NRF_ERROR_INVALID_ADDR)
TEST_VALUE(NRF_ERROR_INTERNAL)
TEST_VALUE(NRF_ERROR_DRV_TWI_ERR_OVERRUN)
TEST_VALUE(NRF_ERROR_DRV_TWI_ERR_ANACK)
TEST_VALUE(NRF_ERROR_DRV_TWI_ERR_DNACK)
void test_mpu9250_port_read_reg_detects_tx_err(ret_code_t err)
{
    nrf_drv_twi_tx_IgnoreAndReturn(err);

    uint8_t rval;
    TEST_ASSERT_EQUAL(ERROR_COMM, mpu9250_port_read_reg(&_port, 0, &rval));
}

TEST_VALUE(NRF_ERROR_BUSY)
TEST_VALUE(NRF_ERROR_INVALID_ADDR)
TEST_VALUE(NRF_ERROR_INTERNAL)
TEST_VALUE(NRF_ERROR_DRV_TWI_ERR_OVERRUN)
TEST_VALUE(NRF_ERROR_DRV_TWI_ERR_ANACK)
TEST_VALUE(NRF_ERROR_DRV_TWI_ERR_DNACK)
void test_mpu9250_port_read_reg_detects_rx_err(ret_code_t err)
{
    nrf_drv_twi_tx_IgnoreAndReturn(NRF_SUCCESS);
    nrf_drv_twi_rx_IgnoreAndReturn(err);

    uint8_t rval;
    TEST_ASSERT_EQUAL(ERROR_COMM, mpu9250_port_read_reg(&_port, 0, &rval));
}

void test_mpu9250_port_write_reg_detects_invalid_handle(void)
{
    static mpu9250_port_t port;

    TEST_ASSERT_FAILS_ENSURE_ARG(_mpu9250_port_read_register_port, NULL);
    TEST_ASSERT_FAILS_ENSURE_ARG(_mpu9250_port_read_register_port, &port);
}

TEST_VALUE(MPU9250_REGISTER_COUNT)
TEST_VALUE(MPU9250_REGISTER_COUNT + 1)
TEST_VALUE(MPU9250_REGISTER_COUNT + 2)
TEST_VALUE(0xFF)
void test_mpu9250_port_read_reg_detects_invalid_address(uint8_t addr)
{
    TEST_ASSERT_FAILS_ENSURE_ARG(
        _mpu9250_port_read_register_addr,
        (void *) (uintptr_t) addr
    );
}

void test_mpu9250_port_read_reg_detects_invalid_value_ptr(void)
{
    TEST_ASSERT_FAILS_ENSURE_ARG(_mpu9250_port_read_register_value, NULL);
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

static void _mpu9250_port_read_register_port(void * port)
{
    uint8_t value;
    mpu9250_port_read_reg(port, 0, &value);
}

static void _mpu9250_port_read_register_addr(void * addr)
{
    uint8_t value;
    mpu9250_port_read_reg(&_port, (uint8_t) (uintptr_t) addr, &value);
}

static void _mpu9250_port_read_register_value(void * value)
{
    mpu9250_port_read_reg(&_port, 0, value);
}

/// @} defgroup MPU9250_PORT_TEST
/// @} addtogroup MPU9250_PORT
