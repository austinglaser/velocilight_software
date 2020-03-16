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

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */

static void _mpu9250_port_init_null_port(void);
static void _mpu9250_port_init_null_config(void);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */
/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_mpu9250_port_init_detects_null_port(void)
{
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_port_init_null_port);
}

void test_mpu9250_port_init_detects_null_config(void)
{
    TEST_ASSERT_FAILS_ENSURE(_mpu9250_port_init_null_config);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _mpu9250_port_init_null_port(void)
{
    mpu9250_port_config_t config;

    mpu9250_port_init(NULL, &config);
}

static void _mpu9250_port_init_null_config(void)
{
    mpu9250_port_t port;

    mpu9250_port_init(&port, NULL);
}

/** @} defgroup MPU9250_PORT_TEST */
/** @} addtogroup MPU9250_PORT */
