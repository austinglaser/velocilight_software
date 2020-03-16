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
#include "rgb_led_implementation.h"

#include "CException.h"

#include "ensure.h"
#include "ensure_c_exception.h"

#include "mock_nrf_gpio.h"

#include "util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

#define RGB_LED_R_PIN   12
#define RGB_LED_G_PIN   13
#define RGB_LED_B_PIN   14

static rgb_led_config_t config = {
    .r_pin_number = RGB_LED_R_PIN,
    .g_pin_number = RGB_LED_G_PIN,
    .b_pin_number = RGB_LED_B_PIN,
};

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */
/* --- PUBLIC TESTS --------------------------------------------------------- */

void test_rgb_led_implementation_pin_init_initializes_pins(void)
{
    nrf_gpio_cfg_output_Expect(RGB_LED_R_PIN);
    nrf_gpio_cfg_output_Expect(RGB_LED_G_PIN);
    nrf_gpio_cfg_output_Expect(RGB_LED_B_PIN);

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
    nrf_gpio_pin_write_Expect(RGB_LED_R_PIN, 0);
    nrf_gpio_pin_write_Expect(RGB_LED_G_PIN, 0);
    nrf_gpio_pin_write_Expect(RGB_LED_B_PIN, 0);

    rgb_led_implementation_update(&config, false, false, false);
}

void test_rgb_led_implementation_update_writes_all_on(void)
{
    nrf_gpio_pin_write_Expect(RGB_LED_R_PIN, 1);
    nrf_gpio_pin_write_Expect(RGB_LED_G_PIN, 1);
    nrf_gpio_pin_write_Expect(RGB_LED_B_PIN, 1);

    rgb_led_implementation_update(&config, true, true, true);
}

void test_rgb_led_implementation_update_writes_red(void)
{
    nrf_gpio_pin_write_Expect(RGB_LED_R_PIN, 1);
    nrf_gpio_pin_write_Expect(RGB_LED_G_PIN, 0);
    nrf_gpio_pin_write_Expect(RGB_LED_B_PIN, 0);

    rgb_led_implementation_update(&config, true, false, false);
}

void test_rgb_led_implementation_update_writes_green(void)
{
    nrf_gpio_pin_write_Expect(RGB_LED_R_PIN, 0);
    nrf_gpio_pin_write_Expect(RGB_LED_G_PIN, 1);
    nrf_gpio_pin_write_Expect(RGB_LED_B_PIN, 0);

    rgb_led_implementation_update(&config, false, true, false);
}

void test_rgb_led_implementation_update_writes_blue(void)
{
    nrf_gpio_pin_write_Expect(RGB_LED_R_PIN, 0);
    nrf_gpio_pin_write_Expect(RGB_LED_G_PIN, 0);
    nrf_gpio_pin_write_Expect(RGB_LED_B_PIN, 1);

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

/** @} defgroup RGB_LED_IMPLEMENTATION_TEST */
/** @} addtogroup RGB_LED_IMPLEMENTATION */
