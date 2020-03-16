################################################################################
# Board make file                                                              #
# hardware v01                                                                 #
#                                                                              #
# This file provides:                                                          #
# - BOARD_INC               Directories to search for board headers            #
# - BOARD_SRC               Board source files                                 #
# - BOARD_ASM               Board assembly files                               #
# - BOARD_DEF               Board preprocessor definitions                     #
# - BOARD_MCU               ARM Cortex to compile for                          #
################################################################################

# --- BOARD DIRECTORIES ------------------------------------------------------ #

# Board directory is the one this makefile resides in
BOARD_DIR   := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

BOARD_INC_DIR   := $(BOARD_DIR)/inc
BOARD_SRC_DIR   := $(BOARD_DIR)/src

# --- BOARD MCU OPTIONS ------------------------------------------------------ #

BOARD_MCU   := cortex-m7
DEVICE      := STM32F746IG

# Startup files
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_stm32f7xx.mk

# Platform include file
include $(CHIBIOS)/os/hal/ports/STM32/STM32F7xx/platform.mk
include $(CHIBIOS_CONTRIB)/os/hal/ports/STM32/STM32F7xx/platform.mk

# --- BOARD LINKER SCRIPT ---------------------------------------------------- #

LDSCRIPT    := $(BOARD_DIR)/ld/STM32F746xG.ld

# --- BOARD HEADERS ---------------------------------------------------------- #

BOARD_INC   :=
BOARD_INC   += $(BOARD_INC_DIR)

# --- BOARD SOURCES ---------------------------------------------------------- #

BOARD_SRC   :=
BOARD_SRC   += $(BOARD_SRC_DIR)/board.c

# --- BOARD ASSEMBLY --------------------------------------------------------- #

BOARD_ASM   :=

# --- BOARD DEFINITIONS ------------------------------------------------------ #

BOARD_DEF   :=
