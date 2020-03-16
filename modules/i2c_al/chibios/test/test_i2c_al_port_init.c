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

/** Call @ref i2c_al_init with a null handle */
static void _i2c_al_init_null_handle(void);

/** Call @ref i2c_al_init with a null config */
static void _i2c_al_init_null_config(void);

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
};

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */
/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_i2c_al_init_starts_driver(void)
{
    i2cStart_Expect(&i2c_hw_driver, &i2c_hw_config);

    TEST_ASSERT_EQUAL(ERROR_NONE, i2c_al_init(&i2c, &i2c_config));
}

void test_i2c_al_init_rejects_null_parameters(void)
{
    /* Ignoring i2cStart gives more descriptive failure messages */
    i2cStart_Ignore();

    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_init_null_handle,
                                     "should catch null i2c handle.");
    TEST_ASSERT_FAILS_ENSURE_MESSAGE(_i2c_al_init_null_config,
                                     "should catch null i2c config.");
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _i2c_al_init_null_handle(void)
{
    i2c_al_init(NULL, &i2c_config);
}

static void _i2c_al_init_null_config(void)
{
    i2c_al_init(&i2c, NULL);
}

/** @} defgroup I2C_AL_PORT_TEST */
/** @} addtogroup I2C_AL_PORT */
