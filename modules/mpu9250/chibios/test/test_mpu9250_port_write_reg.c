/**@file    test_mpu9250_port.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Mpu9250Port Test Source
 *
 * @addtogroup MPU9250_PORT
 * @{
 *
 * @defgroup MPU9250_PORT_TEST Mpu9250Port Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* Test framework */
#include "unity.h"

/* Module under test */
#include "mpu9250_port.h"

/* Supporting modules */
#include "hal.h"
#include "util.h"

/* Mocks, fakes, test support */
#include "ensure_support.h"
#include "mock_spi.h"

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

static void _mpu9250_port_write_reg_null_handle(void);
static void _mpu9250_port_write_reg_static_uninit_handle(void);
static void _mpu9250_port_write_reg_shared_addr(void);

static void _spiSelect_callback(SPIDriver * spip, int num_prev_calls);
static void _spiUnselect_callback(SPIDriver * spip, int num_prev_calls);
static void _spiSend_callback(SPIDriver * spip,
                              size_t n,
                              const void * txbuf,
                              int num_prev_calls);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

static SPIDriver _spid;
static bool _selected = false;
static uint8_t _txbuf[2];

static uint8_t _shared_addr;

static mpu9250_port_t _port;
static mpu9250_port_config_t _config = {
    .spid = &_spid,
};

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void setUp(void)
{
    _selected = false;

    mpu9250_port_init(&_port, &_config);

    spiSelect_StubWithCallback(_spiSelect_callback);
    spiUnselect_StubWithCallback(_spiUnselect_callback);
    spiSend_StubWithCallback(_spiSend_callback);
}

/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_mpu9250_write_reg_sends_addr(void)
{
    _txbuf[0] = 0x00;
    _txbuf[1] = 0x00;

    err_t err = mpu9250_port_write_reg(&_port, 0x30, 0xAB);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX8(0x30, _txbuf[0]);

    _txbuf[0] = 0x00;
    _txbuf[1] = 0x00;

    err = mpu9250_port_write_reg(&_port, 0x01, 0x73);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX8(0x01, _txbuf[0]);
}

void test_mpu9250_write_reg_sends_value(void)
{
    _txbuf[0] = 0x00;
    _txbuf[1] = 0x00;

    err_t err = mpu9250_port_write_reg(&_port, 0x30, 0xAB);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX8(0xAB, _txbuf[1]);

    _txbuf[0] = 0x00;
    _txbuf[1] = 0x00;

    err = mpu9250_port_write_reg(&_port, 0x01, 0x73);

    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL_HEX8(0x73, _txbuf[1]);
}

void test_mpu9250_write_reg_detects_invalid_port(void)
{
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_port_write_reg_null_handle);
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_port_write_reg_static_uninit_handle);
}

void test_mpu9250_write_reg_detectsi_invalid_address(void)
{
    static const uint8_t bad_addrs[] = {
        0x80,
        0xFF,
        0xBC,
    };

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(bad_addrs); i++) {
        _shared_addr = bad_addrs[i];
        TEST_ASSERT_FAILS_ENSURE(_mpu9250_port_write_reg_shared_addr);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _mpu9250_port_write_reg_null_handle(void)
{
    mpu9250_port_write_reg(NULL, 0x00, 0x00);
}

static void _mpu9250_port_write_reg_static_uninit_handle(void)
{
    static const mpu9250_port_t port;
    mpu9250_port_write_reg(&port, 0x00, 0x00);
}

static void _mpu9250_port_write_reg_shared_addr(void)
{
    mpu9250_port_write_reg(&_port, _shared_addr, 0x00);
}

static void _spiSelect_callback(SPIDriver * spip, int num_prev_calls)
{
    UNUSED_PARAMETER(num_prev_calls);

    TEST_ASSERT_EQUAL_PTR(spip, &_spid);

    _selected = true;
}

static void _spiUnselect_callback(SPIDriver * spip, int num_prev_calls)
{
    UNUSED_PARAMETER(num_prev_calls);

    TEST_ASSERT_EQUAL_PTR(spip, &_spid);

    _selected = false;
}

static void _spiSend_callback(SPIDriver * spip,
                              size_t n,
                              const void * txbuf,
                              int num_prev_calls)
{
    UNUSED_PARAMETER(num_prev_calls);

    TEST_ASSERT_EQUAL_PTR(spip, &_spid);

    TEST_ASSERT_MESSAGE(_selected, "spiSend on unselected bus");

    TEST_ASSERT_NOT_NULL(txbuf);

    memcpy(_txbuf, txbuf, n);
}

/** @} defgroup MPU9250_PORT_TEST */
/** @} addtogroup MPU9250_PORT */
