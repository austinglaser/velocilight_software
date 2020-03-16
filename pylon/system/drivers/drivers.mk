################################################################################
# Drivers makefile                                                        #
#                                                                              #
# This file provides:                                                          #
# - DRIVERS_INC           Directories to search for Drivers headers  #
# - DRIVERS_SRC           Drivers source files                       #
# - DRIVERS_ASM           Drivers assembly files                     #
# - DRIVERS_DEF           Drivers preprocessor definitions           #
# - DRIVERS_TEST          Drivers test directories                   #
# - DRIVERS_TESTDEF       Drivers test defines                       #
# - DRIVERS_TESTSUPPORT   Drivers test support directories           #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

DRIVERS_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

DRIVERS_INC         :=
DRIVERS_SRC         :=
DRIVERS_ASM         :=
DRIVERS_DEF         :=
DRIVERS_TEST        :=
DRIVERS_TESTDEF     :=
DRIVERS_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

DRIVERS_INC         += $(DRIVERS_DIR)/inc
DRIVERS_SRC         += $(DRIVERS_DIR)/src/audio_adc.c
