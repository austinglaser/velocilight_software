/**@file    test_rgb_led_implementation.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   RgbLedImplementation Test Source
 *
 * @addtogroup RGB_LED_IMPLEMENTATION
 * @{
 *
 * @defgroup RGB_LED_IMPLEMENTATION_TEST RgbLedImplementation Tests
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"
#include "rgb_led.h"
#include "mock_rgb_led_implementation.h"

#include "CException.h"

#include "ensure.h"
#include "ensure_c_exception.h"
#include "util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

static rgb_led_config_t config = {
};

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static rgb_led_t rgb_led;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void setUp(void)
{
    rgb_led_implementation_pin_init_Expect(&config);
    rgb_led_implementation_update_Expect(&config, 0, 0, 0);

    rgb_led_init(&rgb_led, &config);
}

/* --- PUBLIC TESTS --------------------------------------------------------- */

void test_rgb_led_init_pin_config(void)
{
    rgb_led_implementation_pin_init_Expect(&config);
    rgb_led_implementation_update_Expect(&config, 0, 0, 0);

    rgb_led_init(&rgb_led, &config);
}

void test_rgb_led_init_detects_bad_descriptor(void)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        rgb_led_init(NULL, &config);
    } Catch (e) { }

    TEST_ASSERT_EQUAL(ENSURE_FAILED, e);
}

void test_rgb_led_set_clears_all_for_black(void)
{
    rgb_led_implementation_update_Expect(&config, 0, 0, 0);

    rgb_led_set(&rgb_led, RGB_LED_COLOR_BLACK);
}

void test_rgb_led_set_sets_all_for_white(void)
{
    rgb_led_implementation_update_Expect(&config, 1, 1, 1);

    rgb_led_set(&rgb_led, RGB_LED_COLOR_WHITE);
}

void test_rgb_led_set_sets_red_for_red(void)
{
    rgb_led_implementation_update_Expect(&config, 1, 0, 0);

    rgb_led_set(&rgb_led, RGB_LED_COLOR_RED);
}

void test_rgb_led_set_sets_green_for_green(void)
{
    rgb_led_implementation_update_Expect(&config, 0, 1, 0);

    rgb_led_set(&rgb_led, RGB_LED_COLOR_GREEN);
}

void test_rgb_led_set_sets_blue_for_blue(void)
{
    rgb_led_implementation_update_Expect(&config, 0, 0, 1);

    rgb_led_set(&rgb_led, RGB_LED_COLOR_BLUE);
}

void test_rgb_led_set_sets_red_and_green_for_yellow(void)
{
    rgb_led_implementation_update_Expect(&config, 1, 1, 0);

    rgb_led_set(&rgb_led, RGB_LED_COLOR_YELLOW);
}

void test_rgb_led_set_sets_red_and_blue_for_violet(void)
{
    rgb_led_implementation_update_Expect(&config, 1, 0, 1);

    rgb_led_set(&rgb_led, RGB_LED_COLOR_VIOLET);
}

void test_rgb_led_set_sets_green_and_blue_for_cyan(void)
{
    rgb_led_implementation_update_Expect(&config, 0, 1, 1);

    rgb_led_set(&rgb_led, RGB_LED_COLOR_CYAN);
}

void test_rgb_led_set_detects_invalid_descriptor(void)
{
    CEXCEPTION_T e = CEXCEPTION_NONE;
    Try {
        rgb_led_set(NULL, RGB_LED_COLOR_BLACK);
    } Catch (e) { }

    TEST_ASSERT_EQUAL(ENSURE_FAILED, e);
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} defgroup RGB_LED_IMPLEMENTATION_TEST */
/** @} addtogroup RGB_LED_IMPLEMENTATION */
