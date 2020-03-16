################################################################################
# Eeprom makefile                                                              #
#                                                                              #
# This file provides:                                                          #
# - EEPROM_INC           Directories to search for Eeprom headers              #
# - EEPROM_SRC           Eeprom source files                                   #
# - EEPROM_ASM           Eeprom assembly files                                 #
# - EEPROM_DEF           Eeprom preprocessor definitions                       #
# - EEPROM_TEST          Eeprom test directories                               #
# - EEPROM_TESTDEF       Eeprom test defines                                   #
# - EEPROM_TESTSUPPORT   Eeprom test support directories                       #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Eeprom directory is the one this makefile resides in
EEPROM_DIR  := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

EEPROM_COMMON_DIR  := $(EEPROM_DIR)/common
EEPROM_DUMMY_DIR   := $(EEPROM_DIR)/dummy

# --- INITIALIZATION---------------------------------------------------------- #

EEPROM_INC         :=
EEPROM_SRC         :=
EEPROM_ASM         :=
EEPROM_DEF         :=
EEPROM_TEST        :=
EEPROM_TESTDEF     :=
EEPROM_TESTSUPPORT :=
EEPROM_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

EEPROM_INC         += $(EEPROM_COMMON_DIR)/inc
EEPROM_TESTSUPPORT += $(EEPROM_COMMON_DIR)/test/support

# TODO: Take this out when an actual implementation is available
EEPROM_INC         += $(EEPROM_DUMMY_DIR)/inc
