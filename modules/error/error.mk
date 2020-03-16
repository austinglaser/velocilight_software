################################################################################
# Error makefile                                                               #
#                                                                              #
# This file provides:                                                          #
# - ERROR_INC    Directories to search for error headers                       #
# - ERROR_SRC    error source files                                            #
# - ERROR_ASM    error assembly files                                          #
# - ERROR_SRC    error preprocessor definitions                                #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Util directory is the one this makefile resides in
ERROR_DIR        := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

ERROR_COMMON_DIR := $(ERROR_DIR)/common

# --- INITIALIZATION --------------------------------------------------------- #

ERROR_INC         :=
ERROR_SRC         :=
ERROR_ASM         :=
ERROR_DEF         :=
ERROR_TEST        :=
ERROR_TESTDEF     :=
ERROR_TESTSUPPORT :=
ERROR_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

ERROR_INC         += $(ERROR_COMMON_DIR)/inc
ERROR_TEST        += $(ERROR_COMMON_DIR)/test
