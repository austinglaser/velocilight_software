################################################################################
# Top-level makefile                                                           #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

ROOT_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
UPPER_DIR := $(realpath $(ROOT_DIR)/..)

NORDIC_SDK  := $(UPPER_DIR)/nrf5-sdk
MODULES_DIR := $(UPPER_DIR)/modules
COMMON_DIR  := $(UPPER_DIR)/common
SUPPORT_DIR := $(ROOT_DIR)/support
SYSTEM_DIR  := $(ROOT_DIR)/system
BUILD_DIR   := $(ROOT_DIR)/build

# --- PROJECT INFO ----------------------------------------------------------- #

PROJECT := velomicro

# --- BOARD CONFIGURATION ---------------------------------------------------- #

BOARD_DEV_KIT := nrf52_dk

include $(SYSTEM_DIR)/boards/boards.mk

# --- NORDIC CONFIGURATION --------------------------------------------------- #

NORDIC_DEVICE           := $(BOARDS_DEVICE)
NORDIC_VAR              := $(BOARDS_VAR)
NORDIC_SD               := s132

NORDIC_USE_BSP          := yes

NORDIC_USE_APP_ATOMIC   := yes
NORDIC_USE_APP_BALLOC   := yes
NORDIC_USE_APP_BUTTON   := yes
NORDIC_USE_APP_FIFO     := yes
NORDIC_USE_APP_LOG      := yes
NORDIC_USE_APP_MEMOBJ   := yes
NORDIC_USE_APP_SECTION_VARS := yes
NORDIC_USE_APP_STRERROR := yes
NORDIC_USE_APP_TIMER    := yes

NORDIC_USE_DRV_DELAY    := yes
NORDIC_USE_DRV_GPIOTE   := yes
NORDIC_USE_DRV_SPI_MASTER := yes
NORDIC_USE_DRV_TWI_MASTER := yes
NORDIC_USE_DRV_UART     := yes

NORDIC_USE_EXT_FPRINTF  := yes

NORDIC_USE_BLE          := yes

include $(MODULES_DIR)/nordic/nordic.mk

# --- MODULES CONFIGURATION -------------------------------------------------- #

USE_NORDIC_IMPLEMENTATION := yes

USE_C_EXCEPTION := yes
USE_COLOR       := yes
USE_ENSURE      := yes
USE_ERROR       := yes
USE_RGB_LED     := yes
USE_UTIL        := yes

USE_MPU9250     := yes

include $(MODULES_DIR)/modules.mk

# --- COMMON LIBRARIES ------------------------------------------------------- #

include $(COMMON_DIR)/perlin/perlin.mk

# --- PROJECT SECTIONS ------------------------------------------------------- #

include $(SYSTEM_DIR)/app/app.mk
include $(SYSTEM_DIR)/drivers/drivers.mk

# --- RULES CONFIGURATION ---------------------------------------------------- #

MCU        := $(NORDIC_MCU)
DEVICE     := $(NORDIC_DEVICE)
VARIANT    := $(NORDIC_VAR)
SOFTDEVICE := $(NORDIC_SOFTDEVICE)
LD_SCRIPT  := $(BOARD_LD_SCRIPT)

CSRC       := $(MODULES_SRC) \
              $(BOARDS_SRC) \
              $(DRIVERS_SRC) \
              $(PERLIN_SRC) \
              $(APP_SRC)

EXTSRC     := $(NORDIC_SRC)

ASMSRC     := $(NORDIC_ASM) \
              $(MODULES_ASM) \
              $(BOARDS_ASM) \
              $(DRIVERS_ASM) \
              $(PERLIN_ASM) \
              $(APP_ASM)

ASMXSRC    := $(NORDIC_ASX)

INCDIR     := $(MODULES_INC) \
              $(BOARDS_INC) \
              $(DRIVERS_INC) \
              $(PERLIN_INC) \
              $(APP_INC)

EXTINCDIR  := $(NORDIC_INC)

LIBDIR     := $(NORDIC_LIBDIR)

DEFS       := $(NORDIC_DEF) \
              $(MODULES_DEF) \
              $(BOARDS_DEF) \
              $(DRIVERS_DEF) \
              $(PERLIN_DEF) \
              $(APP_DEF) \
              ENSURE_MODE=ENSURE_MODE_OFF

OPT        := -Og \
              -flto \
              -std=gnu11 \
              -ggdb \
              -mfloat-abi=hard \
              -mfpu=fpv4-sp-d16 \
              -fsingle-precision-constant

WARN       := -Wall \
              -Wextra \
              -Wformat=2 \
              -Wshadow \
              -Wwrite-strings \
              -Wredundant-decls \
              -Wnested-externs \
              -Wmissing-include-dirs \
              -Wno-expansion-to-defined \
              -Wno-old-style-declaration \
              -Wno-unused-parameter \
              -Wdouble-promotion \
              -Werror

LDOPT      := ,-lm

# --- RELEASE TARGETS -------------------------------------------------------- #

all: nordic-release
release: nordic-release

include $(NORDIC_RULES_DIR)/rules.mk

# --- TEST CONFIGURATION------------------------------------------------------ #

CEEDLING_BUILDDIR := $(ROOT_DIR)/build_test
TESTBASECONFIG    := $(SUPPORT_DIR)/ceedling.yml

TESTSRC           := $(MODULES_SRC) \
                     $(BOARDS_SRC) \
                     $(DRIVERS_SRC) \
                     $(PERLIN_SRC) \
                     $(APP_SRC)

TESTINC           := $(NORDIC_INC) \
                     $(MODULES_INC) \
                     $(BOARDS_INC) \
                     $(DRIVERS_INC) \
                     $(PERLIN_INC) \
                     $(APP_INC)

TESTTEST          := $(MODULES_TEST) \
                     $(BOARDS_TEST) \
                     $(DRIVERS_TEST) \
                     $(PERLIN_TEST) \
                     $(APP_TEST)

TESTDEF           := $(NORDIC_TESTDEF) \
                     $(MODULES_TESTDEF) \
                     $(BOARDS_TESTDEF) \
                     $(DRIVERS_TESTDEF) \
                     $(PERLIN_TESTDEF) \
                     $(APP_TESTDEF)

TESTSUPPORT       := $(NORDIC_TESTSUPPORT) \
                     $(MODULES_TESTSUPPORT) \
                     $(BOARDS_TESTSUPPORT) \
                     $(DRIVERS_TESTSUPPORT) \
                     $(PERLIN_TESTSUPPORT) \
                     $(APP_TESTSUPPORT)

# --- TEST TARGETS ----------------------------------------------------------- #

test: ceedling-test
coverage: ceedling-coverage
test-clean: ceedling-clean
clean: test-clean

include $(MODULES_DIR)/ceedling/rules.mk
