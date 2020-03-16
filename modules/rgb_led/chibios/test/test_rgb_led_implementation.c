/**
 * @file    test_rgb_led_implementation.c
 * @author  Krithik Chandrashekar <krithik@boulderes.com>
 * @brief   TestLed Source
 *
 * @addtogroup TEST_RGB_LED_IMPLEMENTATION
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"
#include "rgb_led.h"
#include "rgb_led_implementation.h"

#include "CException.h"

#include "ensure.h"
#include "ensure_c_exception.h"
#include "util.h"

#include "ch.h"
#include "hal.h"
#include "mock_pal.h"

#include <stdbool.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

#undef RGB_LED_R_LINE
#undef RGB_LED_G_LINE
#undef RGB_LED_B_LINE

#define RGB_LED_R_LINE 0x80000000
#define RGB_LED_B_LINE 0x81000000
#define RGB_LED_G_LINE 0x82000000

static rgb_led_config_t const config = {
    .r_line = RGB_LED_R_LINE,
    .g_line = RGB_LED_G_LINE,
    .b_line = RGB_LED_B_LINE,
};

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void test_rgb_led_implementation_pin_init_initializes_pins(void)
{
    palSetLineMode_Expect(RGB_LED_R_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode_Expect(RGB_LED_G_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode_Expect(RGB_LED_B_LINE, PAL_MODE_OUTPUT_PUSHPULL);

    rgb_led_implementation_pin_init(&config);
}

void test_rgb_led_implementation_pin_init_sanitizes_input(void)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        rgb_led_implementation_pin_init(NULL);
    } Catch (e) { }

    TEST_ASSERT_EQUAL(ENSURE_FAILED, e);
}

void test_rgb_led_implementation_update_writes_all_off(void)
{
    palWriteLine_Expect(RGB_LED_R_LINE, 0);
    palWriteLine_Expect(RGB_LED_G_LINE, 0);
    palWriteLine_Expect(RGB_LED_B_LINE, 0);

    rgb_led_implementation_update(&config, false, false, false);
}

void test_rgb_led_implementation_update_writes_all_on(void)
{
    palWriteLine_Expect(RGB_LED_R_LINE, 1);
    palWriteLine_Expect(RGB_LED_G_LINE, 1);
    palWriteLine_Expect(RGB_LED_B_LINE, 1);

    rgb_led_implementation_update(&config, true, true, true);
}

void test_rgb_led_implementation_update_writes_red(void)
{
    palWriteLine_Expect(RGB_LED_R_LINE, 1);
    palWriteLine_Expect(RGB_LED_G_LINE, 0);
    palWriteLine_Expect(RGB_LED_B_LINE, 0);

    rgb_led_implementation_update(&config, true, false, false);
}

void test_rgb_led_implementation_update_writes_green(void)
{
    palWriteLine_Expect(RGB_LED_R_LINE, 0);
    palWriteLine_Expect(RGB_LED_G_LINE, 1);
    palWriteLine_Expect(RGB_LED_B_LINE, 0);

    rgb_led_implementation_update(&config, false, true, false);
}

void test_rgb_led_implementation_update_writes_blue(void)
{
    palWriteLine_Expect(RGB_LED_R_LINE, 0);
    palWriteLine_Expect(RGB_LED_G_LINE, 0);
    palWriteLine_Expect(RGB_LED_B_LINE, 1);

    rgb_led_implementation_update(&config, false, false, true);
}

void test_rgb_led_implementation_update_sanitizes_input(void)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        rgb_led_implementation_update(NULL, true, false, true);
    } Catch (e) { }

    TEST_ASSERT_EQUAL(ENSURE_FAILED, e);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_BYTESWAP */