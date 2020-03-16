################################################################################
# Log makefile                                                                 #
#                                                                              #
# This file provides:                                                          #
# - LOG_INC           Directories to search for Log headers                    #
# - LOG_SRC           Log source files                                         #
# - LOG_ASM           Log assembly files                                       #
# - LOG_DEF           Log preprocessor definitions                             #
# - LOG_TEST          Log test directories                                     #
# - LOG_TESTDEF       Log test defines                                         #
# - LOG_TESTSUPPORT   Log test support directories                             #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Log directory is the one this makefile resides in
LOG_DIR         := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

LOG_COMMON_DIR  := $(LOG_DIR)/common
LOG_CHIBIOS_DIR := $(LOG_DIR)/chibios

# --- INITIALIZATION --------------------------------------------------------- #

LOG_INC         :=
LOG_SRC         :=
LOG_ASM         :=
LOG_DEF         :=
LOG_TEST        :=
LOG_TESTDEF     :=
LOG_TESTSUPPORT :=
LOG_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

LOG_INC         += $(LOG_COMMON_DIR)/inc

LOG_SRC         += $(LOG_COMMON_DIR)/src/log.c
LOG_SRC         += $(LOG_COMMON_DIR)/src/log_serialize.c
LOG_SRC         += $(LOG_COMMON_DIR)/src/log_memory_eeprom.c

LOG_TEST        += $(LOG_COMMON_DIR)/test

LOG_TESTSUPPORT += $(LOG_COMMON_DIR)/test/support

LOG_TESTHELPERS += $(LOG_COMMON_DIR)/test/support/unity_log_helper.h

# --- CHIBIOS ---------------------------------------------------------------- #

ifeq ($(USE_CHIBIOS_IMPLEMENTATION),yes)
LOG_INC         += $(LOG_CHIBIOS_DIR)/inc

LOG_SRC         += $(LOG_CHIBIOS_DIR)/src/log_memory_implementation.c

LOG_TEST        += $(LOG_CHIBIOS_DIR)/test
endif
