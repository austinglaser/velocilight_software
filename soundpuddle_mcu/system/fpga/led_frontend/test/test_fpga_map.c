/**@file    test_fpga_map.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   FpgaMap Test Source
 *
 * @addtogroup FPGA_MAP
 * @{
 *
 * @defgroup FPGA_MAP_TEST FpgaMap Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* Test framework */
#include "unity.h"

/* Module under test */
#include "fpga_map.h"

/* Supporting modules */

/* Mocks, fakes, test support */
#include "ensure_support.h"
#include "mock_memory.h"

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
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */
/* --- PUBLIC TESTS -------------------------------------------------------- */

void test_fpga_registers_have_correct_offsets(void)
{
    TEST_ASSERT_EQUAL(0, offsetof(fpga_t, STAT));
    TEST_ASSERT_EQUAL(2, offsetof(fpga_t, CTRL));
    TEST_ASSERT_EQUAL(4, offsetof(fpga_t, DATA));
}

void test_fpga_get_stat_reads_stat(void)
{
    fpga_t fpga;

    fpga.STAT = 0;
    memory_barrier_data_Expect();
    TEST_ASSERT_EQUAL_UINT16(0, fpga_get_stat(&fpga));

    fpga.STAT = 32;
    memory_barrier_data_Expect();
    TEST_ASSERT_EQUAL_UINT16(32, fpga_get_stat(&fpga));

    fpga.STAT = UINT16_MAX;
    memory_barrier_data_Expect();
    TEST_ASSERT_EQUAL_UINT16(UINT16_MAX, fpga_get_stat(&fpga));
}

static void _fpga_get_stat_null_fpga(void)
{
    fpga_get_stat(NULL);
}

void test_fpga_get_stat_detects_null_handle(void)
{
    TEST_ASSERT_FAILS_ENSURE(_fpga_get_stat_null_fpga);
}

void test_fpga_set_ctrl_writes_ctrl(void)
{
    fpga_t fpga;

    fpga.CTRL = 0;
    memory_barrier_data_Expect();
    fpga_set_ctrl(&fpga, 1);
    TEST_ASSERT_EQUAL_UINT16(1, fpga.CTRL);

    fpga.CTRL = 0;
    memory_barrier_data_Expect();
    fpga_set_ctrl(&fpga, 9235);
    TEST_ASSERT_EQUAL_UINT16(9235, fpga.CTRL);

    fpga.CTRL = 0;
    memory_barrier_data_Expect();
    fpga_set_ctrl(&fpga, UINT16_MAX);
    TEST_ASSERT_EQUAL_UINT16(UINT16_MAX, fpga.CTRL);
}

static void _fpga_set_ctrl_null_handle(void)
{
    fpga_set_ctrl(NULL, 32);
}

void test_fpga_set_ctrl_detects_null_handle(void)
{
    TEST_ASSERT_FAILS_ENSURE(_fpga_set_ctrl_null_handle);
}

void test_fpga_set_data_writes_data(void)
{
    fpga_t fpga;

    fpga.DATA = 0;
    memory_barrier_data_Expect();
    fpga_set_data(&fpga, 1);
    TEST_ASSERT_EQUAL_UINT16(1, fpga.DATA);

    fpga.DATA = 0;
    memory_barrier_data_Expect();
    fpga_set_data(&fpga, 23255);
    TEST_ASSERT_EQUAL_UINT16(23255, fpga.DATA);

    fpga.DATA = 0;
    memory_barrier_data_Expect();
    fpga_set_data(&fpga, UINT16_MAX);
    TEST_ASSERT_EQUAL_UINT16(UINT16_MAX, fpga.DATA);
}

static void _fpga_set_data_null_handle(void)
{
    fpga_set_data(NULL, 32);
}

void test_fpga_set_data_detects_null_handle(void)
{
    TEST_ASSERT_FAILS_ENSURE(_fpga_set_data_null_handle);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

/** @} defgroup FPGA_MAP_TEST */
/** @} addtogroup FPGA_MAP */
