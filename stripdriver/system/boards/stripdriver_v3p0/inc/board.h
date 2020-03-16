/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*
 * Setup for STMicroelectronics STM32F4-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_STM32F4_DISCOVERY
#define BOARD_NAME                  "StripDriver v3.0"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                12000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F405xx

/*
 * IO pins assignments.
 */
#define GPIOA_PWR_INT               0U
#define GPIOA_5V_SENSE              1U
#define GPIOA_PWR_KILL              2U
#define GPIOA_5V_EN                 3U
#define GPIOA_AUX_ADC               4U
#define GPIOA_MIC_ADC               5U
#define GPIOA_PIN6                  6U
#define GPIOA_PIN7                  7U
#define GPIOA_STATUS_LED            8U
#define GPIOA_ESP32_RX              9U
#define GPIOA_ESP32_TX              10U
#define GPIOA_USB_DM                11U
#define GPIOA_USB_DP                12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_IMU_FSYNC             0U
#define GPIOB_ESP32_RESET           1U
#define GPIOB_ESP32_AUX             2U
#define GPIOB_LED_SCK               3U
#define GPIOB_PIN4                  4U
#define GPIOB_LED_MOSI              5U
#define GPIOB_SCL                   6U
#define GPIOB_SDA                   7U
#define GPIOB_CAN_RX                8U
#define GPIOB_CAN_TX                9U
#define GPIOB_PIN10                 10U
#define GPIOB_PIN11                 11U
#define GPIOB_ESP32_SPICSO_CS       12U
#define GPIOB_ESP32_SPICLK_SCK      13U
#define GPIOB_ESP32_SPIQ_MISO       14U
#define GPIOB_ESP32_SPID_MOSI       15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_CAN_S                 3U
#define GPIOC_IMU_INT               4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_SD_DATA0              8U
#define GPIOC_SD_DATA1              9U
#define GPIOC_SD_DATA2              10U
#define GPIOC_SD_DATA3              11U
#define GPIOC_SD_CLK                12U
#define GPIOC_PIN13                 13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_SD_CMD                2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.
 */

/* Power */
#define LINE_PWR_INT                PAL_LINE(GPIOA, 0U)
#define LINE_5V_SENSE               PAL_LINE(GPIOA, 1U)
#define LINE_PWR_KILL               PAL_LINE(GPIOA, 2U)
#define LINE_5V_EN                  PAL_LINE(GPIOA, 3U)

/* Oscillators */
#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)
#define LINE_OSC32_IN               PAL_LINE(GPIOC, 14U)
#define LINE_OSC32_OUT              PAL_LINE(GPIOC, 15U)

/* ADC */
#define LINE_AUX_ADC                PAL_LINE(GPIOA, 4U)
#define LINE_MIC_ADC                PAL_LINE(GPIOA, 5U)

/* LED */
#define LINE_STATUS_LED             PAL_LINE(GPIOA, 8U)
#define LINE_LED_SCK                PAL_LINE(GPIOB, 3U)
#define LINE_LED_MOSI               PAL_LINE(GPIOB, 5U)

/* USB */
#define LINE_USB_DM                 PAL_LINE(GPIOA, 10U)
#define LINE_USB_DP                 PAL_LINE(GPIOA, 11U)

/* IMU */
#define LINE_IMU_FSYNC              PAL_LINE(GPIOB, 0U)
#define LINE_IMU_INT                PAL_LINE(GPIOC, 4U)
#define LINE_SCL                    PAL_LINE(GPIOB, 6U)
#define LINE_SDA                    PAL_LINE(GPIOB, 7U)

/* CAN */
#define LINE_CAN_RX                 PAL_LINE(GPIOB, 8U)
#define LINE_CAN_TX                 PAL_LINE(GPIOB, 9U)
#define LINE_CAN_S                  PAL_LINE(GPIOC, 3U)

/* SD card */
#define LINE_SD_DATA0               PAL_LINE(GPIOC, 8U)
#define LINE_SD_DATA1               PAL_LINE(GPIOC, 9U)
#define LINE_SD_DATA2               PAL_LINE(GPIOC, 10U)
#define LINE_SD_DATA3               PAL_LINE(GPIOC, 11U)
#define LINE_SD_CLK                 PAL_LINE(GPIOC, 12U)
#define LINE_SD_CMD                 PAL_LINE(GPIOD, 2U)

/* ESP32
 *
 * Note: RX and TX are from perspective of ESP32 *
 *
 * Note: Some ESP signals (strapping etc.) are muxed onto other signals.
 * TODO: Add a list, maybe alternate defs
 */
#define LINE_ESP32_RX               PAL_LINE(GPIOA, 8U)
#define LINE_ESP32_TX               PAL_LINE(GPIOA, 9U)

#define LINE_ESP32_SPICSO_CS        PAL_LINE(GPIOB, 12U)
#define LINE_ESP32_SPICLCK_SCK      PAL_LINE(GPIOB, 13U)
#define LINE_ESP32_SPIQ_MISO        PAL_LINE(GPIOB, 14U)
#define LINE_ESP32_SPID_MOSI        PAL_LINE(GPIOB, 15U)

#define LINE_ESP32_RESET            PAL_LINE(GPIOB, 1U)

#define LINE_ESP32_AUX              PAL_LINE(GPIOB, 2U)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - PWR_INT                   (input floating).
 * PA1  - 5V_SENSE                  (input analog).
 * PA2  - PWR_KILL                  (input analog).
 * PA3  - 5V_EN                     (output pushpull, low).
 * PA4  - AUX_ADC                   (input analog).
 * PA5  - MIC_ADC                   (input analog).
 * PA6  - PIN6                      (input pullup).
 * PA7  - PIN6                      (input pullup).
 * PA8  - STATUS_LED                (output pushpull, low).
 * PA9  - ESP32_RX                  (alternate 7).
 * PA10 - ESP32_TX                  (alternate 7).
 * PA11 - USB_DM                    (alternate 10).
 * PA12 - USB_DP                    (alternate 10).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - PIN15                     (input pullup).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_PWR_INT) |        \
                                     PIN_MODE_INPUT(GPIOA_5V_SENSE) |       \
                                     PIN_MODE_INPUT(GPIOA_PWR_KILL) |       \
                                     PIN_MODE_OUTPUT(GPIOA_5V_EN) |         \
                                     PIN_MODE_INPUT(GPIOA_AUX_ADC) |        \
                                     PIN_MODE_INPUT(GPIOA_MIC_ADC) |        \
                                     PIN_MODE_INPUT(GPIOA_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN7) |           \
                                     PIN_MODE_OUTPUT(GPIOA_STATUS_LED) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_ESP32_RX) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_ESP32_TX) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_DM) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_DP) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_PIN15))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PWR_INT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_5V_SENSE) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PWR_KILL) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_5V_EN) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_AUX_ADC) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MIC_ADC) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_STATUS_LED) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ESP32_RX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ESP32_TX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_DM) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_DP) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_PWR_INT) |       \
                                     PIN_OSPEED_HIGH(GPIOA_5V_SENSE) |      \
                                     PIN_OSPEED_HIGH(GPIOA_PWR_KILL) |      \
                                     PIN_OSPEED_HIGH(GPIOA_5V_EN) |         \
                                     PIN_OSPEED_HIGH(GPIOA_AUX_ADC) |       \
                                     PIN_OSPEED_HIGH(GPIOA_MIC_ADC) |       \
                                     PIN_OSPEED_HIGH(GPIOA_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOA_STATUS_LED) |    \
                                     PIN_OSPEED_HIGH(GPIOA_ESP32_RX) |      \
                                     PIN_OSPEED_HIGH(GPIOA_ESP32_TX) |      \
                                     PIN_OSPEED_HIGH(GPIOA_USB_DM) |        \
                                     PIN_OSPEED_HIGH(GPIOA_USB_DP) |        \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_PWR_INT) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_5V_SENSE) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_PWR_KILL) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_5V_EN) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_AUX_ADC) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_MIC_ADC) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_STATUS_LED) | \
                                     PIN_PUPDR_FLOATING(GPIOA_ESP32_RX) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_ESP32_TX) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DM) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DP) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_SWDIO) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN15))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_PWR_INT) |          \
                                     PIN_ODR_HIGH(GPIOA_5V_SENSE) |         \
                                     PIN_ODR_HIGH(GPIOA_PWR_KILL) |         \
                                     PIN_ODR_LOW(GPIOA_5V_EN) |             \
                                     PIN_ODR_HIGH(GPIOA_AUX_ADC) |          \
                                     PIN_ODR_HIGH(GPIOA_MIC_ADC) |          \
                                     PIN_ODR_HIGH(GPIOA_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN7) |             \
                                     PIN_ODR_LOW(GPIOA_STATUS_LED) |        \
                                     PIN_ODR_HIGH(GPIOA_ESP32_RX) |         \
                                     PIN_ODR_HIGH(GPIOA_ESP32_TX) |         \
                                     PIN_ODR_HIGH(GPIOA_USB_DM) |           \
                                     PIN_ODR_HIGH(GPIOA_USB_DP) |           \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PWR_INT, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_5V_SENSE, 0U) |      \
                                     PIN_AFIO_AF(GPIOA_PWR_KILL, 0U) |      \
                                     PIN_AFIO_AF(GPIOA_5V_EN, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_AUX_ADC, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_MIC_ADC, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN7, 0U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_STATUS_LED, 0U) |    \
                                     PIN_AFIO_AF(GPIOA_ESP32_RX, 7U) |      \
                                     PIN_AFIO_AF(GPIOA_ESP32_TX, 7U) |      \
                                     PIN_AFIO_AF(GPIOA_USB_DM, 10U) |       \
                                     PIN_AFIO_AF(GPIOA_USB_DP, 10U) |       \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_PIN15, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - IMU_FSYNC                 (input floating).
 * PB1  - ESP32_RESET               (input floating).
 * PB2  - ESP32_AUX                 (input floating).
 * PB3  - LED_SCK                   (alternate 5).
 * PB4  - PIN4                      (input pullup).
 * PB5  - LED_MOSI                  (alternate 5).
 * PB6  - SCL                       (alternate 4).
 * PB7  - SDA                       (alternate 4).
 * PB8  - CAN_RX                    (alternate 9).
 * PB9  - CAN_TX                    (alternate 9).
 * PB10 - PIN10                     (input pullup).
 * PB11 - PIN11                     (input pullup).
 * PB12 - ESP32_SPICSO_CS           (input pullup).
 * PB13 - ESP32_SPICLK_SCK          (input floating).
 * PB14 - ESP32_SPIQ_MISO           (input pullup).
 * PB15 - ESP32_SPID_MOSI           (input pullup).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_IMU_FSYNC) |            \
                                     PIN_MODE_INPUT(GPIOB_ESP32_RESET) |          \
                                     PIN_MODE_INPUT(GPIOB_ESP32_AUX) |            \
                                     PIN_MODE_ALTERNATE(GPIOB_LED_SCK) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |                 \
                                     PIN_MODE_ALTERNATE(GPIOB_LED_MOSI) |         \
                                     PIN_MODE_ALTERNATE(GPIOB_SCL) |              \
                                     PIN_MODE_ALTERNATE(GPIOB_SDA) |              \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN_RX) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN_TX) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN10) |                \
                                     PIN_MODE_INPUT(GPIOB_PIN11) |                \
                                     PIN_MODE_INPUT(GPIOB_ESP32_SPICSO_CS) |      \
                                     PIN_MODE_INPUT(GPIOB_ESP32_SPICLK_SCK) |     \
                                     PIN_MODE_INPUT(GPIOB_ESP32_SPIQ_MISO) |      \
                                     PIN_MODE_INPUT(GPIOB_ESP32_SPID_MOSI))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_IMU_FSYNC) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ESP32_RESET) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ESP32_AUX) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED_SCK) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |             \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED_MOSI) |         \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_SCL) |             \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_SDA) |             \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN_RX) |           \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN_TX) |           \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN10) |            \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN11) |            \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ESP32_SPICSO_CS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ESP32_SPICLK_SCK) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ESP32_SPIQ_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ESP32_SPID_MOSI))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_IMU_FSYNC) |           \
                                     PIN_OSPEED_HIGH(GPIOB_ESP32_RESET) |         \
                                     PIN_OSPEED_HIGH(GPIOB_ESP32_AUX) |           \
                                     PIN_OSPEED_HIGH(GPIOB_LED_SCK) |             \
                                     PIN_OSPEED_HIGH(GPIOB_PIN4) |                \
                                     PIN_OSPEED_HIGH(GPIOB_LED_MOSI) |            \
                                     PIN_OSPEED_HIGH(GPIOB_SCL) |                 \
                                     PIN_OSPEED_HIGH(GPIOB_SDA) |                 \
                                     PIN_OSPEED_HIGH(GPIOB_CAN_RX) |              \
                                     PIN_OSPEED_HIGH(GPIOB_CAN_TX) |              \
                                     PIN_OSPEED_HIGH(GPIOB_PIN10) |               \
                                     PIN_OSPEED_HIGH(GPIOB_PIN11) |               \
                                     PIN_OSPEED_HIGH(GPIOB_ESP32_SPICSO_CS) |     \
                                     PIN_OSPEED_HIGH(GPIOB_ESP32_SPICLK_SCK) |    \
                                     PIN_OSPEED_HIGH(GPIOB_ESP32_SPIQ_MISO) |     \
                                     PIN_OSPEED_HIGH(GPIOB_ESP32_SPID_MOSI))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_IMU_FSYNC) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_ESP32_RESET) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_ESP32_AUX) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_LED_SCK) |          \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN4) |               \
                                     PIN_PUPDR_FLOATING(GPIOB_LED_MOSI) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_SCL) |              \
                                     PIN_PUPDR_FLOATING(GPIOB_SDA) |              \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN_RX) |           \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN_TX) |           \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN10) |              \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN11) |              \
                                     PIN_PUPDR_PULLUP(GPIOB_ESP32_SPICSO_CS) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_ESP32_SPICLK_SCK) | \
                                     PIN_PUPDR_PULLUP(GPIOB_ESP32_SPIQ_MISO) |    \
                                     PIN_PUPDR_PULLUP(GPIOB_ESP32_SPID_MOSI))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_IMU_FSYNC) |              \
                                     PIN_ODR_HIGH(GPIOB_ESP32_RESET) |            \
                                     PIN_ODR_HIGH(GPIOB_ESP32_AUX) |              \
                                     PIN_ODR_HIGH(GPIOB_LED_SCK) |                \
                                     PIN_ODR_HIGH(GPIOB_PIN4) |                   \
                                     PIN_ODR_HIGH(GPIOB_LED_MOSI) |               \
                                     PIN_ODR_HIGH(GPIOB_SCL) |                    \
                                     PIN_ODR_HIGH(GPIOB_SDA) |                    \
                                     PIN_ODR_HIGH(GPIOB_CAN_RX) |                 \
                                     PIN_ODR_HIGH(GPIOB_CAN_TX) |                 \
                                     PIN_ODR_HIGH(GPIOB_PIN10) |                  \
                                     PIN_ODR_HIGH(GPIOB_PIN11) |                  \
                                     PIN_ODR_HIGH(GPIOB_ESP32_SPICSO_CS) |        \
                                     PIN_ODR_HIGH(GPIOB_ESP32_SPICLK_SCK) |       \
                                     PIN_ODR_HIGH(GPIOB_ESP32_SPIQ_MISO) |        \
                                     PIN_ODR_HIGH(GPIOB_ESP32_SPID_MOSI))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_IMU_FSYNC, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_ESP32_RESET, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_ESP32_AUX, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_LED_SCK, 5U) |             \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0U) |                \
                                     PIN_AFIO_AF(GPIOB_LED_MOSI, 4U) |            \
                                     PIN_AFIO_AF(GPIOB_SCL, 4U) |                 \
                                     PIN_AFIO_AF(GPIOB_SDA, 4U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_CAN_RX, 9U) |              \
                                     PIN_AFIO_AF(GPIOB_CAN_TX, 9U) |              \
                                     PIN_AFIO_AF(GPIOB_PIN10, 0U) |               \
                                     PIN_AFIO_AF(GPIOB_PIN11, 0U) |               \
                                     PIN_AFIO_AF(GPIOB_ESP32_SPICSO_CS, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_ESP32_SPICLK_SCK, 0U) |    \
                                     PIN_AFIO_AF(GPIOB_ESP32_SPIQ_MISO, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_ESP32_SPID_MOSI, 0U))

/*
 * GPIOC setup:
 *
 * PC0  - PIN0                      (input pullup).
 * PC1  - PIN1                      (input pullup).
 * PC2  - PIN2                      (input pullup).
 * PC3  - CAN_S                     (output pushpull, high).
 * PC4  - IMU_INT                   (input floating).
 * PC5  - PIN5                      (input pullup).
 * PC6  - PIN6                      (input pullup).
 * PC7  - PIN7                      (input pullup).
 * PC8  - SD_DATA0                  (alternate 12).
 * PC9  - SD_DATA1                  (alternate 12).
 * PC10 - SD_DATA2                  (alternate 12).
 * PC11 - SD_DATA3                  (alternate 12).
 * PC12 - SD_CLK                    (alternate 12).
 * PC13 - PIN13                     (input pullup).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_PIN0) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |         \
                                     PIN_MODE_OUTPUT(GPIOC_CAN_S) |       \
                                     PIN_MODE_INPUT(GPIOC_IMU_INT) |      \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |         \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_DATA0) | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_DATA1) | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_DATA2) | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_DATA3) | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_CLK) |   \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |        \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |     \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_CAN_S) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_IMU_INT) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_DATA0) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_DATA1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_DATA2) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_DATA3) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_CLK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_PIN0) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN1) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN2) |        \
                                     PIN_OSPEED_HIGH(GPIOC_CAN_S) |       \
                                     PIN_OSPEED_HIGH(GPIOC_IMU_INT) |     \
                                     PIN_OSPEED_HIGH(GPIOC_PIN5) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN6) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN7) |        \
                                     PIN_OSPEED_HIGH(GPIOC_SD_DATA0) |    \
                                     PIN_OSPEED_HIGH(GPIOC_SD_DATA1) |    \
                                     PIN_OSPEED_HIGH(GPIOC_SD_DATA2) |    \
                                     PIN_OSPEED_HIGH(GPIOC_SD_DATA3) |    \
                                     PIN_OSPEED_HIGH(GPIOC_SD_CLK) |      \
                                     PIN_OSPEED_HIGH(GPIOC_PIN13) |       \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |    \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_PIN0) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_CAN_S) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_IMU_INT) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN5) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN6) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_DATA0) | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_DATA1) | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_DATA2) | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_DATA3) | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_CLK) |   \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) | \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_PIN0) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN2) |           \
                                     PIN_ODR_HIGH(GPIOC_CAN_S) |          \
                                     PIN_ODR_HIGH(GPIOC_IMU_INT) |        \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN7) |           \
                                     PIN_ODR_HIGH(GPIOC_SD_DATA0) |       \
                                     PIN_ODR_HIGH(GPIOC_SD_DATA1) |       \
                                     PIN_ODR_HIGH(GPIOC_SD_DATA2) |       \
                                     PIN_ODR_HIGH(GPIOC_SD_DATA3) |       \
                                     PIN_ODR_HIGH(GPIOC_SD_CLK) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |          \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |       \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_CAN_S, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_IMU_INT, 0U) |     \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN7, 6U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SD_DATA0, 12U) |   \
                                     PIN_AFIO_AF(GPIOC_SD_DATA1, 12U) |   \
                                     PIN_AFIO_AF(GPIOC_SD_DATA2, 12U) |   \
                                     PIN_AFIO_AF(GPIOC_SD_DATA3, 12U) |   \
                                     PIN_AFIO_AF(GPIOC_SD_CLK, 12U) |     \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |    \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (input floating).
 * PD1  - PIN1                      (input floating).
 * PD2  - SD_CMD                    (input floating).
 * PD3  - PIN3                      (input floating).
 * PD4  - PIN4                      (input floating).
 * PD5  - PIN5                      (input floating).
 * PD6  - PIN6                      (input floating).
 * PD7  - PIN7                      (input floating).
 * PD8  - PIN8                      (input floating).
 * PD9  - PIN9                      (input floating).
 * PD10 - PIN10                     (input floating).
 * PD11 - PIN11                     (input floating).
 * PD12 - PIN12                     (input floating).
 * PD13 - PIN13                     (input floating).
 * PD14 - PIN14                     (input floating).
 * PD15 - PIN15                     (input floating).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_SD_CMD) |         \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SD_CMD) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOD_SD_CMD) |        \
                                     PIN_OSPEED_HIGH(GPIOD_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_SD_CMD) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOD_SD_CMD) |           \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_SD_CMD, 0U) |        \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                      (input floating).
 * PE1  - PIN1                      (input floating).
 * PE2  - PIN2                      (input floating).
 * PE3  - PIN3                      (input floating).
 * PE4  - PIN4                      (input floating).
 * PE5  - PIN5                      (input floating).
 * PE6  - PIN6                      (input floating).
 * PE7  - PIN7                      (input floating).
 * PE8  - PIN8                      (input floating).
 * PE9  - PIN9                      (input floating).
 * PE10 - PIN10                     (input floating).
 * PE11 - PIN11                     (input floating).
 * PE12 - PIN12                     (input floating).
 * PE13 - PIN13                     (input floating).
 * PE14 - PIN14                     (input floating).
 * PE15 - PIN15                     (input floating).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0U))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (input floating).
 * PF1  - PIN1                      (input floating).
 * PF2  - PIN2                      (input floating).
 * PF3  - PIN3                      (input floating).
 * PF4  - PIN4                      (input floating).
 * PF5  - PIN5                      (input floating).
 * PF6  - PIN6                      (input floating).
 * PF7  - PIN7                      (input floating).
 * PF8  - PIN8                      (input floating).
 * PF9  - PIN9                      (input floating).
 * PF10 - PIN10                     (input floating).
 * PF11 - PIN11                     (input floating).
 * PF12 - PIN12                     (input floating).
 * PF13 - PIN13                     (input floating).
 * PF14 - PIN14                     (input floating).
 * PF15 - PIN15                     (input floating).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0U))

/*
 * GPIOG setup:
 *
 * PG0  - PIN0                      (input floating).
 * PG1  - PIN1                      (input floating).
 * PG2  - PIN2                      (input floating).
 * PG3  - PIN3                      (input floating).
 * PG4  - PIN4                      (input floating).
 * PG5  - PIN5                      (input floating).
 * PG6  - PIN6                      (input floating).
 * PG7  - PIN7                      (input floating).
 * PG8  - PIN8                      (input floating).
 * PG9  - PIN9                      (input floating).
 * PG10 - PIN10                     (input floating).
 * PG11 - PIN11                     (input floating).
 * PG12 - PIN12                     (input floating).
 * PG13 - PIN13                     (input floating).
 * PG14 - PIN14                     (input floating).
 * PG15 - PIN15                     (input floating).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input floating).
 * PH3  - PIN3                      (input floating).
 * PH4  - PIN4                      (input floating).
 * PH5  - PIN5                      (input floating).
 * PH6  - PIN6                      (input floating).
 * PH7  - PIN7                      (input floating).
 * PH8  - PIN8                      (input floating).
 * PH9  - PIN9                      (input floating).
 * PH10 - PIN10                     (input floating).
 * PH11 - PIN11                     (input floating).
 * PH12 - PIN12                     (input floating).
 * PH13 - PIN13                     (input floating).
 * PH14 - PIN14                     (input floating).
 * PH15 - PIN15                     (input floating).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOH_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input floating).
 * PI1  - PIN1                      (input floating).
 * PI2  - PIN2                      (input floating).
 * PI3  - PIN3                      (input floating).
 * PI4  - PIN4                      (input floating).
 * PI5  - PIN5                      (input floating).
 * PI6  - PIN6                      (input floating).
 * PI7  - PIN7                      (input floating).
 * PI8  - PIN8                      (input floating).
 * PI9  - PIN9                      (input floating).
 * PI10 - PIN10                     (input floating).
 * PI11 - PIN11                     (input floating).
 * PI12 - PIN12                     (input floating).
 * PI13 - PIN13                     (input floating).
 * PI14 - PIN14                     (input floating).
 * PI15 - PIN15                     (input floating).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_FLOATING(GPIOI_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
