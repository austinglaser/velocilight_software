################################################################################
# Chibios Config makefile                                                      #
#                                                                              #
# Configuration files for running chibios-dependent tests locally              #
#                                                                              #
# This file provides:                                                          #
# - CONFIG_INC           Directories to search for Config headers              #
# - CONFIG_SRC           Config source files                                   #
# - CONFIG_ASM           Config assembly files                                 #
# - CONFIG_DEF           Config preprocessor definitions                       #
# - CONFIG_TEST          Config test directories                               #
# - CONFIG_TESTDEF       Config test defines                                   #
# - CONFIG_TESTSUPPORT   Config test support directories                       #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# ChConfig directory is the one this makefile resides in
CONFIG_DIR	:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

CONFIG_INC_DIR	:= $(CONFIG_DIR)/inc

# --- HEADERS ---------------------------------------------------------------- #

CONFIG_INC		:=
CONFIG_INC		+= $(CONFIG_INC_DIR)

# --- SOURCES ---------------------------------------------------------------- #

CONFIG_SRC		:=

# --- ASSEMBLY --------------------------------------------------------------- #

CONFIG_ASM		:=

# --- DEFINITIONS ------------------------------------------------------------ #

CONFIG_DEF		:=

# --- TESTS ------------------------------------------------------------------ #

CONFIG_TEST		:=

CONFIG_TESTDEF	:=

CONFIG_TESTSUPPORT	:=
