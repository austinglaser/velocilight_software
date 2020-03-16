################################################################################
# Color makefile                                                               #
#                                                                              #
# This file provides:                                                          #
# - COLOR_INC    Directories to search for Color headers                       #
# - COLOR_SRC    Color source files                                            #
# - COLOR_ASM    Color assembly files                                          #
# - COLOR_SRC    Color preprocessor definitions                                #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Color directory is the one this makefile resides in
COLOR_DIR           := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

COLOR_COMMON_DIR    := $(COLOR_DIR)/common

# --- INITIALIZATION --------------------------------------------------------- #

COLOR_INC           :=
COLOR_SRC           :=
COLOR_ASM           :=
COLOR_DEF           :=
COLOR_TEST          :=
COLOR_TESTDEF       :=
COLOR_TESTSUPPORT   :=
COLOR_TESTHELPERS   :=

# --- COMMON ----------------------------------------------------------------- #

COLOR_INC           += $(COLOR_COMMON_DIR)/inc
COLOR_SRC           += $(COLOR_COMMON_DIR)/src/color.c
COLOR_TEST          += $(COLOR_COMMON_DIR)/test
COLOR_TESTSUPPORT   += $(COLOR_COMMON_DIR)/test/support
COLOR_TESTHELPERS   += $(COLOR_COMMON_DIR)/test/support/unity_color_helper.h
