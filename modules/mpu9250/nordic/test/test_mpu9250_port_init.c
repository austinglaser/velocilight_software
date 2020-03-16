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

// Supporting modules

// Mocks, fakes, test support
#include "ensure_support.h"
#include "mock_nrf_drv_twi.h"

// Source dependencies (present only to make Ceedling include the right
// objects)
#include "ensure_c_exception.h"
#include "unity_util.h"

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //
// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //

static void _mpu9250_port_init_port(void * port);
static void _mpu9250_port_init_config(void * config);

// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //
// --- PUBLIC TESTS -------------------------------------------------------- //

void test_mpu9250_port_init_detects_invalid_port(void)
{
    TEST_ASSERT_FAILS_ENSURE_ARG(_mpu9250_port_init_port, NULL);
}

void test_mpu9250_port_init_detects_invalidconfig(void)
{
    TEST_ASSERT_FAILS_ENSURE_ARG(_mpu9250_port_init_config, NULL);

    mpu9250_port_config_t null_twi = {
        .twi = NULL,
    };
    TEST_ASSERT_FAILS_ENSURE_ARG(_mpu9250_port_init_config, &null_twi);
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

static void _mpu9250_port_init_port(void * port)
{
    mpu9250_port_config_t config;

    mpu9250_port_init(port, &config);
}

static void _mpu9250_port_init_config(void * config)
{
    mpu9250_port_t port;

    mpu9250_port_init(&port, config);
}

/// @} defgroup MPU9250_PORT_TEST
/// @} addtogroup MPU9250_PORT
