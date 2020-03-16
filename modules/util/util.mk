################################################################################
# Util makefile                                                                #
#                                                                              #
# This file provides:                                                          #
# - UTIL_INC    Directories to search for Util headers                         #
# - UTIL_SRC    Util source files                                              #
# - UTIL_ASM    Util assembly files                                            #
# - UTIL_SRC    Util preprocessor definitions                                  #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Util directory is the one this makefile resides in
UTIL_DIR        := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

UTIL_COMMON_DIR := $(UTIL_DIR)/common

# --- INITIALIZATION --------------------------------------------------------- #

UTIL_INC         :=
UTIL_SRC         :=
UTIL_ASM         :=
UTIL_DEF         :=
UTIL_TEST        :=
UTIL_TESTDEF     :=
UTIL_TESTSUPPORT :=
UTIL_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

UTIL_INC         += $(UTIL_COMMON_DIR)/inc
UTIL_SRC         += $(UTIL_COMMON_DIR)/src/util.c
UTIL_TEST        += $(UTIL_COMMON_DIR)/test
UTIL_TESTSUPPORT += $(UTIL_COMMON_DIR)/test/support
