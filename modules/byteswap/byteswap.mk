################################################################################
# Byteswap makefile                                                            #
#                                                                              #
# This file provides:                                                          #
# - BYTESWAP_INC    Directories to search for Byteswap headers                 #
# - BYTESWAP_SRC    Byteswap source files                                      #
# - BYTESWAP_ASM    Byteswap assembly files                                    #
# - BYTESWAP_SRC    Byteswap preprocessor definitions                          #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Byteswap directory is the one this makefile resides in
BYTESWAP_DIR         := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

BYTESWAP_COMMON_DIR  := $(BYTESWAP_DIR)/common

# --- INITIALIZATION --------------------------------------------------------- #

BYTESWAP_INC         :=
BYTESWAP_SRC         :=
BYTESWAP_ASM         :=
BYTESWAP_DEF         :=
BYTESWAP_TEST        :=
BYTESWAP_TESTDEF     :=
BYTESWAP_TESTSUPPORT :=
BYTESWAP_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

BYTESWAP_INC         += $(BYTESWAP_COMMON_DIR)/inc
BYTESWAP_SRC         += $(BYTESWAP_COMMON_DIR)/src/byteswap.c
BYTESWAP_TEST        += $(BYTESWAP_COMMON_DIR)/test

