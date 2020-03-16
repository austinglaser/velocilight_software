################################################################################
# ProjectInfo makefile                                                         #
#                                                                              #
# This file provides:                                                          #
# - PROJECT_INFO_INC           Directories to search for ProjectInfo headers   #
# - PROJECT_INFO_SRC           ProjectInfo source files                        #
# - PROJECT_INFO_ASM           ProjectInfo assembly files                      #
# - PROJECT_INFO_DEF           ProjectInfo preprocessor definitions            #
# - PROJECT_INFO_TEST          ProjectInfo test directories                    #
# - PROJECT_INFO_TESTDEF       ProjectInfo test defines                        #
# - PROJECT_INFO_TESTSUPPORT   ProjectInfo test support directories            #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

PROJECT_INFO_DIR     := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

PROJECT_INFO_COMMON_DIR := $(PROJECT_INFO_DIR)/common

# --- INITIALIZATION --------------------------------------------------------- #

PROJECT_INFO_INC         :=
PROJECT_INFO_SRC         :=
PROJECT_INFO_ASM         :=
PROJECT_INFO_DEF         :=
PROJECT_INFO_TEST        :=
PROJECT_INFO_TESTDEF     :=
PROJECT_INFO_TESTSUPPORT :=
PROJECT_INFO_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

PROJECT_INFO_INC += $(PROJECT_INFO_COMMON_DIR)/inc
