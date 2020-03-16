################################################################################
# Files and include directories for the nordic SDK                             #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

NORDIC_DIR       := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
NORDIC_RULES_DIR := $(NORDIC_DIR)/rules

ifeq ($(MODULES_DIR),)
    MODULES_DIR  := $(realpath $(NORDIC_DIR)/..)
endif

ifeq ($(NORDIC_SDK),)
    $(error NORDIC_SDK must be set to the nrf51-sdk directory)
endif

NORDIC_SDK_COMPONENTS   := $(realpath $(NORDIC_SDK)/components)
NORDIC_SDK_EXTERNAL     := $(realpath $(NORDIC_SDK)/external)
NORDIC_SDK_DRIVERS_NRF  := $(realpath $(NORDIC_SDK_COMPONENTS)/drivers_nrf)
NORDIC_SDK_DEVICE       := $(realpath $(NORDIC_SDK_COMPONENTS)/device)
NORDIC_SDK_LIBRARIES    := $(realpath $(NORDIC_SDK_COMPONENTS)/libraries)
NORDIC_SDK_TOOLCHAIN    := $(realpath $(NORDIC_SDK_COMPONENTS)/toolchain)
NORDIC_SDK_SER          := $(realpath $(NORDIC_SDK_COMPONENTS)/serialization)
NORDIC_SDK_SOFTDEVICE   := $(realpath $(NORDIC_SDK_COMPONENTS)/softdevice)
NORDIC_SDK_BLE          := $(realpath $(NORDIC_SDK_COMPONENTS)/ble)

# --- STANDARD LIBRARY ------------------------------------------------------- #

# need for 'substr', 'uc'
include $(MODULES_DIR)/support/gmsl

# --- CONFIGURATION ---------------------------------------------------------- #

NORDIC_DEVICES := nrf51422 nrf51822 \
                  nrf52832

ifeq ($(filter $(NORDIC_DEVICE), $(NORDIC_DEVICES)),)
    $(error NORDIC_DEVICE=$(NORDIC_DEVICE) is not a valid device. Should be one of [$(NORDIC_DEVICES)])
endif

NORDIC_FAMILY     := $(call substr,$(NORDIC_DEVICE),1,5)

NORDIC_nrf51_VARS := xxaa xxab xxac
NORDIC_nrf51_SDS  := blank s130
NORDIC_nrf51_MCU  := cortex-m0

NORDIC_nrf52_VARS := xxaa
NORDIC_nrf52_SDS  := blank s132
NORDIC_nrf52_MCU  := cortex-m4

NORDIC_VARS       := $(NORDIC_$(NORDIC_FAMILY)_VARS)
NORDIC_SDS        := $(NORDIC_$(NORDIC_FAMILY)_SDS)
NORDIC_MCU        := $(NORDIC_$(NORDIC_FAMILY)_MCU)

ifeq ($(filter $(NORDIC_VAR), $(NORDIC_VARS)),)
    $(error NORDIC_VAR=$(NORDIC_VAR) is not a valid variant of $(NORDIC_DEVICE). Should be one of [$(NORDIC_VARS)])
endif

ifeq ($(NORDIC_SD),)
    NORDIC_SD := blank
endif
ifeq ($(filter $(NORDIC_SD), $(NORDIC_SDS)),)
    $(error NORDIC_SD=$(NORDIC_SD) is not a valid softdevice for $(NORDIC_DEVICE). Should be one of [$(NORDIC_SDS)], or unset)
endif

ifeq ($(NORDIC_USE_BLE),yes)
    ifeq ($(NORDIC_SD),blank)
        $(error Enabling BLE requires a softdevice)
    endif
endif

ifneq ($(NORDIC_SD),blank)
    NORDIC_USE_BLE := yes
endif

# --- VARIABLES -------------------------------------------------------------- #

NORDIC_SRC         :=
NORDIC_INC         :=
NORDIC_ASM         :=
NORDIC_ASX         :=
NORDIC_DEF         :=
NORDIC_LIBDIR      :=

NORDIC_TESTSUPPORT :=
NORDIC_TESTDEF     :=

# --- DEFINITIONS ------------------------------------------------------------ #

NORDIC_DEVICE_DEF := $(call uc, $(NORDIC_DEVICE)_$(NORDIC_VAR))

NORDIC_DEF += $(NORDIC_DEVICE_DEF)

ifeq ($(NORDIC_USE_BLE), yes)
    NORDIC_DEF += BLE_STACK_SUPPORT_REQD
endif

ifneq ($(NORDIC_SD),blank)
    NORDIC_SD_DEF := $(call uc, $(NORDIC_SD))
    NORDIC_DEF += $(NORDIC_SD_DEF)
    NORDIC_DEF += SOFTDEVICE_PRESENT
endif

NORDIC_DEF += NRF_SD_BLE_API_VERSION=5

# --- LINKER SCRIPT ---------------------------------------------------------- #

NORDIC_LD_SCRIPT := $(NORDIC_RULES_DIR)/$(NORDIC_FAMILY)_$(NORDIC_VAR)_$(NORDIC_SD).ld
NORDIC_LIBDIR    := $(dir $(NORDIC_LD_SCRIPT))

# --- SOFTDEVICE ------------------------------------------------------------- #

ifneq ($(NORDIC_SD),blank)
    NORDIC_SOFTDEVICE := $(wildcard $(NORDIC_SDK_SOFTDEVICE)/$(NORDIC_SD)/hex/*.hex)
endif

# --- CORE MODULES ----------------------------------------------------------- #

# NOTE: Incomplete list, add as necessary

# System
NORDIC_INC += $(NORDIC_SDK_TOOLCHAIN)
NORDIC_INC += $(NORDIC_SDK_DEVICE)
NORDIC_INC += $(NORDIC_SDK_TOOLCHAIN)/cmsis/include
NORDIC_SRC += $(NORDIC_SDK_TOOLCHAIN)/system_$(NORDIC_FAMILY).c
NORDIC_ASX += $(NORDIC_SDK_TOOLCHAIN)/gcc/gcc_startup_$(NORDIC_FAMILY).S

# Softdevice Integration
ifeq ($(NORDIC_SD),blank)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/nrf_soc_nosd
else
    NORDIC_INC += $(NORDIC_SDK_SOFTDEVICE)/$(NORDIC_SD)/headers
    NORDIC_INC += $(NORDIC_SDK_SOFTDEVICE)/common/
    NORDIC_SRC += $(NORDIC_SDK_SOFTDEVICE)/common/nrf_sdh.c
    NORDIC_SRC += $(NORDIC_SDK_SOFTDEVICE)/common/nrf_sdh_ble.c
endif

# --- LIBRARY MODULES -------------------------------------------------------- #

# Utilities
NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/util
NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/util/app_error.c
NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/util/app_error_weak.c
NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/util/app_util_platform.c
NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/util/nrf_assert.c

# Atomic integers
ifeq ($(NORDIC_USE_APP_ATOMIC),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/atomic
endif

# balloc
ifeq ($(NORDIC_USE_APP_BALLOC),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/balloc
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/balloc/nrf_balloc.c
endif

# BSP
ifeq ($(NORDIC_USE_BSP),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/bsp
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/bsp/bsp.c

    NORDIC_INC += $(NORDIC_SDK_COMPONENTS)/boards
    NORDIC_SRC += $(NORDIC_SDK_COMPONENTS)/boards/boards.c
endif

# Button
ifeq ($(NORDIC_USE_APP_BUTTON),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/button
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/button/app_button.c
endif

# FIFO
ifeq ($(NORDIC_USE_APP_FIFO),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/fifo
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/fifo/app_fifo.c
endif

# Flash storage
ifeq ($(NORDIC_USE_APP_FSTORAGE),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/fstorage
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/fstorage/config
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/fstorage/fstorage.c
else ifeq ($(NORDIC_USE_APP_FSTORAGE),nosd)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/fstorage
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/fstorage/fstorage_nosd.c
endif

# Log
ifeq ($(NORDIC_USE_APP_LOG),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/experimental_log
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/experimental_log/src
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/experimental_log/src/nrf_log_frontend.c
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/experimental_log/src/nrf_log_default_backends.c
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/experimental_log/src/nrf_log_backend_uart.c
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/experimental_log/src/nrf_log_backend_serial.c
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/experimental_log/src/nrf_log_str_formatter.c
endif

# Linker section variables
ifeq ($(NORDIC_USE_APP_SECTION_VARS),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/experimental_section_vars
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/experimental_section_vars/nrf_section_iter.c
endif

# Memobj
ifeq ($(NORDIC_USE_APP_MEMOBJ),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/experimental_memobj
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/experimental_memobj/nrf_memobj.c
endif

# strerror
ifeq ($(NORDIC_USE_APP_STRERROR),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/strerror
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/strerror/nrf_strerror.c
endif

# Timer
ifeq ($(NORDIC_USE_APP_TIMER),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/timer
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/timer/app_timer.c
endif

# UART
ifeq ($(NORDIC_USE_APP_UART),yes)
    NORDIC_INC += $(NORDIC_SDK_LIBRARIES)/uart
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/uart/app_uart.c
    NORDIC_SRC += $(NORDIC_SDK_LIBRARIES)/uart/retarget.c
endif

# --- DRIVER MODULES --------------------------------------------------------- #

# Driver common
NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/common
NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/common/nrf_drv_common.c

# HAL
NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/hal
NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/hal/nrf_ecb.c
NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/hal/nrf_nvmc.c

# ADC
ifeq ($(NORDIC_USE_DRV_ADC),yes)
    ifeq ($(NORDIC_FAMILY),nrf52)
        $(error adc not supported on nrf52, use saadc instead)
    endif
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/adc
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/adc/nrf_drv_adc.c
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/hal/nrf_adc.c
endif

# Flash modification
ifeq ($(NORDIC_USE_DRV_BLE_FLASH),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/ble_flash
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/ble_flash/ble_flash.c
endif

# Clock
ifeq ($(NORDIC_USE_DRV_CLOCK),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/clock
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/clock/nrf_drv_clock.c
endif

# Comparator
ifeq ($(NORDIC_USE_DRV_COMP),yes)
    ifeq ($(NORDIC_FAMILY),nrf51)
        $(error comp not supported on nrf51, use lpcomp)
    endif
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/comp
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/comp/nrf_drv_comp.c
endif

# Polled delay
ifeq ($(NORDIC_USE_DRV_DELAY),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/delay
endif

# GPIOTE
ifeq ($(NORDIC_USE_DRV_GPIOTE),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/gpiote
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/gpiote/nrf_drv_gpiote.c
endif

# I2S
ifeq ($(NORDIC_USE_DRV_I2S),yes)
    ifeq ($(NORDIC_FAMILY),nrf51)
        $(error i2s not supported on nrf51)
    endif
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/i2s
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/i2s/nrf_drv_i2s.c
endif

# Low-power comparator
ifeq ($(NORDIC_USE_DRV_LPCOMP),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/lpcomp
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/lpcomp/nrf_drv_lpcomp.c
endif

# Pulse-density-modulation input
ifeq ($(NORDIC_USE_DRV_PDM),yes)
    ifeq ($(NORDIC_FAMILY),nrf51)
        $(error pdm not supported on nrf51)
    endif
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/pdm
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/pdm/nrf_drv_pdm.c
endif

# Peripheral interconnect
ifeq ($(NORDIC_USE_DRV_LPCOMP),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/ppi
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/ppi/nrf_drv_ppi.c
endif

# Persistent storage
ifeq ($(NORDIC_USE_DRV_PSTORAGE),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/pstorage
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/pstorage/pstorage.c
else ifeq ($(NORDIC_USE_DRV_PSTORAGE),nosd)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/pstorage
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/pstorage/pstorage_nosd.c
else ifeq ($(NORDIC_USE_DRV_PSTORAGE),raw)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/pstorage
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/pstorage/pstorage_nosd.c
endif

# Pulse-width modulation output
ifeq ($(NORDIC_USE_DRV_PWM),yes)
    ifeq ($(NORDIC_FAMILY),nrf51)
        $(error pwm not supported on nrf51)
    endif
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/pwm
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/pwm/nrf_drv_pwm.c
endif

# Quadrature decoder
ifeq ($(NORDIC_USE_DRV_QDEC),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/qdec
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/qdec/nrf_drv_qdec.c
endif

# Random number generator
ifeq ($(NORDIC_USE_DRV_RNG),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/rng
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/rng/nrf_drv_rng.c
endif

# Real-time clock
ifeq ($(NORDIC_USE_DRV_RTC),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/rtc
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/rtc/nrf_drv_rtc.c
endif

# SAADC
ifeq ($(NORDIC_USE_DRV_SAADC),yes)
    ifeq ($(NORDIC_FAMILY),nrf51)
        $(error saadc not supported on nrf51, use adc instead)
    endif
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/saadc
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/saadc/nrf_drv_saadc.c
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/hal/nrf_saadc.c
endif

# SPI master
ifeq ($(NORDIC_USE_DRV_SPI_MASTER),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/spi_master
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/spi_master/nrf_drv_spi.c
endif

# SPI slave
ifeq ($(NORDIC_USE_DRV_SPI_SLAVE),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/spi_slave
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/spi_slave/nrf_drv_spis.c
endif

# Software interrupts
ifeq ($(NORDIC_USE_DRV_SWI),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/swi
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/swi/nrf_drv_swi.c
endif

# Timer
ifeq ($(NORDIC_USE_DRV_TIMER),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/timer
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/timer/nrf_drv_timer.c
endif

# Two-wire (I2C) master
ifeq ($(NORDIC_USE_DRV_TWI_MASTER),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/twi_master
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/twi_master/nrf_drv_twi.c
endif

# Two-wire (I2C) slave
ifeq ($(NORDIC_USE_DRV_TWI_SLAVE),yes)
    ifeq ($(NORDIC_FAMILY),nrf51)
        $(error twi slave not supported on nrf51)
    endif
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/twis_slave
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/twis_slave/nrf_drv_twis.c
endif

# UART
ifeq ($(NORDIC_USE_DRV_UART),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/uart
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/uart/nrf_drv_uart.c
endif

# Watchdog timer
ifeq ($(NORDIC_USE_DRV_WDT),yes)
    NORDIC_INC += $(NORDIC_SDK_DRIVERS_NRF)/wdt
    NORDIC_SRC += $(NORDIC_SDK_DRIVERS_NRF)/wdt/nrf_drv_wdt.c
endif

# --- EXTERNAL MODULES ------------------------------------------------------- #

# fprintf
ifeq ($(NORDIC_USE_EXT_FPRINTF),yes)
    NORDIC_INC += $(NORDIC_SDK_EXTERNAL)/fprintf
    NORDIC_SRC += $(NORDIC_SDK_EXTERNAL)/fprintf/nrf_fprintf.c
    NORDIC_SRC += $(NORDIC_SDK_EXTERNAL)/fprintf/nrf_fprintf_format.c
endif

# --- BLE MODULES ------------------------------------------------------------ #

# TODO: Allow proper configuration for central/peripheral
#
# For now, just assume we'll always be in a peripheral role

ifeq ($(NORDIC_USE_BLE),yes)
    NORDIC_INC += $(NORDIC_SDK_BLE)/common

    NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_db_discovery/ble_db_discovery.c
    NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_dtm/ble_dtm.c
    NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_racp/ble_racp.c
    NORDIC_SRC += $(NORDIC_SDK_BLE)/common/ble_advdata.c
    NORDIC_SRC += $(NORDIC_SDK_BLE)/common/ble_conn_params.c
    NORDIC_SRC += $(NORDIC_SDK_BLE)/common/ble_srv_common.c

    # Battery service
    ifeq ($(NORDIC_USE_BLE_SRV_BAS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_bas
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_bas/ble_bas.c
    endif

    # Blood Pressure service
    ifeq ($(NORDIC_USE_BLE_SRV_BPS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_bps
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_bps/ble_bps.c
    endif

    # Cycle speed/cadence service
    ifeq ($(NORDIC_USE_BLE_SRV_CSCS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_cscs
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_cscs/ble_cscs.c
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_cscs/ble_sc_ctrlpt.c
    endif

    # Direct File Upload service
    ifeq ($(NORDIC_USE_BLE_SRV_DFU),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_dfu
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_dfu/ble_dfu.c
    endif

    # Device Information service
    ifeq ($(NORDIC_USE_BLE_SRV_DIS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_dis
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_dis/ble_dis.c
    endif

    # Glucose service
    ifeq ($(NORDIC_USE_BLE_SRV_GLS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_gls
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_gls/ble_gls.c
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_gls/ble_gls_db.c
    endif

    # Human Interface Device service
    ifeq ($(NORDIC_USE_BLE_SRV_HIDS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_hids
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_hids/ble_hids.c
    endif

    # Heart Rate service
    ifeq ($(NORDIC_USE_BLE_SRV_HRS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_hrs
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_hrs/ble_hrs.c
    endif

    # Health Thermometer service
    ifeq ($(NORDIC_USE_BLE_SRV_HTS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_hts
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_hts/ble_hts.c
    endif

    # Immediate Alert service
    ifeq ($(NORDIC_USE_BLE_SRV_IAS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_ias
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_ias/ble_ias.c
    endif

    # LED/Button service
    ifeq ($(NORDIC_USE_BLE_SRV_LBS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_lbs
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_lbs/ble_lbs.c
    endif

    # Link Loss service
    ifeq ($(NORDIC_USE_BLE_SRV_LLS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_lls
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_lls/ble_lls.c
    endif

    # Nordic UART service
    ifeq ($(NORDIC_USE_BLE_SRV_NUS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_nus
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_nus/ble_nus.c
    endif

    # Running Speed and Cadence service
    ifeq ($(NORDIC_USE_BLE_SRV_RSCS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_rscs
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_rscs/ble_rscs.c
    endif

    # TX Power service
    ifeq ($(NORDIC_USE_BLE_SRV_TPS),yes)
        NORDIC_INC += $(NORDIC_SDK_BLE)/ble_services/ble_tps
        NORDIC_SRC += $(NORDIC_SDK_BLE)/ble_services/ble_tps/ble_tps.c
    endif
endif

# --- TEST SUPPORT ----------------------------------------------------------- #

NORDIC_TESTSUPPORT :=
NORDIC_TESTSUPPORT += $(NORDIC_DIR)/test_support
NORDIC_TESTSUPPORT += $(NORDIC_DIR)/test_support/device
NORDIC_TESTSUPPORT += $(NORDIC_DIR)/test_support/cmsis
NORDIC_TESTSUPPORT += $(NORDIC_DIR)/test_support/$(NORDIC_SD)

NORDIC_TESTDEF     :=
NORDIC_TESTDEF     += $(NORDIC_DEF)
NORDIC_TESTDEF     += MOCK_NORDIC
NORDIC_TESTDEF     += SUPPRESS_INLINE_IMPLEMENTATION
NORDIC_TESTDEF     += __STATIC_INLINE=
