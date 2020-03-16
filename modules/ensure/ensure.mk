################################################################################
# Ensure makefile                                                              #
#                                                                              #
# This file provides:                                                          #
# - ENSURE_INC           Directories to search for Ensure headers              #
# - ENSURE_SRC           Ensure source files                                   #
# - ENSURE_ASM           Ensure assembly files                                 #
# - ENSURE_DEF           Ensure preprocessor definitions                       #
# - ENSURE_TEST          Ensure test directories                               #
# - ENSURE_TESTDEF       Ensure test defines                                   #
# - ENSURE_TESTSUPPORT   Ensure test support directories                       #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Ensure directory is the one this makefile resides in
ENSURE_DIR  := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

ENSURE_COMMON_DIR  := $(ENSURE_DIR)/common
ENSURE_CHIBIOS_DIR := $(ENSURE_DIR)/chibios

# --- INITIALIZATION --------------------------------------------------------- #

ENSURE_INC         :=
ENSURE_SRC         :=
ENSURE_ASM         :=
ENSURE_DEF         :=
ENSURE_TEST        :=
ENSURE_TESTDEF     :=
ENSURE_TESTSUPPORT :=
ENSURE_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

ENSURE_INC         += $(ENSURE_COMMON_DIR)/inc
ENSURE_SRC         += $(ENSURE_COMMON_DIR)/src/ensure_c_exception.c
ENSURE_TEST        += $(ENSURE_COMMON_DIR)/test
ENSURE_TESTSUPPORT += $(ENSURE_COMMON_DIR)/test/support
ENSURE_TESTDEF     += ENSURE_MODE=ENSURE_MODE_C_EXCEPTION

# --- CHIBIOS ---------------------------------------------------------------- #

ifeq ($(USE_CHIBIOS_IMPLEMENTATION),yes)
ENSURE_DEF         += ENSURE_HAS_PORT
ENSURE_INC         += $(ENSURE_CHIBIOS_DIR)/inc
ENSURE_SRC         += $(ENSURE_CHIBIOS_DIR)/src/ensure_osal_assert.c
ENSURE_TEST        += $(ENSURE_CHIBIOS_DIR)/test
ENSURE_TESTDEF     += ENSURE_HAS_PORT
endif

