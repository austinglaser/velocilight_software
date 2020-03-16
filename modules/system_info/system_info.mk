################################################################################
# System info makefile                                                         #
#                                                                              #
# This file provides:                                                          #
# - SYSTEM_INFO_INC           Directories to search for System headers         #
# - SYSTEM_INFO_SRC           System source files                              #
# - SYSTEM_INFO_ASM           System assembly files                            #
# - SYSTEM_INFO_DEF           System preprocessor definitions                  #
# - SYSTEM_INFO_TEST          System test directories                          #
# - SYSTEM_INFO_TESTDEF       System test defines                              #
# - SYSTEM_INFO_TESTSUPPORT   System test support directories                  #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# System directory is the one this makefile resides in
SYSTEM_INFO_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

SYSTEM_INFO_COMMON_DIR  := $(SYSTEM_INFO_DIR)/common
SYSTEM_INFO_DUMMY_DIR   := $(SYSTEM_INFO_DIR)/dummy

# --- INITIALIZATION --------------------------------------------------------- #

SYSTEM_INFO_INC         :=
SYSTEM_INFO_SRC         :=
SYSTEM_INFO_ASM         :=
SYSTEM_INFO_DEF         :=
SYSTEM_INFO_TEST        :=
SYSTEM_INFO_TESTDEF     :=
SYSTEM_INFO_TESTSUPPORT :=
SYSTEM_INFO_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

SYSTEM_INFO_INC         += $(SYSTEM_INFO_COMMON_DIR)/inc
SYSTEM_INFO_TESTSUPPORT += $(SYSTEM_INFO_COMMON_DIR)/test/support

# TODO: Take this out when an actual implementation is available
SYSTEM_INFO_INC         += $(SYSTEM_INFO_DUMMY_DIR)/inc
