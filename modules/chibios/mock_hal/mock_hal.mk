################################################################################
# ChibiOS HAL mock makefile                                                    #
#                                                                              #
# Provides a set of headers compatible with CMOCK.                             #
#                                                                              #
# This file provides:                                                          #
# - MOCK_HAL_INC           Directories to search for Hal headers               #
# - MOCK_HAL_SRC           Hal source files                                    #
# - MOCK_HAL_ASM           Hal assembly files                                  #
# - MOCK_HAL_DEF           Hal preprocessor definitions                        #
# - MOCK_HAL_TEST          Hal test directories                                #
# - MOCK_HAL_TESTDEF       Hal test definitions                                #
# - MOCK_HAL_TESTSUPPORT   Hal test support directories                        #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# MockHal directory is the one this makefile resides in
MOCK_HAL_DIR		:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

MOCK_HAL_INC_DIR	:= $(MOCK_HAL_DIR)/inc
MOCK_HAL_LLD_DIR	:= $(MOCK_HAL_DIR)/lld
MOCK_HAL_OSAL_DIR	:= $(MOCK_HAL_DIR)/osal

# --- HEADERS ---------------------------------------------------------------- #

MOCK_HAL_INC		:=

# --- SOURCES ---------------------------------------------------------------- #

MOCK_HAL_SRC		:=

# --- ASSEMBLY --------------------------------------------------------------- #

MOCK_HAL_ASM		:=

# --- DEFINITIONS ------------------------------------------------------------ #

MOCK_HAL_DEF		:=

# --- TESTS ------------------------------------------------------------------ #

MOCK_HAL_TEST		:=

MOCK_HAL_TESTDEF	:=
MOCK_HAL_TESTDEF	+= MOCK_HAL

MOCK_HAL_TESTSUPPORT	:=
MOCK_HAL_TESTSUPPORT	+= $(MOCK_HAL_INC_DIR)
MOCK_HAL_TESTSUPPORT	+= $(MOCK_HAL_LLD_DIR)
MOCK_HAL_TESTSUPPORT	+= $(MOCK_HAL_OSAL_DIR)

MOCK_HAL_TESTHELPERS	:=
