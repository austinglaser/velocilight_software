################################################################################
# ChibiOS RT mock makefile                                                     #
#                                                                              #
# This file provides:                                                          #
# - MOCK_RT_INC           Directories to search for MockRt headers             #
# - MOCK_RT_SRC           RT source files                                      #
# - MOCK_RT_ASM           RT assembly files                                    #
# - MOCK_RT_DEF           RT preprocessor definitions                          #
# - MOCK_RT_TEST          RT test directories                                  #
# - MOCK_RT_TESTSUPPORT   RT test support directories                          #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# MockRt directory is the one this makefile resides in
MOCK_RT_DIR		:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

MOCK_RT_INC_DIR		:= $(MOCK_RT_DIR)/inc
MOCK_RT_STUBS_DIR	:= $(MOCK_RT_DIR)/stubs

# --- HEADERS ---------------------------------------------------------------- #

MOCK_RT_INC		:=

# --- SOURCES ---------------------------------------------------------------- #

MOCK_RT_SRC		:=

# --- ASSEMBLY --------------------------------------------------------------- #

MOCK_RT_ASM		:=

# --- DEFINITIONS ------------------------------------------------------------ #

MOCK_RT_DEF		:=

# --- TESTS ------------------------------------------------------------------ #

MOCK_RT_TEST		:=

MOCK_RT_TESTDEF		:=
MOCK_RT_TESTDEF		+= MOCK_RT

MOCK_RT_TESTSUPPORT	:=
MOCK_RT_TESTSUPPORT	+= $(MOCK_RT_INC_DIR)
MOCK_RT_TESTSUPPORT	+= $(MOCK_RT_STUBS_DIR)

MOCK_RT_TESTHELPERS	:=
