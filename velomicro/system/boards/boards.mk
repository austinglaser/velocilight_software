################################################################################
# Boards makefile                                                              #
#                                                                              #
# This file provides:                                                          #
# - BOARDS_INC           Directories to search for Boards headers              #
# - BOARDS_SRC           Boards source files                                   #
# - BOARDS_ASM           Boards assembly files                                 #
# - BOARDS_DEF           Boards preprocessor definitions                       #
# - BOARDS_TEST          Boards test directories                               #
# - BOARDS_TESTDEF       Boards test defines                                   #
# - BOARDS_TESTSUPPORT   Boards test support directories                       #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Boards directory is the one this makefile resides in
BOARDS_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

BOARDS_INC_DIR := $(BOARDS_DIR)/inc

# --- HEADERS ---------------------------------------------------------------- #

BOARDS_INC :=

# --- SOURCES ---------------------------------------------------------------- #

BOARDS_SRC :=

# --- ASSEMBLY --------------------------------------------------------------- #

BOARDS_ASM :=

# --- DEFINITIONS ------------------------------------------------------------ #

BOARDS_DEF :=

# --- TESTS ------------------------------------------------------------------ #

BOARDS_TEST        :=

BOARDS_TESTDEF     :=

BOARDS_TESTSUPPORT :=

# --- BOARD SELECTION -------------------------------------------------------- #

ifeq ($(BOARD_DEV_KIT),nrf51_dk)
    BOARD_MK = $(BOARDS_DIR)/pca10028/board.mk
else ifeq ($(BOARD_DEV_KIT),nrf52_dk)
    BOARD_MK = $(BOARDS_DIR)/pca10040/board.mk
else
    $(error no custom boards yet implemented)
endif

include $(BOARD_MK)

BOARDS_DEVICE      := $(BOARD_DEVICE)
BOARDS_VAR         := $(BOARD_VAR)

BOARDS_INC         += $(BOARD_INC)
BOARDS_SRC         += $(BOARD_SRC)
BOARDS_ASM         += $(BOARD_ASM)
BOARDS_DEF         += $(BOARD_DEF)
BOARDS_TEST        += $(BOARD_TEST)
BOARDS_TESTDEF     += $(BOARD_TESTDEF)
BOARDS_TESTSUPPORT += $(BOARD_TESTSUPORT)
