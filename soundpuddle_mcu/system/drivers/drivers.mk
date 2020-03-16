################################################################################
# Driver makefile                                                              #
#                                                                              #
# This file provides:                                                          #
# - DRIVER_INC              Directories to search for driver headers           #
# - DRIVER_SRC              Driver source files                                #
# - DRIVER_ASM              Driver assembly files                              #
# - DRIVER_DEF              Driver preprocessor definitions                    #
################################################################################

# --- DRIVER DIRECTORIES ----------------------------------------------------- #

# Driver directory is the one this makefile resides in
DRIVER_DIR  := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

DRIVER_INC         :=
DRIVER_SRC         :=
DRIVER_ASM         :=
DRIVER_DEF         :=
DRIVER_TEST        :=
DRIVER_TESTDEF     :=
DRIVER_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

DRIVER_INC          += $(DRIVER_DIR)/inc

DRIVER_SRC          += $(DRIVER_DIR)/src/audio_adc.c

DRIVER_TEST         += $(DRIVER_DIR)/test
DRIVER_TESTSUPPORT  += $(DRIVER_DIR)/test/support
