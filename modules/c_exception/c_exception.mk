################################################################################
# CException makefile                                                          #
#                                                                              #
# This file provides:                                                          #
# - C_EXCEPTION_INC    Directories to search for CException headers            #
# - C_EXCEPTION_SRC    CException source files                                 #
# - C_EXCEPTION_ASM    CException assembly files                               #
# - C_EXCEPTION_SRC    CException preprocessor definitions                     #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# CException directory is the one this makefile resides in
C_EXCEPTION_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

C_EXCEPTION_INC_DIR     := $(C_EXCEPTION_DIR)/lib
C_EXCEPTION_SRC_DIR     := $(C_EXCEPTION_DIR)/lib

# --- INITIALIZATION --------------------------------------------------------- #

C_EXCEPTION_INC         :=
C_EXCEPTION_SRC         :=
C_EXCEPTION_ASM         :=
C_EXCEPTION_DEF         :=
C_EXCEPTION_TEST        :=
C_EXCEPTION_TESTDEF     :=
C_EXCEPTION_TESTSUPPORT :=
C_EXCEPTION_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

C_EXCEPTION_INC         += $(C_EXCEPTION_INC_DIR)
C_EXCEPTION_SRC         += $(C_EXCEPTION_SRC_DIR)/CException.c
