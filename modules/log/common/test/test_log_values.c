/**@file    test_log_values.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Logger Standard Values Test
 *
 * @addtogroup TEST_LOG_VALUES
 * @{
 *
 * Test list:
 *
 * [X] Type values are correct
 * [X] Subtype values are correct
 * [X] Flag values are correct
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"
#include "log.h"

#include "mock_log_memory.h"
#include "mock_log_serialize.h"
#include "mock_memory_pool.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */
/* --- TESTS ---------------------------------------------------------------- */

void test_type_values_are_standard(void)
{
    TEST_ASSERT_EQUAL_HEX8(0x80, TYPE_RESET);
    TEST_ASSERT_EQUAL_HEX8(0x81, TYPE_EXCEPTION);
    TEST_ASSERT_EQUAL_HEX8(0x82, TYPE_RUNTIME_ERROR);
    TEST_ASSERT_EQUAL_HEX8(0x83, TYPE_STATE_CHANGE);
}

void test_reset_subtypes_are_standard(void)
{
    TEST_ASSERT_EQUAL_HEX8(0x80, SUBTYPE_UNKNOWN_RESET);
    TEST_ASSERT_EQUAL_HEX8(0x81, SUBTYPE_POWER_RESET);
    TEST_ASSERT_EQUAL_HEX8(0x82, SUBTYPE_SOFTWARE_RESET);
    TEST_ASSERT_EQUAL_HEX8(0x83, SUBTYPE_WATCHDOG_RESET);
}

void test_exception_subtypes_are_standard(void)
{
    TEST_ASSERT_EQUAL_HEX8(0x80, SUBTYPE_UNKNOWN_EXCEPTION);
    TEST_ASSERT_EQUAL_HEX8(0x81, SUBTYPE_STACK_OVERFLOW_EXCEPTION);
    TEST_ASSERT_EQUAL_HEX8(0x82, SUBTYPE_HARD_FAULT_EXCEPTION);
    TEST_ASSERT_EQUAL_HEX8(0x83, SUBTYPE_BUS_FAULT_EXCEPTION);
    TEST_ASSERT_EQUAL_HEX8(0x84, SUBTYPE_USAGE_FAULT_EXCEPTION);
}

void test_runtime_error_subtypes_are_standard(void)
{
    TEST_ASSERT_EQUAL_HEX8(0x80, SUBTYPE_UNKNOWN_RUNTIME_ERROR);
    TEST_ASSERT_EQUAL_HEX8(0x81, SUBTYPE_INVALID_LOG_TYPE_RUNTIME_ERROR);
    TEST_ASSERT_EQUAL_HEX8(0x82, SUBTYPE_INVALID_LOG_SUBTYPE_RUNTIME_ERROR);
    TEST_ASSERT_EQUAL_HEX8(0x83, SUBTYPE_INVALID_ARGUMENT_RUNTIME_ERROR);
    TEST_ASSERT_EQUAL_HEX8(0x84, SUBTYPE_BUFFER_OVERFLOW_RUNTIME_ERROR);
    TEST_ASSERT_EQUAL_HEX8(0x85, SUBTYPE_MEMORY_ALLOCATION_RUNTIME_ERROR);
}

void test_flag_values_are_standard(void)
{
    TEST_ASSERT_EQUAL_HEX16(0x0000, LOG_NO_FLAGS);
    TEST_ASSERT_EQUAL_HEX16(0x8000, LOG_FLAG_PC);
    TEST_ASSERT_EQUAL_HEX16(0x4000, LOG_FLAG_SP);
    TEST_ASSERT_EQUAL_HEX16(0x2000, LOG_FLAG_SU);
    TEST_ASSERT_EQUAL_HEX16(0x1000, LOG_FLAG_DSC);
    TEST_ASSERT_EQUAL_HEX16(0x0800, LOG_FLAG_BIN);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_LOG_VALUES */
