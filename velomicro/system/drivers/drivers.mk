################################################################################
# Drivers makefile                                                             #
#                                                                              #
# This file provides:                                                          #
# - DRIVERS_INC           Directories to search for Drivers headers            #
# - DRIVERS_SRC           Drivers source files                                 #
# - DRIVERS_ASM           Drivers assembly files                               #
# - DRIVERS_DEF           Drivers preprocessor definitions                     #
# - DRIVERS_TEST          Drivers test directories                             #
# - DRIVERS_TESTDEF       Drivers test defines                                 #
# - DRIVERS_TESTSUPPORT   Drivers test support directories                     #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Drivers directory is the one this makefile resides in
DRIVERS_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

DRIVERS_INC_DIR  := $(DRIVERS_DIR)/inc
DRIVERS_SRC_DIR  := $(DRIVERS_DIR)/src
DRIVERS_TEST_DIR := $(DRIVERS_DIR)/test

# --- HEADERS ---------------------------------------------------------------- #

DRIVERS_INC :=
DRIVERS_INC += $(DRIVERS_INC_DIR)

# --- SOURCES ---------------------------------------------------------------- #

DRIVERS_SRC :=
DRIVERS_SRC += $(DRIVERS_SRC_DIR)/led_strip.c

# --- ASSEMBLY --------------------------------------------------------------- #

DRIVERS_ASM :=

# --- DEFINITIONS ------------------------------------------------------------ #

DRIVERS_DEF :=

# --- TESTS ------------------------------------------------------------------ #

DRIVERS_TEST :=
DRIVERS_TEST += $(DRIVERS_TEST_DIR)

DRIVERS_TESTDEF :=

DRIVERS_TESTSUPPORT :=
