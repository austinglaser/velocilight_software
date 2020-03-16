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
 * Setup for STMicroelectronics STM32F746G-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_STM32F746G_DISCOVERY
#define BOARD_NAME                  "Velocilight SoundPuddle v3.0"

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                12000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   330U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F746xx

/*
 * IO pins assignments.
 */
#define GPIOA_ENCODER_SW            0U
#define GPIOA_VIN_ADC               1U
#define GPIOA_PCBTEMP1_ADC          2U
#define GPIOA_FAN_ENABLE            3U
#define GPIOA_FPGA_SPI_NSS          4U
#define GPIOA_FPGA_SPI_SCK          5U
#define GPIOA_FPGA_SPI_MISO         6U
#define GPIOA_FPGA_SPI_MOSI         7U
#define GPIOA_MCO1                  8U
#define GPIOA_USART1_TX             9U
#define GPIOA_USART1_RX             10U
#define GPIOA_OTG_FS_DM             11U
#define GPIOA_OTG_FS_DP             12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_JTDI                  15U

#define GPIOB_OUT2_IMON_ADC         0U
#define GPIOB_OUT3_IMON_ADC         1U
#define GPIOB_FLASH_CS              2U
#define GPIOB_SWO                   3U
#define GPIOB_JTRST                 4U
#define GPIOB_CAN_S                 5U
#define GPIOB_I2C1_SCL              6U
#define GPIOB_I2C1_SDA              7U
#define GPIOB_CAN1_RX               8U
#define GPIOB_CAN1_TX               9U
#define GPIOB_USART3_TX             10U
#define GPIOB_USART3_RX             11U
#define GPIOB_ICE40_CBSEL1          12U
#define GPIOB_USART3_CTS            13U
#define GPIOB_USART3_RTS            14U
#define GPIOB_LTC4020_STAT2         15U

#define GPIOC_LINEIN_R_ADC          0U
#define GPIOC_MIC0_ADC              1U
#define GPIOC_MIC1_ADC              2U
#define GPIOC_LINEIN_L_ADC          3U
#define GPIOC_OUT0_IMON_ADC         4U
#define GPIOC_OUT1_IMON_ADC         5U
#define GPIOC_IMU_FSYNC             6U
#define GPIOC_IMU_INT               7U
#define GPIOC_SD_D0                 8U
#define GPIOC_SD_D1                 9U
#define GPIOC_SD_D2                 10U
#define GPIOC_SD_D3                 11U
#define GPIOC_SD_CLK                12U
#define GPIOC_LTC4020_STAT1         13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_FMC_D2                0U
#define GPIOD_FMC_D3                1U
#define GPIOD_SD_CMD                2U
#define GPIOD_FMC_CLK               3U
#define GPIOD_FMC_NOE               4U
#define GPIOD_FMC_NWE               5U
#define GPIOD_FMC_NWAIT             6U
#define GPIOD_FMC_NE1               7U
#define GPIOD_FMC_D13               8U
#define GPIOD_FMC_D14               9U
#define GPIOD_FMC_D15               10U
#define GPIOD_FMC_A16               11U
#define GPIOD_FMC_A17               12U
#define GPIOD_FMC_A18               13U
#define GPIOD_FMC_D0                14U
#define GPIOD_FMC_D1                15U

#define GPIOE_FMC_NBL0              0U
#define GPIOE_FMC_NBL1              1U
#define GPIOE_SAI1_MCLK_A           2U
#define GPIOE_FMC_A19               3U
#define GPIOE_SAI1_FS_A             4U
#define GPIOE_SAI1_SCK_A            5U
#define GPIOE_SAI1_SD_A             6U
#define GPIOE_FMC_D4                7U
#define GPIOE_FMC_D5                8U
#define GPIOE_FMC_D6                9U
#define GPIOE_FMC_D7                10U
#define GPIOE_FMC_D8                11U
#define GPIOE_FMC_D9                12U
#define GPIOE_FMC_D10               13U
#define GPIOE_FMC_D11               14U
#define GPIOE_FMC_D12               15U

#define GPIOF_FMC_A0                0U
#define GPIOF_FMC_A1                1U
#define GPIOF_FMC_A2                2U
#define GPIOF_FMC_A3                3U
#define GPIOF_FMC_A4                4U
#define GPIOF_FMC_A5                5U
#define GPIOF_SAI_SD_B              6U
#define GPIOF_5V_48V_ADC            7U
#define GPIOF_5V_ADC                8U
#define GPIOF_PCBTEMP0_ADC          9U
#define GPIOF_BATT_ADC              10U
#define GPIOF_SAI2_SD_B             11U
#define GPIOF_FMC_A6                12U
#define GPIOF_FMC_A7                13U
#define GPIOF_FMC_A8                14U
#define GPIOF_FMC_A9                15U

#define GPIOG_FMC_A10               0U
#define GPIOG_FMC_A11               1U
#define GPIOG_FMC_A12               2U
#define GPIOG_FMC_A13               3U
#define GPIOG_FMC_A14               4U
#define GPIOG_FMC_A15               5U
#define GPIOG_DIP0                  6U
#define GPIOG_DIP1                  7U
#define GPIOG_DIP2                  8U
#define GPIOG_FMC_NE2               9U
#define GPIOG_SD_DETECT             10U
#define GPIOG_OUT0_ENABLE           11U
#define GPIOG_OUT1_ENABLE           12U
#define GPIOG_OUT2_ENABLE           13U
#define GPIOG_OUT3_ENABLE           14U
#define GPIOG_ICE40_CBSEL0          15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_OUT0_NFAULT           2U
#define GPIOH_OUT1_NFAULT           3U
#define GPIOH_I2C2_SCL              4U
#define GPIOH_I2C2_SDA              5U
#define GPIOH_ENCODER_A             6U
#define GPIOH_ICE40_CDONE           7U
#define GPIOH_ICE40_RESET           8U
#define GPIOH_ENCODER_B             9U
#define GPIOH_LED_R                 10U
#define GPIOH_LED_G                 11U
#define GPIOH_LED_B                 12U
#define GPIOH_ESP32_RESET           13U
#define GPIOH_ESP32_GPIO0           14U
#define GPIOH_LTC4020_SHUTDOWN      15U

#define GPIOI_SPI2_NSS              0U
#define GPIOI_SPI2_SCK              1U
#define GPIOI_SPI2_MISO             2U
#define GPIOI_SPI2_MOSI             3U
#define GPIOI_SAI2_MCLK_A           4U
#define GPIOI_SAI2_SCK_A            5U
#define GPIOI_SAI2_SD_A             6U
#define GPIOI_SAI2_FS_A             7U
#define GPIOI_CODEC_RESET           8U
#define GPIOI_OUT2_NFAULT           9U
#define GPIOI_OUT3_NFAULT           10U
#define GPIOI_5V_DISABLE            11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

#define GPIOJ_PIN0                  0U
#define GPIOJ_PIN1                  1U
#define GPIOJ_PIN2                  2U
#define GPIOJ_PIN3                  3U
#define GPIOJ_PIN4                  4U
#define GPIOJ_PIN5                  5U
#define GPIOJ_PIN6                  6U
#define GPIOJ_PIN7                  7U
#define GPIOJ_PIN8                  8U
#define GPIOJ_PIN9                  9U
#define GPIOJ_PIN10                 10U
#define GPIOJ_PIN11                 11U
#define GPIOJ_PIN12                 12U
#define GPIOJ_PIN13                 13U
#define GPIOJ_PIN14                 14U
#define GPIOJ_PIN15                 15U

#define GPIOK_PIN0                  0U
#define GPIOK_PIN1                  1U
#define GPIOK_PIN2                  2U
#define GPIOK_PIN3                  3U
#define GPIOK_PIN4                  4U
#define GPIOK_PIN5                  5U
#define GPIOK_PIN6                  6U
#define GPIOK_PIN7                  7U
#define GPIOK_PIN8                  8U
#define GPIOK_PIN9                  9U
#define GPIOK_PIN10                 10U
#define GPIOK_PIN11                 11U
#define GPIOK_PIN12                 12U
#define GPIOK_PIN13                 13U
#define GPIOK_PIN14                 14U
#define GPIOK_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_ENCODER_SW             PAL_LINE(GPIOA, 0U)
#define LINE_VIN_ADC                PAL_LINE(GPIOA, 1U)
#define LINE_PCBTEMP1_ADC           PAL_LINE(GPIOA, 2U)
#define LINE_FAN_ENABLE             PAL_LINE(GPIOA, 3U)
#define LINE_FPGA_SPI_NSS           PAL_LINE(GPIOA, 4U)
#define LINE_FPGA_SPI_SCK           PAL_LINE(GPIOA, 5U)
#define LINE_FPGA_SPI_MISO          PAL_LINE(GPIOA, 6U)
#define LINE_FPGA_SPI_MOSI          PAL_LINE(GPIOA, 7U)
#define LINE_MCO1                   PAL_LINE(GPIOA, 8U)
#define LINE_USART1_TX              PAL_LINE(GPIOA, 9U)
#define LINE_USART1_RX              PAL_LINE(GPIOA, 10U)
#define LINE_OTG_FS_DM              PAL_LINE(GPIOA, 11U)
#define LINE_OTG_FS_DP              PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_JTDI                   PAL_LINE(GPIOA, 15U)

#define LINE_OUT2_IMON_ADC          PAL_LINE(GPIOB, 0U)
#define LINE_OUT3_IMON_ADC          PAL_LINE(GPIOB, 1U)
#define LINE_FLASH_CS               PAL_LINE(GPIOB, 2U)
#define LINE_SWO                    PAL_LINE(GPIOB, 3U)
#define LINE_JTRST                  PAL_LINE(GPIOB, 4U)
#define LINE_CAN_S                  PAL_LINE(GPIOB, 5U)
#define LINE_I2C1_SCL               PAL_LINE(GPIOB, 6U)
#define LINE_I2C1_SDA               PAL_LINE(GPIOB, 7U)
#define LINE_CAN1_RX                PAL_LINE(GPIOB, 8U)
#define LINE_CAN1_TX                PAL_LINE(GPIOB, 9U)
#define LINE_USART3_TX              PAL_LINE(GPIOB, 10U)
#define LINE_USART3_RX              PAL_LINE(GPIOB, 11U)
#define LINE_ICE40_CBSEL1           PAL_LINE(GPIOB, 12U)
#define LINE_USART3_CTS             PAL_LINE(GPIOB, 13U)
#define LINE_USART3_RTS             PAL_LINE(GPIOB, 14U)
#define LINE_LTC4020_STAT2          PAL_LINE(GPIOB, 15U)

#define LINE_LINEIN_R_ADC           PAL_LINE(GPIOC, 0U)
#define LINE_MIC0_ADC               PAL_LINE(GPIOC, 1U)
#define LINE_MIC1_ADC               PAL_LINE(GPIOC, 2U)
#define LINE_LINEIN_L_ADC           PAL_LINE(GPIOC, 3U)
#define LINE_OUT0_IMON_ADC          PAL_LINE(GPIOC, 4U)
#define LINE_OUT1_IMON_ADC          PAL_LINE(GPIOC, 5U)
#define LINE_IMU_FSYNC              PAL_LINE(GPIOC, 6U)
#define LINE_IMU_INT                PAL_LINE(GPIOC, 7U)
#define LINE_SD_D0                  PAL_LINE(GPIOC, 8U)
#define LINE_SD_D1                  PAL_LINE(GPIOC, 9U)
#define LINE_SD_D2                  PAL_LINE(GPIOC, 10U)
#define LINE_SD_D3                  PAL_LINE(GPIOC, 11U)
#define LINE_SD_CLK                 PAL_LINE(GPIOC, 12U)
#define LINE_LTC4020_STAT1          PAL_LINE(GPIOC, 13U)
#define LINE_OSC32_IN               PAL_LINE(GPIOC, 14U)
#define LINE_OSC32_OUT              PAL_LINE(GPIOC, 15U)

#define LINE_FMC_D2                 PAL_LINE(GPIOD, 0U)
#define LINE_FMC_D3                 PAL_LINE(GPIOD, 1U)
#define LINE_SD_CMD                 PAL_LINE(GPIOD, 2U)
#define LINE_FMC_CLK                PAL_LINE(GPIOD, 3U)
#define LINE_FMC_NOE                PAL_LINE(GPIOD, 4U)
#define LINE_FMC_NWE                PAL_LINE(GPIOD, 5U)
#define LINE_FMC_NWAIT              PAL_LINE(GPIOD, 6U)
#define LINE_FMC_NE1                PAL_LINE(GPIOD, 7U)
#define LINE_FMC_D13                PAL_LINE(GPIOD, 8U)
#define LINE_FMC_D14                PAL_LINE(GPIOD, 9U)
#define LINE_FMC_D15                PAL_LINE(GPIOD, 10U)
#define LINE_FMC_A16                PAL_LINE(GPIOD, 11U)
#define LINE_FMC_A17                PAL_LINE(GPIOD, 12U)
#define LINE_FMC_A18                PAL_LINE(GPIOD, 13U)
#define LINE_FMC_D0                 PAL_LINE(GPIOD, 14U)
#define LINE_FMC_D1                 PAL_LINE(GPIOD, 15U)

#define LINE_FMC_NBL0               PAL_LINE(GPIOE, 0U)
#define LINE_FMC_NBL1               PAL_LINE(GPIOE, 1U)
#define LINE_SAI1_MCLK_A            PAL_LINE(GPIOE, 2U)
#define LINE_FMC_A19                PAL_LINE(GPIOE, 3U)
#define LINE_SAI1_FS_A              PAL_LINE(GPIOE, 4U)
#define LINE_SAI1_SCK_A             PAL_LINE(GPIOE, 5U)
#define LINE_SAI1_SD_A              PAL_LINE(GPIOE, 6U)
#define LINE_FMC_D4                 PAL_LINE(GPIOE, 7U)
#define LINE_FMC_D5                 PAL_LINE(GPIOE, 8U)
#define LINE_FMC_D6                 PAL_LINE(GPIOE, 9U)
#define LINE_FMC_D7                 PAL_LINE(GPIOE, 10U)
#define LINE_FMC_D8                 PAL_LINE(GPIOE, 11U)
#define LINE_FMC_D9                 PAL_LINE(GPIOE, 12U)
#define LINE_FMC_D10                PAL_LINE(GPIOE, 13U)
#define LINE_FMC_D11                PAL_LINE(GPIOE, 14U)
#define LINE_FMC_D12                PAL_LINE(GPIOE, 15U)

#define LINE_FMC_A0                 PAL_LINE(GPIOF, 0U)
#define LINE_FMC_A1                 PAL_LINE(GPIOF, 1U)
#define LINE_FMC_A2                 PAL_LINE(GPIOF, 2U)
#define LINE_FMC_A3                 PAL_LINE(GPIOF, 3U)
#define LINE_FMC_A4                 PAL_LINE(GPIOF, 4U)
#define LINE_FMC_A5                 PAL_LINE(GPIOF, 5U)
#define LINE_SAI_SD_B               PAL_LINE(GPIOF, 6U)
#define LINE_5V_48V_ADC             PAL_LINE(GPIOF, 7U)
#define LINE_5V_ADC                 PAL_LINE(GPIOF, 8U)
#define LINE_PCBTEMP0_ADC           PAL_LINE(GPIOF, 9U)
#define LINE_BATT_ADC               PAL_LINE(GPIOF, 10U)
#define LINE_SAI2_SD_B              PAL_LINE(GPIOF, 11U)
#define LINE_FMC_A6                 PAL_LINE(GPIOF, 12U)
#define LINE_FMC_A7                 PAL_LINE(GPIOF, 13U)
#define LINE_FMC_A8                 PAL_LINE(GPIOF, 14U)
#define LINE_FMC_A9                 PAL_LINE(GPIOF, 15U)

#define LINE_FMC_A10                PAL_LINE(GPIOG, 0U)
#define LINE_FMC_A11                PAL_LINE(GPIOG, 1U)
#define LINE_FMC_A12                PAL_LINE(GPIOG, 2U)
#define LINE_FMC_A13                PAL_LINE(GPIOG, 3U)
#define LINE_FMC_A14                PAL_LINE(GPIOG, 4U)
#define LINE_FMC_A15                PAL_LINE(GPIOG, 5U)
#define LINE_DIP0                   PAL_LINE(GPIOG, 6U)
#define LINE_DIP1                   PAL_LINE(GPIOG, 7U)
#define LINE_DIP2                   PAL_LINE(GPIOG, 8U)
#define LINE_FMC_NE2                PAL_LINE(GPIOG, 9U)
#define LINE_SD_DETECT              PAL_LINE(GPIOG, 10U)
#define LINE_OUT0_ENABLE            PAL_LINE(GPIOG, 11U)
#define LINE_OUT1_ENABLE            PAL_LINE(GPIOG, 12U)
#define LINE_OUT2_ENABLE            PAL_LINE(GPIOG, 13U)
#define LINE_OUT3_ENABLE            PAL_LINE(GPIOG, 14U)
#define LINE_ICE40_CBSEL0           PAL_LINE(GPIOG, 15U)

#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)
#define LINE_OUT0_NFAULT            PAL_LINE(GPIOH, 2U)
#define LINE_OUT1_NFAULT            PAL_LINE(GPIOH, 3U)
#define LINE_I2C2_SCL               PAL_LINE(GPIOH, 4U)
#define LINE_I2C2_SDA               PAL_LINE(GPIOH, 5U)
#define LINE_ENCODER_A              PAL_LINE(GPIOH, 6U)
#define LINE_ICE40_CDONE            PAL_LINE(GPIOH, 7U)
#define LINE_ICE40_RESET            PAL_LINE(GPIOH, 8U)
#define LINE_ENCODER_B              PAL_LINE(GPIOH, 9U)
#define LINE_LED_R                  PAL_LINE(GPIOH, 10U)
#define LINE_LED_G                  PAL_LINE(GPIOH, 11U)
#define LINE_LED_B                  PAL_LINE(GPIOH, 12U)
#define LINE_ESP32_RESET            PAL_LINE(GPIOH, 13U)
#define LINE_ESP32_GPIO0            PAL_LINE(GPIOH, 14U)
#define LINE_LTC4020_SHUTDOWN       PAL_LINE(GPIOH, 15U)

#define LINE_SPI2_NSS               PAL_LINE(GPIOI, 0U)
#define LINE_SPI2_SCK               PAL_LINE(GPIOI, 1U)
#define LINE_SPI2_MISO              PAL_LINE(GPIOI, 2U)
#define LINE_SPI2_MOSI              PAL_LINE(GPIOI, 3U)
#define LINE_SAI2_MCLK_A            PAL_LINE(GPIOI, 4U)
#define LINE_SAI2_SCK_A             PAL_LINE(GPIOI, 5U)
#define LINE_SAI2_SD_A              PAL_LINE(GPIOI, 6U)
#define LINE_SAI2_FS_A              PAL_LINE(GPIOI, 7U)
#define LINE_CODEC_RESET            PAL_LINE(GPIOI, 8U)
#define LINE_OUT2_NFAULT            PAL_LINE(GPIOI, 9U)
#define LINE_OUT3_NFAULT            PAL_LINE(GPIOI, 10U)
#define LINE_5V_DISABLE             PAL_LINE(GPIOI, 11U)

/*
 * Peripheral assignment
 */

#define FPGA_SPID                   SPID1

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
 * PA0  - ENCODER_SW                (input floating).
 * PA1  - VIN_ADC                   (input analog).
 * PA2  - PCBTEMP1_ADC              (input analog).
 * PA3  - FAN_ENABLE                (output pushpull, low).
 * PA4  - FPGA_SPI_NSS                  (output pushpull, high).
 * PA5  - FPGA_SPI_SCK                  (alternate 5).
 * PA6  - FPGA_SPI_MISO                 (alternate 5).
 * PA7  - FPGA_SPI_MOSI                 (alternate 5).
 * PA8  - MCO1                      (alternate 0).
 * PA9  - USART1_TX                 (alternate 7).
 * PA10 - USART1_RX                 (alternate 7).
 * PA11 - OTG_FS_DM                 (alternate 10).
 * PA12 - OTG_FS_DP                 (alternate 10).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - JTDI                      (alternate 0).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_ENCODER_SW)        | \
                                     PIN_MODE_ANALOG(GPIOA_VIN_ADC)          | \
                                     PIN_MODE_ANALOG(GPIOA_PCBTEMP1_ADC)     | \
                                     PIN_MODE_OUTPUT(GPIOA_FAN_ENABLE)       | \
                                     PIN_MODE_OUTPUT(GPIOA_FPGA_SPI_NSS)     | \
                                     PIN_MODE_ALTERNATE(GPIOA_FPGA_SPI_SCK)  | \
                                     PIN_MODE_ALTERNATE(GPIOA_FPGA_SPI_MISO) | \
                                     PIN_MODE_ALTERNATE(GPIOA_FPGA_SPI_MOSI) | \
                                     PIN_MODE_ALTERNATE(GPIOA_MCO1)          | \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_TX)     | \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_RX)     | \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DM)     | \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DP)     | \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO)         | \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK)         | \
                                     PIN_MODE_ALTERNATE(GPIOA_JTDI))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_ENCODER_SW)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_VIN_ADC)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PCBTEMP1_ADC)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_FAN_ENABLE)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_FPGA_SPI_NSS)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_FPGA_SPI_SCK)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_FPGA_SPI_MISO) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_FPGA_SPI_MOSI) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MCO1)          | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART1_TX)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART1_RX)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DM)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DP)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_JTDI))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_ENCODER_SW)       | \
                                     PIN_OSPEED_HIGH(GPIOA_VIN_ADC)          | \
                                     PIN_OSPEED_HIGH(GPIOA_PCBTEMP1_ADC)     | \
                                     PIN_OSPEED_HIGH(GPIOA_FAN_ENABLE)       | \
                                     PIN_OSPEED_HIGH(GPIOA_FPGA_SPI_NSS)     | \
                                     PIN_OSPEED_HIGH(GPIOA_FPGA_SPI_SCK)     | \
                                     PIN_OSPEED_HIGH(GPIOA_FPGA_SPI_MISO)    | \
                                     PIN_OSPEED_HIGH(GPIOA_FPGA_SPI_MOSI)    | \
                                     PIN_OSPEED_HIGH(GPIOA_MCO1)             | \
                                     PIN_OSPEED_HIGH(GPIOA_USART1_TX)        | \
                                     PIN_OSPEED_HIGH(GPIOA_USART1_RX)        | \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_DM)        | \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_DP)        | \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO)            | \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK)            | \
                                     PIN_OSPEED_HIGH(GPIOA_JTDI))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_ENCODER_SW)    | \
                                     PIN_PUPDR_FLOATING(GPIOA_VIN_ADC)       | \
                                     PIN_PUPDR_FLOATING(GPIOA_PCBTEMP1_ADC)  | \
                                     PIN_PUPDR_FLOATING(GPIOA_FAN_ENABLE)    | \
                                     PIN_PUPDR_FLOATING(GPIOA_FPGA_SPI_NSS)  | \
                                     PIN_PUPDR_FLOATING(GPIOA_FPGA_SPI_SCK)  | \
                                     PIN_PUPDR_FLOATING(GPIOA_FPGA_SPI_MISO) | \
                                     PIN_PUPDR_FLOATING(GPIOA_FPGA_SPI_MOSI) | \
                                     PIN_PUPDR_FLOATING(GPIOA_MCO1)          | \
                                     PIN_PUPDR_FLOATING(GPIOA_USART1_TX)     | \
                                     PIN_PUPDR_FLOATING(GPIOA_USART1_RX)     | \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DM)     | \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DP)     | \
                                     PIN_PUPDR_FLOATING(GPIOA_SWDIO)         | \
                                     PIN_PUPDR_FLOATING(GPIOA_SWCLK)         | \
                                     PIN_PUPDR_FLOATING(GPIOA_JTDI))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_ENCODER_SW)          | \
                                     PIN_ODR_HIGH(GPIOA_VIN_ADC)             | \
                                     PIN_ODR_HIGH(GPIOA_PCBTEMP1_ADC)        | \
                                     PIN_ODR_LOW(GPIOA_FAN_ENABLE)           | \
                                     PIN_ODR_HIGH(GPIOA_FPGA_SPI_NSS)        | \
                                     PIN_ODR_HIGH(GPIOA_FPGA_SPI_SCK)        | \
                                     PIN_ODR_HIGH(GPIOA_FPGA_SPI_MISO)       | \
                                     PIN_ODR_HIGH(GPIOA_FPGA_SPI_MOSI)       | \
                                     PIN_ODR_HIGH(GPIOA_MCO1)                | \
                                     PIN_ODR_HIGH(GPIOA_USART1_TX)           | \
                                     PIN_ODR_HIGH(GPIOA_USART1_RX)           | \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DM)           | \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DP)           | \
                                     PIN_ODR_HIGH(GPIOA_SWDIO)               | \
                                     PIN_ODR_HIGH(GPIOA_SWCLK)               | \
                                     PIN_ODR_HIGH(GPIOA_JTDI))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_ENCODER_SW, 0U)       | \
                                     PIN_AFIO_AF(GPIOA_VIN_ADC, 0U)          | \
                                     PIN_AFIO_AF(GPIOA_PCBTEMP1_ADC, 0U)     | \
                                     PIN_AFIO_AF(GPIOA_FAN_ENABLE, 0U)       | \
                                     PIN_AFIO_AF(GPIOA_FPGA_SPI_NSS, 0U)     | \
                                     PIN_AFIO_AF(GPIOA_FPGA_SPI_SCK, 5U)     | \
                                     PIN_AFIO_AF(GPIOA_FPGA_SPI_MISO, 5U)    | \
                                     PIN_AFIO_AF(GPIOA_FPGA_SPI_MOSI, 5U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_MCO1, 0U)             | \
                                     PIN_AFIO_AF(GPIOA_USART1_TX, 7U)        | \
                                     PIN_AFIO_AF(GPIOA_USART1_RX, 7U)        | \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DM, 10U)       | \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DP, 10U)       | \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U)            | \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U)            | \
                                     PIN_AFIO_AF(GPIOA_JTDI, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - OUT2_IMON_ADC             (input analog).
 * PB1  - OUT3_IMON_ADC             (input analog).
 * PB2  - FLASH_CS                  (input floating).
 * PB3  - SWO                       (alternate 0).
 * PB4  - JTRST                     (alternate 0).
 * PB5  - CAN_S                     (output pushpull, high).
 * PB6  - I2C1_SCL                  (alternate 4).
 * PB7  - I2C1_SDA                  (alternate 4).
 * PB8  - CAN1_RX                   (alternate 9).
 * PB9  - CAN1_TX                   (alternate 9).
 * PB10 - USART3_TX                 (alternate 7).
 * PB11 - USART3_RX                 (alternate 7).
 * PB12 - ICE40_CBSEL1              (input floating).
 * PB13 - USART3_CTS                (alternate 7).
 * PB14 - USART3_RTS                (alternate 7).
 * PB15 - LTC4020_STAT2             (input floating).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ANALOG(GPIOB_OUT2_IMON_ADC)     | \
                                     PIN_MODE_ANALOG(GPIOB_OUT3_IMON_ADC)     | \
                                     PIN_MODE_INPUT(GPIOB_FLASH_CS)           | \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO)            | \
                                     PIN_MODE_ALTERNATE(GPIOB_JTRST)          | \
                                     PIN_MODE_OUTPUT(GPIOB_CAN_S)             | \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SCL)       | \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SDA)       | \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN1_RX)        | \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN1_TX)        | \
                                     PIN_MODE_ALTERNATE(GPIOB_USART3_TX)      | \
                                     PIN_MODE_ALTERNATE(GPIOB_USART3_RX)      | \
                                     PIN_MODE_INPUT(GPIOB_ICE40_CBSEL1)       | \
                                     PIN_MODE_ALTERNATE(GPIOB_USART3_CTS)     | \
                                     PIN_MODE_ALTERNATE(GPIOB_USART3_RTS)     | \
                                     PIN_MODE_INPUT(GPIOB_LTC4020_STAT2))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_OUT2_IMON_ADC)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OUT3_IMON_ADC)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_FLASH_CS)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO)            | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_JTRST)          | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN_S)          | \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SCL)      | \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SDA)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN1_RX)        | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN1_TX)        | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USART3_TX)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USART3_RX)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ICE40_CBSEL1)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USART3_CTS)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USART3_RTS)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LTC4020_STAT2))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_OUT2_IMON_ADC)     | \
                                     PIN_OSPEED_HIGH(GPIOB_OUT3_IMON_ADC)     | \
                                     PIN_OSPEED_HIGH(GPIOB_FLASH_CS)          | \
                                     PIN_OSPEED_HIGH(GPIOB_SWO)               | \
                                     PIN_OSPEED_HIGH(GPIOB_JTRST)             | \
                                     PIN_OSPEED_HIGH(GPIOB_CAN_S)             | \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SCL)          | \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SDA)          | \
                                     PIN_OSPEED_HIGH(GPIOB_CAN1_RX)           | \
                                     PIN_OSPEED_HIGH(GPIOB_CAN1_TX)           | \
                                     PIN_OSPEED_HIGH(GPIOB_USART3_TX)         | \
                                     PIN_OSPEED_HIGH(GPIOB_USART3_RX)         | \
                                     PIN_OSPEED_HIGH(GPIOB_ICE40_CBSEL1)      | \
                                     PIN_OSPEED_HIGH(GPIOB_USART3_CTS)        | \
                                     PIN_OSPEED_HIGH(GPIOB_USART3_RTS)        | \
                                     PIN_OSPEED_HIGH(GPIOB_LTC4020_STAT2))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_OUT2_IMON_ADC)  | \
                                     PIN_PUPDR_FLOATING(GPIOB_OUT3_IMON_ADC)  | \
                                     PIN_PUPDR_FLOATING(GPIOB_FLASH_CS)       | \
                                     PIN_PUPDR_FLOATING(GPIOB_SWO)            | \
                                     PIN_PUPDR_FLOATING(GPIOB_JTRST)          | \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN_S)          | \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SCL)       | \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SDA)       | \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN1_RX)        | \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN1_TX)        | \
                                     PIN_PUPDR_FLOATING(GPIOB_USART3_TX)      | \
                                     PIN_PUPDR_FLOATING(GPIOB_USART3_RX)      | \
                                     PIN_PUPDR_FLOATING(GPIOB_ICE40_CBSEL1)   | \
                                     PIN_PUPDR_FLOATING(GPIOB_USART3_CTS)     | \
                                     PIN_PUPDR_FLOATING(GPIOB_USART3_RTS)     | \
                                     PIN_PUPDR_FLOATING(GPIOB_LTC4020_STAT2))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_OUT2_IMON_ADC)        | \
                                     PIN_ODR_HIGH(GPIOB_OUT3_IMON_ADC)        | \
                                     PIN_ODR_HIGH(GPIOB_FLASH_CS)             | \
                                     PIN_ODR_HIGH(GPIOB_SWO)                  | \
                                     PIN_ODR_HIGH(GPIOB_JTRST)                | \
                                     PIN_ODR_HIGH(GPIOB_CAN_S)                | \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SCL)             | \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SDA)             | \
                                     PIN_ODR_HIGH(GPIOB_CAN1_RX)              | \
                                     PIN_ODR_HIGH(GPIOB_CAN1_TX)              | \
                                     PIN_ODR_HIGH(GPIOB_USART3_TX)            | \
                                     PIN_ODR_HIGH(GPIOB_USART3_RX)            | \
                                     PIN_ODR_HIGH(GPIOB_ICE40_CBSEL1)         | \
                                     PIN_ODR_HIGH(GPIOB_USART3_CTS)           | \
                                     PIN_ODR_HIGH(GPIOB_USART3_RTS)           | \
                                     PIN_ODR_HIGH(GPIOB_LTC4020_STAT2))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_OUT2_IMON_ADC, 0U)     | \
                                     PIN_AFIO_AF(GPIOB_OUT3_IMON_ADC, 0U)     | \
                                     PIN_AFIO_AF(GPIOB_FLASH_CS, 0U)          | \
                                     PIN_AFIO_AF(GPIOB_SWO, 0U)               | \
                                     PIN_AFIO_AF(GPIOB_JTRST, 0U)             | \
                                     PIN_AFIO_AF(GPIOB_CAN_S, 0U)             | \
                                     PIN_AFIO_AF(GPIOB_I2C1_SCL, 4U)          | \
                                     PIN_AFIO_AF(GPIOB_I2C1_SDA, 4U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_CAN1_RX, 9U)           | \
                                     PIN_AFIO_AF(GPIOB_CAN1_TX, 9U)           | \
                                     PIN_AFIO_AF(GPIOB_USART3_TX, 7U)         | \
                                     PIN_AFIO_AF(GPIOB_USART3_RX, 7U)         | \
                                     PIN_AFIO_AF(GPIOB_ICE40_CBSEL1, 0U)      | \
                                     PIN_AFIO_AF(GPIOB_USART3_CTS, 7U)        | \
                                     PIN_AFIO_AF(GPIOB_USART3_RTS, 7U)        | \
                                     PIN_AFIO_AF(GPIOB_LTC4020_STAT2, 0U))

/*
 * GPIOC setup:
 *
 * PC0  - LINEIN_R_ADC              (input analog).
 * PC1  - MIC0_ADC                  (input analog).
 * PC2  - MIC1_ADC                  (input analog).
 * PC3  - LINEIN_L_ADC              (input analog).
 * PC4  - OUT0_IMON_ADC             (input analog).
 * PC5  - OUT1_IMON_ADC             (input analog).
 * PC6  - IMU_FSYNC                 (input pulldown).
 * PC7  - IMU_INT                   (input floating).
 * PC8  - SD_D0                     (alternate 12).
 * PC9  - SD_D1                     (alternate 12).
 * PC10 - SD_D2                     (alternate 12).
 * PC11 - SD_D3                     (alternate 12).
 * PC12 - SD_CLK                    (alternate 12).
 * PC13 - LTC4020_STAT1             (input floating).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ANALOG(GPIOC_LINEIN_R_ADC)     | \
                                     PIN_MODE_ANALOG(GPIOC_MIC0_ADC)         | \
                                     PIN_MODE_ANALOG(GPIOC_MIC1_ADC)         | \
                                     PIN_MODE_ANALOG(GPIOC_LINEIN_L_ADC)     | \
                                     PIN_MODE_ANALOG(GPIOC_OUT0_IMON_ADC)    | \
                                     PIN_MODE_ANALOG(GPIOC_OUT1_IMON_ADC)    | \
                                     PIN_MODE_INPUT(GPIOC_IMU_FSYNC)         | \
                                     PIN_MODE_INPUT(GPIOC_IMU_INT)           | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D0)         | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D1)         | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D2)         | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D3)         | \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_CLK)        | \
                                     PIN_MODE_INPUT(GPIOC_LTC4020_STAT1)     | \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN)          | \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_LINEIN_R_ADC)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_MIC0_ADC)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_MIC1_ADC)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LINEIN_L_ADC)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OUT0_IMON_ADC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OUT1_IMON_ADC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_IMU_FSYNC)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_IMU_INT)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D0)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D1)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D2)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D3)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_CLK)        | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LTC4020_STAT1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_LINEIN_R_ADC)     | \
                                     PIN_OSPEED_HIGH(GPIOC_MIC0_ADC)         | \
                                     PIN_OSPEED_HIGH(GPIOC_MIC1_ADC)         | \
                                     PIN_OSPEED_HIGH(GPIOC_LINEIN_L_ADC)     | \
                                     PIN_OSPEED_HIGH(GPIOC_OUT0_IMON_ADC)    | \
                                     PIN_OSPEED_HIGH(GPIOC_OUT1_IMON_ADC)    | \
                                     PIN_OSPEED_HIGH(GPIOC_IMU_FSYNC)        | \
                                     PIN_OSPEED_HIGH(GPIOC_IMU_INT)          | \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D0)            | \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D1)            | \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D2)            | \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D3)            | \
                                     PIN_OSPEED_HIGH(GPIOC_SD_CLK)           | \
                                     PIN_OSPEED_HIGH(GPIOC_LTC4020_STAT1)    | \
                                     PIN_OSPEED_VERYLOW(GPIOC_OSC32_IN)      | \
                                     PIN_OSPEED_VERYLOW(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_LINEIN_R_ADC)  | \
                                     PIN_PUPDR_FLOATING(GPIOC_MIC0_ADC)      | \
                                     PIN_PUPDR_FLOATING(GPIOC_MIC1_ADC)      | \
                                     PIN_PUPDR_FLOATING(GPIOC_LINEIN_L_ADC)  | \
                                     PIN_PUPDR_FLOATING(GPIOC_OUT0_IMON_ADC) | \
                                     PIN_PUPDR_FLOATING(GPIOC_OUT1_IMON_ADC) | \
                                     PIN_PUPDR_PULLDOWN(GPIOC_IMU_FSYNC)     | \
                                     PIN_PUPDR_FLOATING(GPIOC_IMU_INT)       | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D0)         | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D1)         | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D2)         | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D3)         | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_CLK)        | \
                                     PIN_PUPDR_FLOATING(GPIOC_LTC4020_STAT1) | \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN)      | \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_LINEIN_R_ADC)        | \
                                     PIN_ODR_HIGH(GPIOC_MIC0_ADC)            | \
                                     PIN_ODR_HIGH(GPIOC_MIC1_ADC)            | \
                                     PIN_ODR_HIGH(GPIOC_LINEIN_L_ADC)        | \
                                     PIN_ODR_HIGH(GPIOC_OUT0_IMON_ADC)       | \
                                     PIN_ODR_HIGH(GPIOC_OUT1_IMON_ADC)       | \
                                     PIN_ODR_HIGH(GPIOC_IMU_FSYNC)           | \
                                     PIN_ODR_HIGH(GPIOC_IMU_INT)             | \
                                     PIN_ODR_HIGH(GPIOC_SD_D0)               | \
                                     PIN_ODR_HIGH(GPIOC_SD_D1)               | \
                                     PIN_ODR_HIGH(GPIOC_SD_D2)               | \
                                     PIN_ODR_HIGH(GPIOC_SD_D3)               | \
                                     PIN_ODR_HIGH(GPIOC_SD_CLK)              | \
                                     PIN_ODR_HIGH(GPIOC_LTC4020_STAT1)       | \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN)            | \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_LINEIN_R_ADC, 0U)     | \
                                     PIN_AFIO_AF(GPIOC_MIC0_ADC, 0U)         | \
                                     PIN_AFIO_AF(GPIOC_MIC1_ADC, 0U)         | \
                                     PIN_AFIO_AF(GPIOC_LINEIN_L_ADC, 0U)     | \
                                     PIN_AFIO_AF(GPIOC_OUT0_IMON_ADC, 0U)    | \
                                     PIN_AFIO_AF(GPIOC_OUT1_IMON_ADC, 0U)    | \
                                     PIN_AFIO_AF(GPIOC_IMU_FSYNC, 0U)        | \
                                     PIN_AFIO_AF(GPIOC_IMU_INT, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SD_D0, 12U)           | \
                                     PIN_AFIO_AF(GPIOC_SD_D1, 12U)           | \
                                     PIN_AFIO_AF(GPIOC_SD_D2, 12U)           | \
                                     PIN_AFIO_AF(GPIOC_SD_D3, 12U)           | \
                                     PIN_AFIO_AF(GPIOC_SD_CLK, 12U)          | \
                                     PIN_AFIO_AF(GPIOC_LTC4020_STAT1, 0U)    | \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U)         | \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - FMC_D2                    (alternate 12).
 * PD1  - FMC_D3                    (alternate 12).
 * PD2  - SD_CMD                    (alternate 12).
 * PD3  - FMC_CLK                   (alternate 12).
 * PD4  - FMC_NOE                   (alternate 12).
 * PD5  - FMC_NWE                   (alternate 12).
 * PD6  - FMC_NWAIT                 (alternate 12).
 * PD7  - FMC_NE1                   (alternate 12).
 * PD8  - FMC_D13                   (alternate 12).
 * PD9  - FMC_D14                   (alternate 12).
 * PD10 - FMC_D15                   (alternate 12).
 * PD11 - FMC_A16                   (alternate 12).
 * PD12 - FMC_A17                   (alternate 12).
 * PD13 - FMC_A18                   (alternate 12).
 * PD14 - FMC_D0                    (alternate 12).
 * PD15 - FMC_D1                    (alternate 12).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ALTERNATE(GPIOD_FMC_D2)    | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D3)    | \
                                     PIN_MODE_ALTERNATE(GPIOD_SD_CMD)    | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_CLK)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NOE)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NWE)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NWAIT) | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NE1)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D13)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D14)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D15)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A16)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A17)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A18)   | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D0)    | \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D1))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_FMC_D2)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D3)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SD_CMD)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_CLK)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NOE)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NWE)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NWAIT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NE1)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D13)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D14)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D15)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A16)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A17)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A18)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D0)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D1))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_FMC_D2)       | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D3)       | \
                                     PIN_OSPEED_HIGH(GPIOD_SD_CMD)       | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_CLK)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NOE)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NWE)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NWAIT)    | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NE1)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D13)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D14)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D15)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A16)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A17)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A18)      | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D0)       | \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_FMC_D2)    | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D3)    | \
                                     PIN_PUPDR_FLOATING(GPIOD_SD_CMD)    | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_CLK)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NOE)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NWE)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NWAIT) | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NE1)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D13)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D14)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D15)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A16)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A17)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A18)   | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D0)    | \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D1))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_FMC_D2)          | \
                                     PIN_ODR_HIGH(GPIOD_FMC_D3)          | \
                                     PIN_ODR_HIGH(GPIOD_SD_CMD)          | \
                                     PIN_ODR_HIGH(GPIOD_FMC_CLK)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_NOE)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_NWE)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_NWAIT)       | \
                                     PIN_ODR_HIGH(GPIOD_FMC_NE1)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_D13)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_D14)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_D15)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_A16)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_A17)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_A18)         | \
                                     PIN_ODR_HIGH(GPIOD_FMC_D0)          | \
                                     PIN_ODR_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_FMC_D2, 12U)      | \
                                     PIN_AFIO_AF(GPIOD_FMC_D3, 12U)      | \
                                     PIN_AFIO_AF(GPIOD_SD_CMD, 12U)      | \
                                     PIN_AFIO_AF(GPIOD_FMC_CLK, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_NOE, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_NWE, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_NWAIT, 12U)   | \
                                     PIN_AFIO_AF(GPIOD_FMC_NE1, 12U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_FMC_D13, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_D14, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_D15, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_A16, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_A17, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_A18, 12U)     | \
                                     PIN_AFIO_AF(GPIOD_FMC_D0, 12U)      | \
                                     PIN_AFIO_AF(GPIOD_FMC_D1, 12U))

/*
 * GPIOE setup:
 *
 * PE0  - FMC_NBL0                  (alternate 12).
 * PE1  - FMC_NBL1                  (alternate 12).
 * PE2  - SAI1_MCLK_A               (alternate 6).
 * PE3  - FMC_A19                   (alternate 12).
 * PE4  - SAI1_FS_A                 (alternate 6).
 * PE5  - SAI1_SCK_A                (alternate 6).
 * PE6  - SAI1_SD_A                 (alternate 6).
 * PE7  - FMC_D4                    (alternate 12).
 * PE8  - FMC_D5                    (alternate 12).
 * PE9  - FMC_D6                    (alternate 12).
 * PE10 - FMC_D7                    (alternate 12).
 * PE11 - FMC_D8                    (alternate 12).
 * PE12 - FMC_D9                    (alternate 12).
 * PE13 - FMC_D10                   (alternate 12).
 * PE14 - FMC_D11                   (alternate 12).
 * PE15 - FMC_D12                   (alternate 12).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ALTERNATE(GPIOE_FMC_NBL0)    | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_NBL1)    | \
                                     PIN_MODE_ALTERNATE(GPIOE_SAI1_MCLK_A) | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_A19)     | \
                                     PIN_MODE_ALTERNATE(GPIOE_SAI1_FS_A)   | \
                                     PIN_MODE_ALTERNATE(GPIOE_SAI1_SCK_A)  | \
                                     PIN_MODE_ALTERNATE(GPIOE_SAI1_SD_A)   | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D4)      | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D5)      | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D6)      | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D7)      | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D8)      | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D9)      | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D10)     | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D11)     | \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D12))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL0)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL1)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SAI1_MCLK_A) | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_A19)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SAI1_FS_A)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SAI1_SCK_A)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SAI1_SD_A)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D4)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D5)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D6)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D7)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D8)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D9)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D10)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D11)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D12))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_FMC_NBL0)       | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_NBL1)       | \
                                     PIN_OSPEED_HIGH(GPIOE_SAI1_MCLK_A)    | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_A19)        | \
                                     PIN_OSPEED_HIGH(GPIOE_SAI1_FS_A)      | \
                                     PIN_OSPEED_HIGH(GPIOE_SAI1_SCK_A)     | \
                                     PIN_OSPEED_HIGH(GPIOE_SAI1_SD_A)      | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D4)         | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D5)         | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D6)         | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D7)         | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D8)         | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D9)         | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D10)        | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D11)        | \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_FMC_NBL0)    | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_NBL1)    | \
                                     PIN_PUPDR_FLOATING(GPIOE_SAI1_MCLK_A) | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_A19)     | \
                                     PIN_PUPDR_FLOATING(GPIOE_SAI1_FS_A)   | \
                                     PIN_PUPDR_FLOATING(GPIOE_SAI1_SCK_A)  | \
                                     PIN_PUPDR_FLOATING(GPIOE_SAI1_SD_A)   | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D4)      | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D5)      | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D6)      | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D7)      | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D8)      | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D9)      | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D10)     | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D11)     | \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D12))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_FMC_NBL0)          | \
                                     PIN_ODR_HIGH(GPIOE_FMC_NBL1)          | \
                                     PIN_ODR_HIGH(GPIOE_SAI1_MCLK_A)       | \
                                     PIN_ODR_HIGH(GPIOE_FMC_A19)           | \
                                     PIN_ODR_HIGH(GPIOE_SAI1_FS_A)         | \
                                     PIN_ODR_HIGH(GPIOE_SAI1_SCK_A)        | \
                                     PIN_ODR_HIGH(GPIOE_SAI1_SD_A)         | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D4)            | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D5)            | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D6)            | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D7)            | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D8)            | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D9)            | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D10)           | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D11)           | \
                                     PIN_ODR_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_FMC_NBL0, 12U)      | \
                                     PIN_AFIO_AF(GPIOE_FMC_NBL1, 12U)      | \
                                     PIN_AFIO_AF(GPIOE_SAI1_MCLK_A, 6U)    | \
                                     PIN_AFIO_AF(GPIOE_FMC_A19, 12U)       | \
                                     PIN_AFIO_AF(GPIOE_SAI1_FS_A, 6U)      | \
                                     PIN_AFIO_AF(GPIOE_SAI1_SCK_A, 6U)     | \
                                     PIN_AFIO_AF(GPIOE_SAI1_SD_A, 6U)      | \
                                     PIN_AFIO_AF(GPIOE_FMC_D4, 12U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_FMC_D5, 12U)        | \
                                     PIN_AFIO_AF(GPIOE_FMC_D6, 12U)        | \
                                     PIN_AFIO_AF(GPIOE_FMC_D7, 12U)        | \
                                     PIN_AFIO_AF(GPIOE_FMC_D8, 12U)        | \
                                     PIN_AFIO_AF(GPIOE_FMC_D9, 12U)        | \
                                     PIN_AFIO_AF(GPIOE_FMC_D10, 12U)       | \
                                     PIN_AFIO_AF(GPIOE_FMC_D11, 12U)       | \
                                     PIN_AFIO_AF(GPIOE_FMC_D12, 12U))

/*
 * GPIOF setup:
 *
 * PF0  - FMC_A0                    (alternate 12).
 * PF1  - FMC_A1                    (alternate 12).
 * PF2  - FMC_A2                    (alternate 12).
 * PF3  - FMC_A3                    (alternate 12).
 * PF4  - FMC_A4                    (alternate 12).
 * PF5  - FMC_A5                    (alternate 12).
 * PF6  - SAI_SD_B                  (alternate 6).
 * PF7  - 5V_48V_ADC                (input analog).
 * PF8  - 5V_ADC                    (input analog).
 * PF9  - PCBTEMP0_ADC              (input analog).
 * PF10 - BATT_ADC                  (input analog).
 * PF11 - SAI2_SD_B                 (alternate 10).
 * PF12 - FMC_A6                    (alternate 12).
 * PF13 - FMC_A7                    (alternate 12).
 * PF14 - FMC_A8                    (alternate 12).
 * PF15 - FMC_A9                    (alternate 12).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_ALTERNATE(GPIOF_FMC_A0)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A1)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A2)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A3)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A4)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A5)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_SAI_SD_B)     | \
                                     PIN_MODE_ANALOG(GPIOF_5V_48V_ADC)      | \
                                     PIN_MODE_ANALOG(GPIOF_5V_ADC)          | \
                                     PIN_MODE_ANALOG(GPIOF_PCBTEMP0_ADC)    | \
                                     PIN_MODE_ANALOG(GPIOF_BATT_ADC)        | \
                                     PIN_MODE_ALTERNATE(GPIOF_SAI2_SD_B)    | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A6)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A7)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A8)       | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A9))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_FMC_A0)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A1)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A2)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A3)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A4)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A5)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SAI_SD_B)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_5V_48V_ADC)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_5V_ADC)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PCBTEMP0_ADC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_BATT_ADC)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SAI2_SD_B)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A6)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A7)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A8)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A9))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_FMC_A0)          | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A1)          | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A2)          | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A3)          | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A4)          | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A5)          | \
                                     PIN_OSPEED_HIGH(GPIOF_SAI_SD_B)        | \
                                     PIN_OSPEED_HIGH(GPIOF_5V_48V_ADC)      | \
                                     PIN_OSPEED_HIGH(GPIOF_5V_ADC)          | \
                                     PIN_OSPEED_HIGH(GPIOF_PCBTEMP0_ADC)    | \
                                     PIN_OSPEED_HIGH(GPIOF_BATT_ADC)        | \
                                     PIN_OSPEED_HIGH(GPIOF_SAI2_SD_B)       | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A6)          | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A7)          | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A8)          | \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_FMC_A0)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A1)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A2)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A3)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A4)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A5)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_SAI_SD_B)     | \
                                     PIN_PUPDR_FLOATING(GPIOF_5V_48V_ADC)   | \
                                     PIN_PUPDR_FLOATING(GPIOF_5V_ADC)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_PCBTEMP0_ADC) | \
                                     PIN_PUPDR_FLOATING(GPIOF_BATT_ADC)     | \
                                     PIN_PUPDR_FLOATING(GPIOF_SAI2_SD_B)    | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A6)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A7)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A8)       | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A9))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_FMC_A0)             | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A1)             | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A2)             | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A3)             | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A4)             | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A5)             | \
                                     PIN_ODR_HIGH(GPIOF_SAI_SD_B)           | \
                                     PIN_ODR_HIGH(GPIOF_5V_48V_ADC)         | \
                                     PIN_ODR_HIGH(GPIOF_5V_ADC)             | \
                                     PIN_ODR_HIGH(GPIOF_PCBTEMP0_ADC)       | \
                                     PIN_ODR_HIGH(GPIOF_BATT_ADC)           | \
                                     PIN_ODR_HIGH(GPIOF_SAI2_SD_B)          | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A6)             | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A7)             | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A8)             | \
                                     PIN_ODR_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_FMC_A0, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_FMC_A1, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_FMC_A2, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_FMC_A3, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_FMC_A4, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_FMC_A5, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_SAI_SD_B, 6U)        | \
                                     PIN_AFIO_AF(GPIOF_5V_48V_ADC, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_5V_ADC, 0U)          | \
                                     PIN_AFIO_AF(GPIOF_PCBTEMP0_ADC, 0U)    | \
                                     PIN_AFIO_AF(GPIOF_BATT_ADC, 0U)        | \
                                     PIN_AFIO_AF(GPIOF_SAI2_SD_B, 10U)      | \
                                     PIN_AFIO_AF(GPIOF_FMC_A6, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_FMC_A7, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_FMC_A8, 12U)         | \
                                     PIN_AFIO_AF(GPIOF_FMC_A9, 12U))

/*
 * GPIOG setup:
 *
 * PG0  - FMC_A10                   (alternate 12).
 * PG1  - FMC_A11                   (alternate 12).
 * PG2  - FMC_A12                   (alternate 12).
 * PG3  - FMC_A13                   (alternate 12).
 * PG4  - FMC_A14                   (alternate 12).
 * PG5  - FMC_A15                   (alternate 12).
 * PG6  - DIP0                      (input floating).
 * PG7  - DIP1                      (input floating).
 * PG8  - DIP2                      (input floating).
 * PG9  - FMC_NE2                   (alternate 12).
 * PG10 - SD_DETECT                 (input floating).
 * PG11 - OUT0_ENABLE               (output pushpull, high).
 * PG12 - OUT1_ENABLE               (output pushpull, high).
 * PG13 - OUT2_ENABLE               (output pushpull, high).
 * PG14 - OUT3_ENABLE               (output pushpull, high).
 * PG15 - ICE40_CBSEL0              (input floating).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_ALTERNATE(GPIOG_FMC_A10)       | \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A11)       | \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A12)       | \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A13)       | \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A14)       | \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A15)       | \
                                     PIN_MODE_INPUT(GPIOG_DIP0)              | \
                                     PIN_MODE_INPUT(GPIOG_DIP1)              | \
                                     PIN_MODE_INPUT(GPIOG_DIP2)              | \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_NE2)       | \
                                     PIN_MODE_INPUT(GPIOG_SD_DETECT)         | \
                                     PIN_MODE_OUTPUT(GPIOG_OUT0_ENABLE)      | \
                                     PIN_MODE_OUTPUT(GPIOG_OUT1_ENABLE)      | \
                                     PIN_MODE_OUTPUT(GPIOG_OUT2_ENABLE)      | \
                                     PIN_MODE_OUTPUT(GPIOG_OUT3_ENABLE)      | \
                                     PIN_MODE_INPUT(GPIOG_ICE40_CBSEL0))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_FMC_A10)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A11)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A12)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A13)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A14)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A15)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_DIP0)          | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_DIP1)          | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_DIP2)          | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_NE2)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_SD_DETECT)     | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_OUT0_ENABLE)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_OUT1_ENABLE)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_OUT2_ENABLE)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_OUT3_ENABLE)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_ICE40_CBSEL0))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_FMC_A10)          | \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A11)          | \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A12)          | \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A13)          | \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A14)          | \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A15)          | \
                                     PIN_OSPEED_HIGH(GPIOG_DIP0)             | \
                                     PIN_OSPEED_HIGH(GPIOG_DIP1)             | \
                                     PIN_OSPEED_HIGH(GPIOG_DIP2)             | \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_NE2)          | \
                                     PIN_OSPEED_HIGH(GPIOG_SD_DETECT)        | \
                                     PIN_OSPEED_HIGH(GPIOG_OUT0_ENABLE)      | \
                                     PIN_OSPEED_HIGH(GPIOG_OUT1_ENABLE)      | \
                                     PIN_OSPEED_HIGH(GPIOG_OUT2_ENABLE)      | \
                                     PIN_OSPEED_HIGH(GPIOG_OUT3_ENABLE)      | \
                                     PIN_OSPEED_HIGH(GPIOG_ICE40_CBSEL0))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_FMC_A10)       | \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A11)       | \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A12)       | \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A13)       | \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A14)       | \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A15)       | \
                                     PIN_PUPDR_FLOATING(GPIOG_DIP0)          | \
                                     PIN_PUPDR_FLOATING(GPIOG_DIP1)          | \
                                     PIN_PUPDR_FLOATING(GPIOG_DIP2)          | \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_NE2)       | \
                                     PIN_PUPDR_FLOATING(GPIOG_SD_DETECT)     | \
                                     PIN_PUPDR_FLOATING(GPIOG_OUT0_ENABLE)   | \
                                     PIN_PUPDR_FLOATING(GPIOG_OUT1_ENABLE)   | \
                                     PIN_PUPDR_FLOATING(GPIOG_OUT2_ENABLE)   | \
                                     PIN_PUPDR_FLOATING(GPIOG_OUT3_ENABLE)   | \
                                     PIN_PUPDR_FLOATING(GPIOG_ICE40_CBSEL0))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_FMC_A10)             | \
                                     PIN_ODR_HIGH(GPIOG_FMC_A11)             | \
                                     PIN_ODR_HIGH(GPIOG_FMC_A12)             | \
                                     PIN_ODR_HIGH(GPIOG_FMC_A13)             | \
                                     PIN_ODR_HIGH(GPIOG_FMC_A14)             | \
                                     PIN_ODR_HIGH(GPIOG_FMC_A15)             | \
                                     PIN_ODR_HIGH(GPIOG_DIP0)                | \
                                     PIN_ODR_HIGH(GPIOG_DIP1)                | \
                                     PIN_ODR_HIGH(GPIOG_DIP2)                | \
                                     PIN_ODR_HIGH(GPIOG_FMC_NE2)             | \
                                     PIN_ODR_HIGH(GPIOG_SD_DETECT)           | \
                                     PIN_ODR_HIGH(GPIOG_OUT0_ENABLE)         | \
                                     PIN_ODR_HIGH(GPIOG_OUT1_ENABLE)         | \
                                     PIN_ODR_HIGH(GPIOG_OUT2_ENABLE)         | \
                                     PIN_ODR_HIGH(GPIOG_OUT3_ENABLE)         | \
                                     PIN_ODR_HIGH(GPIOG_ICE40_CBSEL0))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_FMC_A10, 12U)         | \
                                     PIN_AFIO_AF(GPIOG_FMC_A11, 12U)         | \
                                     PIN_AFIO_AF(GPIOG_FMC_A12, 12U)         | \
                                     PIN_AFIO_AF(GPIOG_FMC_A13, 12U)         | \
                                     PIN_AFIO_AF(GPIOG_FMC_A14, 12U)         | \
                                     PIN_AFIO_AF(GPIOG_FMC_A15, 12U)         | \
                                     PIN_AFIO_AF(GPIOG_DIP0, 0U)             | \
                                     PIN_AFIO_AF(GPIOG_DIP1, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_DIP2, 0U)             | \
                                     PIN_AFIO_AF(GPIOG_FMC_NE2, 12U)         | \
                                     PIN_AFIO_AF(GPIOG_SD_DETECT, 0U)        | \
                                     PIN_AFIO_AF(GPIOG_OUT0_ENABLE, 0U)      | \
                                     PIN_AFIO_AF(GPIOG_OUT1_ENABLE, 0U)      | \
                                     PIN_AFIO_AF(GPIOG_OUT2_ENABLE, 0U)      | \
                                     PIN_AFIO_AF(GPIOG_OUT3_ENABLE, 0U)      | \
                                     PIN_AFIO_AF(GPIOG_ICE40_CBSEL0, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - OUT0_NFAULT               (input floating).
 * PH3  - OUT1_NFAULT               (input floating).
 * PH4  - I2C2_SCL                  (alternate 4).
 * PH5  - I2C2_SDA                  (alternate 4).
 * PH6  - ENCODER_A                 (alternate 9).
 * PH7  - ICE40_CDONE               (input floating).
 * PH8  - ICE40_RESET               (output opendrain, low).
 * PH9  - ENCODER_B                 (alternate 9).
 * PH10 - LED_R                     (output pushpull, low).
 * PH11 - LED_G                     (output pushpull, low).
 * PH12 - LED_B                     (output pushpull, low).
 * PH13 - ESP32_RESET               (input floating).
 * PH14 - ESP32_GPIO0               (input floating).
 * PH15 - LTC4020_SHUTDOWN          (output pushpull, high).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN)                | \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT)               | \
                                     PIN_MODE_INPUT(GPIOH_OUT0_NFAULT)           | \
                                     PIN_MODE_INPUT(GPIOH_OUT1_NFAULT)           | \
                                     PIN_MODE_ALTERNATE(GPIOH_I2C2_SCL)          | \
                                     PIN_MODE_ALTERNATE(GPIOH_I2C2_SDA)          | \
                                     PIN_MODE_ALTERNATE(GPIOH_ENCODER_A)         | \
                                     PIN_MODE_INPUT(GPIOH_ICE40_CDONE)           | \
                                     PIN_MODE_OUTPUT(GPIOH_ICE40_RESET)          | \
                                     PIN_MODE_ALTERNATE(GPIOH_ENCODER_B)         | \
                                     PIN_MODE_OUTPUT(GPIOH_LED_R)                | \
                                     PIN_MODE_OUTPUT(GPIOH_LED_G)                | \
                                     PIN_MODE_OUTPUT(GPIOH_LED_B)                | \
                                     PIN_MODE_INPUT(GPIOH_ESP32_RESET)           | \
                                     PIN_MODE_INPUT(GPIOH_ESP32_GPIO0)           | \
                                     PIN_MODE_OUTPUT(GPIOH_LTC4020_SHUTDOWN))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN)            | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT)           | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OUT0_NFAULT)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OUT1_NFAULT)       | \
                                     PIN_OTYPE_OPENDRAIN(GPIOH_I2C2_SCL)         | \
                                     PIN_OTYPE_OPENDRAIN(GPIOH_I2C2_SDA)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_ENCODER_A)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_ICE40_CDONE)       | \
                                     PIN_OTYPE_OPENDRAIN(GPIOH_ICE40_RESET)      | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_ENCODER_B)         | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LED_R)             | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LED_G)             | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LED_B)             | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_ESP32_RESET)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_ESP32_GPIO0)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_LTC4020_SHUTDOWN))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN)               | \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT)              | \
                                     PIN_OSPEED_HIGH(GPIOH_OUT0_NFAULT)          | \
                                     PIN_OSPEED_HIGH(GPIOH_OUT1_NFAULT)          | \
                                     PIN_OSPEED_HIGH(GPIOH_I2C2_SCL)             | \
                                     PIN_OSPEED_HIGH(GPIOH_I2C2_SDA)             | \
                                     PIN_OSPEED_HIGH(GPIOH_ENCODER_A)            | \
                                     PIN_OSPEED_HIGH(GPIOH_ICE40_CDONE)          | \
                                     PIN_OSPEED_HIGH(GPIOH_ICE40_RESET)          | \
                                     PIN_OSPEED_HIGH(GPIOH_ENCODER_B)            | \
                                     PIN_OSPEED_HIGH(GPIOH_LED_R)                | \
                                     PIN_OSPEED_HIGH(GPIOH_LED_G)                | \
                                     PIN_OSPEED_HIGH(GPIOH_LED_B)                | \
                                     PIN_OSPEED_HIGH(GPIOH_ESP32_RESET)          | \
                                     PIN_OSPEED_HIGH(GPIOH_ESP32_GPIO0)          | \
                                     PIN_OSPEED_HIGH(GPIOH_LTC4020_SHUTDOWN))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN)            | \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT)           | \
                                     PIN_PUPDR_FLOATING(GPIOH_OUT0_NFAULT)       | \
                                     PIN_PUPDR_FLOATING(GPIOH_OUT1_NFAULT)       | \
                                     PIN_PUPDR_FLOATING(GPIOH_I2C2_SCL)          | \
                                     PIN_PUPDR_FLOATING(GPIOH_I2C2_SDA)          | \
                                     PIN_PUPDR_FLOATING(GPIOH_ENCODER_A)         | \
                                     PIN_PUPDR_FLOATING(GPIOH_ICE40_CDONE)       | \
                                     PIN_PUPDR_FLOATING(GPIOH_ICE40_RESET)       | \
                                     PIN_PUPDR_FLOATING(GPIOH_ENCODER_B)         | \
                                     PIN_PUPDR_FLOATING(GPIOH_LED_R)             | \
                                     PIN_PUPDR_FLOATING(GPIOH_LED_G)             | \
                                     PIN_PUPDR_FLOATING(GPIOH_LED_B)             | \
                                     PIN_PUPDR_FLOATING(GPIOH_ESP32_RESET)       | \
                                     PIN_PUPDR_FLOATING(GPIOH_ESP32_GPIO0)       | \
                                     PIN_PUPDR_FLOATING(GPIOH_LTC4020_SHUTDOWN))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN)                  | \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT)                 | \
                                     PIN_ODR_HIGH(GPIOH_OUT0_NFAULT)             | \
                                     PIN_ODR_HIGH(GPIOH_OUT1_NFAULT)             | \
                                     PIN_ODR_HIGH(GPIOH_I2C2_SCL)                | \
                                     PIN_ODR_HIGH(GPIOH_I2C2_SDA)                | \
                                     PIN_ODR_HIGH(GPIOH_ENCODER_A)               | \
                                     PIN_ODR_HIGH(GPIOH_ICE40_CDONE)             | \
                                     PIN_ODR_LOW(GPIOH_ICE40_RESET)              | \
                                     PIN_ODR_HIGH(GPIOH_ENCODER_B)               | \
                                     PIN_ODR_LOW(GPIOH_LED_R)                    | \
                                     PIN_ODR_LOW(GPIOH_LED_G)                    | \
                                     PIN_ODR_LOW(GPIOH_LED_B)                    | \
                                     PIN_ODR_HIGH(GPIOH_ESP32_RESET)             | \
                                     PIN_ODR_HIGH(GPIOH_ESP32_GPIO0)             | \
                                     PIN_ODR_HIGH(GPIOH_LTC4020_SHUTDOWN))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U)               | \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U)              | \
                                     PIN_AFIO_AF(GPIOH_OUT0_NFAULT, 0U)          | \
                                     PIN_AFIO_AF(GPIOH_OUT1_NFAULT, 0)           | \
                                     PIN_AFIO_AF(GPIOH_I2C2_SCL, 4U)             | \
                                     PIN_AFIO_AF(GPIOH_I2C2_SDA, 4U)             | \
                                     PIN_AFIO_AF(GPIOH_ENCODER_A, 9U)            | \
                                     PIN_AFIO_AF(GPIOH_ICE40_CDONE, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_ICE40_RESET, 0U)          | \
                                     PIN_AFIO_AF(GPIOH_ENCODER_B, 9U)            | \
                                     PIN_AFIO_AF(GPIOH_LED_R, 0U)                | \
                                     PIN_AFIO_AF(GPIOH_LED_G, 0U)                | \
                                     PIN_AFIO_AF(GPIOH_LED_B, 0U)                | \
                                     PIN_AFIO_AF(GPIOH_ESP32_RESET, 0U)          | \
                                     PIN_AFIO_AF(GPIOH_ESP32_GPIO0, 0U)          | \
                                     PIN_AFIO_AF(GPIOH_LTC4020_SHUTDOWN, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - SPI2_NSS                  (alternate 5).
 * PI1  - SPI2_SCK                  (alternate 5).
 * PI2  - SPI2_MISO                 (alternate 5).
 * PI3  - SPI2_MOSI                 (alternate 5).
 * PI4  - SAI2_MCLK_A               (alternate 10).
 * PI5  - SAI2_SCK_A                (alternate 10).
 * PI6  - SAI2_SD_A                 (alternate 10).
 * PI7  - SAI2_FS_A                 (alternate 10).
 * PI8  - CODEC_RESET               (output pushpull, low).
 * PI9  - OUT2_NFAULT               (input floating).
 * PI10 - OUT3_NFAULT               (input floating).
 * PI11 - 5V_DISABLE                (output pushpull, high).
 * PI12 - PIN12                     (input floating).
 * PI13 - PIN13                     (input floating).
 * PI14 - PIN14                     (input floating).
 * PI15 - PIN15                     (input floating).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_ALTERNATE(GPIOI_SPI2_NSS)    | \
                                     PIN_MODE_ALTERNATE(GPIOI_SPI2_SCK)    | \
                                     PIN_MODE_ALTERNATE(GPIOI_SPI2_MISO)   | \
                                     PIN_MODE_ALTERNATE(GPIOI_SPI2_MOSI)   | \
                                     PIN_MODE_ALTERNATE(GPIOI_SAI2_MCLK_A) | \
                                     PIN_MODE_ALTERNATE(GPIOI_SAI2_SCK_A)  | \
                                     PIN_MODE_ALTERNATE(GPIOI_SAI2_SD_A)   | \
                                     PIN_MODE_ALTERNATE(GPIOI_SAI2_FS_A)   | \
                                     PIN_MODE_OUTPUT(GPIOI_CODEC_RESET)    | \
                                     PIN_MODE_INPUT(GPIOI_OUT2_NFAULT)     | \
                                     PIN_MODE_INPUT(GPIOI_OUT3_NFAULT)     | \
                                     PIN_MODE_OUTPUT(GPIOI_5V_DISABLE)     | \
                                     PIN_MODE_INPUT(GPIOI_PIN12)           | \
                                     PIN_MODE_INPUT(GPIOI_PIN13)           | \
                                     PIN_MODE_INPUT(GPIOI_PIN14)           | \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_SPI2_NSS)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SPI2_SCK)    | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SPI2_MISO)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SPI2_MOSI)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SAI2_MCLK_A) | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SAI2_SCK_A)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SAI2_SD_A)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_SAI2_FS_A)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_CODEC_RESET) | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_OUT2_NFAULT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_OUT3_NFAULT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_5V_DISABLE)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14)       | \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_SPI2_NSS)       | \
                                     PIN_OSPEED_HIGH(GPIOI_SPI2_SCK)       | \
                                     PIN_OSPEED_HIGH(GPIOI_SPI2_MISO)      | \
                                     PIN_OSPEED_HIGH(GPIOI_SPI2_MOSI)      | \
                                     PIN_OSPEED_HIGH(GPIOI_SAI2_MCLK_A)    | \
                                     PIN_OSPEED_HIGH(GPIOI_SAI2_SCK_A)     | \
                                     PIN_OSPEED_HIGH(GPIOI_SAI2_SD_A)      | \
                                     PIN_OSPEED_HIGH(GPIOI_SAI2_FS_A)      | \
                                     PIN_OSPEED_HIGH(GPIOI_CODEC_RESET)    | \
                                     PIN_OSPEED_HIGH(GPIOI_OUT2_NFAULT)    | \
                                     PIN_OSPEED_HIGH(GPIOI_OUT3_NFAULT)    | \
                                     PIN_OSPEED_HIGH(GPIOI_5V_DISABLE)     | \
                                     PIN_OSPEED_HIGH(GPIOI_PIN12)          | \
                                     PIN_OSPEED_HIGH(GPIOI_PIN13)          | \
                                     PIN_OSPEED_HIGH(GPIOI_PIN14)          | \
                                     PIN_OSPEED_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_FLOATING(GPIOI_SPI2_NSS)    | \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_SCK)    | \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_MISO)   | \
                                     PIN_PUPDR_FLOATING(GPIOI_SPI2_MOSI)   | \
                                     PIN_PUPDR_FLOATING(GPIOI_SAI2_MCLK_A) | \
                                     PIN_PUPDR_FLOATING(GPIOI_SAI2_SCK_A)  | \
                                     PIN_PUPDR_FLOATING(GPIOI_SAI2_SD_A)   | \
                                     PIN_PUPDR_FLOATING(GPIOI_SAI2_FS_A)   | \
                                     PIN_PUPDR_FLOATING(GPIOI_CODEC_RESET) | \
                                     PIN_PUPDR_FLOATING(GPIOI_OUT2_NFAULT) | \
                                     PIN_PUPDR_FLOATING(GPIOI_OUT3_NFAULT) | \
                                     PIN_PUPDR_FLOATING(GPIOI_5V_DISABLE)  | \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN12)       | \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN13)       | \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN14)       | \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_SPI2_NSS)          | \
                                     PIN_ODR_HIGH(GPIOI_SPI2_SCK)          | \
                                     PIN_ODR_HIGH(GPIOI_SPI2_MISO)         | \
                                     PIN_ODR_HIGH(GPIOI_SPI2_MOSI)         | \
                                     PIN_ODR_HIGH(GPIOI_SAI2_MCLK_A)       | \
                                     PIN_ODR_HIGH(GPIOI_SAI2_SCK_A)        | \
                                     PIN_ODR_HIGH(GPIOI_SAI2_SD_A)         | \
                                     PIN_ODR_HIGH(GPIOI_SAI2_FS_A)         | \
                                     PIN_ODR_LOW(GPIOI_CODEC_RESET)        | \
                                     PIN_ODR_HIGH(GPIOI_OUT2_NFAULT)       | \
                                     PIN_ODR_HIGH(GPIOI_OUT3_NFAULT)       | \
                                     PIN_ODR_HIGH(GPIOI_5V_DISABLE)        | \
                                     PIN_ODR_HIGH(GPIOI_PIN12)             | \
                                     PIN_ODR_HIGH(GPIOI_PIN13)             | \
                                     PIN_ODR_HIGH(GPIOI_PIN14)             | \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_SPI2_NSS, 5U)       | \
                                     PIN_AFIO_AF(GPIOI_SPI2_SCK, 5U)       | \
                                     PIN_AFIO_AF(GPIOI_SPI2_MISO, 5U)      | \
                                     PIN_AFIO_AF(GPIOI_SPI2_MOSI, 5U)      | \
                                     PIN_AFIO_AF(GPIOI_SAI2_MCLK_A, 10U)   | \
                                     PIN_AFIO_AF(GPIOI_SAI2_SCK_A, 10U)    | \
                                     PIN_AFIO_AF(GPIOI_SAI2_SD_A, 10U)     | \
                                     PIN_AFIO_AF(GPIOI_SAI2_FS_A, 10U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_CODEC_RESET, 0U)    | \
                                     PIN_AFIO_AF(GPIOI_OUT2_NFAULT, 0U)    | \
                                     PIN_AFIO_AF(GPIOI_OUT3_NFAULT, 0U)    | \
                                     PIN_AFIO_AF(GPIOI_5V_DISABLE, 0U)     | \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U)          | \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U)          | \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U)          | \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*
 * GPIOJ setup:
 *
 * PJ0  - PIN0                      (input floating).
 * PJ1  - PIN1                      (input floating).
 * PJ2  - PIN2                      (input floating).
 * PJ3  - PIN3                      (input floating).
 * PJ4  - PIN4                      (input floating).
 * PJ5  - PIN5                      (input floating).
 * PJ6  - PIN6                      (input floating).
 * PJ7  - PIN7                      (input floating).
 * PJ8  - PIN8                      (input floating).
 * PJ9  - PIN9                      (input floating).
 * PJ10 - PIN10                     (input floating).
 * PJ11 - PIN11                     (input floating).
 * PJ12 - PIN12                     (input floating).
 * PJ13 - PIN13                     (input floating).
 * PJ14 - PIN14                     (input floating).
 * PJ15 - PIN15                     (input floating).
 */
#define VAL_GPIOJ_MODER             (PIN_MODE_INPUT(GPIOJ_PIN0)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN1)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN2)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN3)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN4)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN5)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN6)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN7)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN8)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN9)       | \
                                     PIN_MODE_INPUT(GPIOJ_PIN10)      | \
                                     PIN_MODE_INPUT(GPIOJ_PIN11)      | \
                                     PIN_MODE_INPUT(GPIOJ_PIN12)      | \
                                     PIN_MODE_INPUT(GPIOJ_PIN13)      | \
                                     PIN_MODE_INPUT(GPIOJ_PIN14)      | \
                                     PIN_MODE_INPUT(GPIOJ_PIN15))
#define VAL_GPIOJ_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOJ_PIN0)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN1)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN2)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN3)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN4)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN5)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN6)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN7)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN8)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN9)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN10)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN11)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN12)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN13)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN14)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN15))
#define VAL_GPIOJ_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOJ_PIN0)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN1)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN2)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN3)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN4)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN5)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN6)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN7)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN8)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN9)   | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN10)  | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN11)  | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN12)  | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN13)  | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN14)  | \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN15))
#define VAL_GPIOJ_PUPDR             (PIN_PUPDR_FLOATING(GPIOJ_PIN0)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN1)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN2)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN3)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN4)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN5)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN6)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN7)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN8)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN9)   | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN10)  | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN11)  | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN12)  | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN13)  | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN14)  | \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN15))
#define VAL_GPIOJ_ODR               (PIN_ODR_HIGH(GPIOJ_PIN0)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN1)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN2)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN3)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN4)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN5)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN6)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN7)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN8)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN9)         | \
                                     PIN_ODR_HIGH(GPIOJ_PIN10)        | \
                                     PIN_ODR_HIGH(GPIOJ_PIN11)        | \
                                     PIN_ODR_HIGH(GPIOJ_PIN12)        | \
                                     PIN_ODR_HIGH(GPIOJ_PIN13)        | \
                                     PIN_ODR_HIGH(GPIOJ_PIN14)        | \
                                     PIN_ODR_HIGH(GPIOJ_PIN15))
#define VAL_GPIOJ_AFRL              (PIN_AFIO_AF(GPIOJ_PIN0, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN1, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN2, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN3, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN4, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN5, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN6, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN7, 0U))
#define VAL_GPIOJ_AFRH              (PIN_AFIO_AF(GPIOJ_PIN8, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN9, 0U)      | \
                                     PIN_AFIO_AF(GPIOJ_PIN10, 0U)     | \
                                     PIN_AFIO_AF(GPIOJ_PIN11, 0U)     | \
                                     PIN_AFIO_AF(GPIOJ_PIN12, 0U)     | \
                                     PIN_AFIO_AF(GPIOJ_PIN13, 0U)     | \
                                     PIN_AFIO_AF(GPIOJ_PIN14, 0U)     | \
                                     PIN_AFIO_AF(GPIOJ_PIN15, 0U))

/*
 * GPIOK setup:
 *
 * PK0  - PIN0                      (input floating).
 * PK1  - PIN1                      (input floating).
 * PK2  - PIN2                      (input floating).
 * PK3  - PIN3                      (input floating).
 * PK4  - PIN4                      (input floating).
 * PK5  - PIN5                      (input floating).
 * PK6  - PIN6                      (input floating).
 * PK7  - PIN7                      (input floating).
 * PK8  - PIN8                      (input floating).
 * PK9  - PIN9                      (input floating).
 * PK10 - PIN10                     (input floating).
 * PK11 - PIN11                     (input floating).
 * PK12 - PIN12                     (input floating).
 * PK13 - PIN13                     (input floating).
 * PK14 - PIN14                     (input floating).
 * PK15 - PIN15                     (input floating).
 */
#define VAL_GPIOK_MODER             (PIN_MODE_INPUT(GPIOK_PIN0)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN1)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN2)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN3)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN4)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN5)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN6)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN7)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN8)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN9)       | \
                                     PIN_MODE_INPUT(GPIOK_PIN10)      | \
                                     PIN_MODE_INPUT(GPIOK_PIN11)      | \
                                     PIN_MODE_INPUT(GPIOK_PIN12)      | \
                                     PIN_MODE_INPUT(GPIOK_PIN13)      | \
                                     PIN_MODE_INPUT(GPIOK_PIN14)      | \
                                     PIN_MODE_INPUT(GPIOK_PIN15))
#define VAL_GPIOK_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOK_PIN0)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN1)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN2)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN3)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN4)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN5)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN6)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN7)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN8)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN9)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN10)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN11)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN12)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN13)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN14)  | \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN15))
#define VAL_GPIOK_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOK_PIN0)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN1)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN2)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN3)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN4)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN5)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN6)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN7)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN8)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN9)   | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN10)  | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN11)  | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN12)  | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN13)  | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN14)  | \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN15))
#define VAL_GPIOK_PUPDR             (PIN_PUPDR_FLOATING(GPIOK_PIN0)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN1)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN2)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN3)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN4)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN5)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN6)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN7)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN8)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN9)   | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN10)  | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN11)  | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN12)  | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN13)  | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN14)  | \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN15))
#define VAL_GPIOK_ODR               (PIN_ODR_HIGH(GPIOK_PIN0)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN1)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN2)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN3)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN4)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN5)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN6)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN7)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN8)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN9)         | \
                                     PIN_ODR_HIGH(GPIOK_PIN10)        | \
                                     PIN_ODR_HIGH(GPIOK_PIN11)        | \
                                     PIN_ODR_HIGH(GPIOK_PIN12)        | \
                                     PIN_ODR_HIGH(GPIOK_PIN13)        | \
                                     PIN_ODR_HIGH(GPIOK_PIN14)        | \
                                     PIN_ODR_HIGH(GPIOK_PIN15))
#define VAL_GPIOK_AFRL              (PIN_AFIO_AF(GPIOK_PIN0, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN1, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN2, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN3, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN4, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN5, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN6, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN7, 0U))
#define VAL_GPIOK_AFRH              (PIN_AFIO_AF(GPIOK_PIN8, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN9, 0U)      | \
                                     PIN_AFIO_AF(GPIOK_PIN10, 0U)     | \
                                     PIN_AFIO_AF(GPIOK_PIN11, 0U)     | \
                                     PIN_AFIO_AF(GPIOK_PIN12, 0U)     | \
                                     PIN_AFIO_AF(GPIOK_PIN13, 0U)     | \
                                     PIN_AFIO_AF(GPIOK_PIN14, 0U)     | \
                                     PIN_AFIO_AF(GPIOK_PIN15, 0U))

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
