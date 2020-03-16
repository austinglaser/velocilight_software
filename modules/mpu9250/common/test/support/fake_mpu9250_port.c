/**@file    fake_mpu9250_port.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Mpu9250PortFake Source
 *
 * @addtogroup MPU9250_PORT_FAKE
 * @{
 *
 * @defgroup MPU9250_PORT_FAKE_PRIVATE Mpu9250PortFake Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "fake_mpu9250_port.h"

/* Supporting modules */
#include "ensure.h"
#include "error.h"
#include "mpu9250_registers.h"
#include "util.h"

/* Third-party headers */
#include "unity.h"
#include "mock_mpu9250_port.h"

/* Standard headers */
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* --- PRIVATE CONSTANTS --------------------------------------------------- */
/* --- PRIVATE DATATYPES --------------------------------------------------- */

/** A fake MPU9250 scratch area */
typedef struct {
    bool reset;             /**< Whether reset */
    uint8_t registers[MPU9250_REGISTER_COUNT]; /**< Fake register bank */

    /** The config the port was initialized with */
    mpu9250_port_config_t const * config;
} fake_mpu9250_guts_t;

/** Overlay struct for mpu9250_port_t */
typedef struct {
    fake_mpu9250_guts_t * guts; /**< Guts of the implementation */
} fake_mpu9250_port_t;

static_assert(sizeof(fake_mpu9250_port_t) <= sizeof(mpu9250_port_t),
              "mpu9250_port_t not big enough for fake."
              " Consider adding a dummy size_t or void * field.");

/* --- PRIVATE MACROS ------------------------------------------------------ */
/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */

/** Get the guts of a fake from a real port
 *
 * @param[in] port:     Port to get the guts for
 *
 * @return      A mutable pointer to the guts of the fake implementation
 */
static fake_mpu9250_guts_t * _get_guts(mpu9250_port_t const * port);

/** Reset the register values in the fake
 *
 * After this call, all registers are at their datasheet reset value. That is,
 * all are 0x00, except for WHO_AM_I (which is 0x71) and PWR_MGMT_1 (which is
 * 0x01).
 *
 * @param[out] fake:    Fake register bank to reset
 */
static void _fake_mpu9250_port_reset_registers(fake_mpu9250_guts_t * fake);

/** Callback for @ref mpu9250_port_init
 *
 * Validates that its arguments are non-null
 *
 * Simply marks @p port as initialized
 *
 * @param[out] port:        Fake port to "initialize"
 * @param[in] config:       A dummy config
 * @param num_prev_calls:   Unused
 */
static void _fake_mpu9250_port_init(mpu9250_port_t * port,
                                    mpu9250_port_config_t const * config,
                                    int num_prev_calls);

/** Callback for @ref mpu9250_port_read_reg
 *
 * Validates that @p port has been initialized
 *
 * Returns the value at @p addr in the fake register bank
 *
 * @param[in] port:         Fake port to read from
 * @param[in] addr:         Register address to use
 * @param[out] value:       To return register value
 *
 * @return      ERROR_NONE
 */
static err_t _fake_mpu9250_port_read_reg(mpu9250_port_t const * port,
                                         uint8_t addr,
                                         uint8_t * value,
                                         int num_prev_calls);

/** Callback for @ref mpu9250_port_write_reg
 *
 * Validates that @p port has been initialized
 *
 * Sets @p addr in the fake register bank to @p value
 *
 * @param[in] port:         Fake port to write to
 * @param[in] addr:         Register address to use
 * @param[in] value:        Value to set
 *
 * @return      ERROR_NONE
 */
static err_t _fake_mpu9250_port_write_reg(mpu9250_port_t const * port,
                                          uint8_t addr,
                                          uint8_t value,
                                          int num_prev_calls);

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void fake_mpu9250_port_setup(mpu9250_port_t * port)
{
    ensure(port != NULL);

    fake_mpu9250_port_teardown(port);

    fake_mpu9250_port_t * fport = (fake_mpu9250_port_t *) port;

    fport->guts = malloc(sizeof(*fport->guts));
    ensure(fport->guts != NULL);

    _fake_mpu9250_port_reset_registers(fport->guts);

    fport->guts->reset       = false;
    fport->guts->config      = NULL;

    mpu9250_port_init_StubWithCallback(_fake_mpu9250_port_init);
    mpu9250_port_read_reg_StubWithCallback(_fake_mpu9250_port_read_reg);
    mpu9250_port_write_reg_StubWithCallback(_fake_mpu9250_port_write_reg);
}

void fake_mpu9250_port_teardown(mpu9250_port_t * port)
{
    fake_mpu9250_port_t * fport = (fake_mpu9250_port_t *) port;
    if (fport->guts != NULL) {
        free(fport->guts);
        fport->guts = NULL;
    }
}

bool fake_mpu9250_port_was_initialized(mpu9250_port_t const * port)
{
    ensure(port != NULL);

    fake_mpu9250_guts_t * guts = _get_guts(port);

    return guts->config != NULL;
}

bool fake_mpu9250_port_was_reset(mpu9250_port_t const * port)
{
    ensure(port != NULL);

    fake_mpu9250_guts_t * guts = _get_guts(port);

    return guts->reset;
}

mpu9250_port_config_t const *
fake_mpu9250_port_config(mpu9250_port_t const * port)
{
    fake_mpu9250_guts_t * guts = _get_guts(port);

    return guts->config;
}

uint8_t fake_mpu9250_port_get_reg(mpu9250_port_t const * port, uint8_t addr)
{
    ensure(port != NULL);

    fake_mpu9250_guts_t * guts = _get_guts(port);

    return guts->registers[addr];
}

void fake_mpu9250_port_set_reg(mpu9250_port_t const * port,
                               uint8_t addr,
                               uint8_t value)
{
    ensure(port != NULL);

    fake_mpu9250_guts_t * guts = _get_guts(port);

    guts->registers[addr] = value;
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static fake_mpu9250_guts_t * _get_guts(mpu9250_port_t const * port)
{
    fake_mpu9250_port_t const * fport = (fake_mpu9250_port_t const *) port;

    return fport->guts;
}

static void _fake_mpu9250_port_reset_registers(fake_mpu9250_guts_t * guts)
{
    memset(guts->registers, 0, sizeof(guts->registers));
    guts->registers[MPU9250_PWR_MGMT_1] = 0x01;
    guts->registers[MPU9250_WHO_AM_I]   = MPU9250_WHO_AM_I_VALUE;
}

static void _fake_mpu9250_port_init(mpu9250_port_t * port,
                                    mpu9250_port_config_t const * config,
                                    int num_prev_calls)
{
    UNUSED_PARAMETER(num_prev_calls);

    TEST_ASSERT_NOT_NULL(port);
    TEST_ASSERT_NOT_NULL(config);

    fake_mpu9250_guts_t * guts = _get_guts(port);

    TEST_ASSERT_NOT_NULL_MESSAGE(guts,
                                 "Internal test error: fake not set up");

    guts->config = config;
}

static err_t _fake_mpu9250_port_read_reg(mpu9250_port_t const * port,
                                         uint8_t addr,
                                         uint8_t * value,
                                         int num_prev_calls)
{
    UNUSED_PARAMETER(num_prev_calls);

    TEST_ASSERT_NOT_NULL(port);

    fake_mpu9250_guts_t * guts = _get_guts(port);

    TEST_ASSERT_NOT_NULL_MESSAGE(guts, "Internal test error: fake not set up");

    TEST_ASSERT_NOT_NULL_MESSAGE(guts->config,
                                 "Read reg before port initialization");

    TEST_ASSERT_MESSAGE(addr < MPU9250_REGISTER_COUNT,
                        "Read register out of range");
    TEST_ASSERT_NOT_NULL(value);

    *value = guts->registers[addr];

    return ERROR_NONE;
}

static err_t _fake_mpu9250_port_write_reg(mpu9250_port_t const * port,
                                          uint8_t addr,
                                          uint8_t value,
                                          int num_prev_calls)
{
    UNUSED_PARAMETER(num_prev_calls);

    TEST_ASSERT_NOT_NULL(port);

    fake_mpu9250_guts_t * guts = _get_guts(port);

    TEST_ASSERT_NOT_NULL_MESSAGE(guts, "Internal test error: fake not set up");

    TEST_ASSERT_NOT_NULL_MESSAGE(guts->config,
                                 "Write reg before port initialization");

    TEST_ASSERT_MESSAGE(addr < MPU9250_REGISTER_COUNT,
                        "Write register out of range");

    if ((addr == MPU9250_PWR_MGMT_1) && (value & MPU9250_PWR_MGMT_1_H_RESET)) {
        _fake_mpu9250_port_reset_registers(guts);
        guts->reset = true;
    } else {
        guts->registers[addr] = value;
    }

    return ERROR_NONE;
}

/** @} defgroup MPU9250_PORT_FAKE_PRIVATE */
/** @} addtogroup MPU9250_PORT_FAKE */
