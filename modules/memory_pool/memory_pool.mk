################################################################################
# MemoryPool makefile                                                        #
#                                                                              #
# This file provides:                                                          #
# - MEMORY_POOL_INC           Directories to search for MemoryPool headers  #
# - MEMORY_POOL_SRC           MemoryPool source files                       #
# - MEMORY_POOL_ASM           MemoryPool assembly files                     #
# - MEMORY_POOL_DEF           MemoryPool preprocessor definitions           #
# - MEMORY_POOL_TEST          MemoryPool test directories                   #
# - MEMORY_POOL_TESTDEF       MemoryPool test defines                       #
# - MEMORY_POOL_TESTSUPPORT   MemoryPool test support directories           #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# MemoryPool directory is the one this makefile resides in
MEMORY_POOL_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

MEMORY_POOL_COMMON_DIR  := $(MEMORY_POOL_DIR)/common
MEMORY_POOL_CHIBIOS_DIR := $(MEMORY_POOL_DIR)/chibios

# --- INITIALIZATION --------------------------------------------------------- #

MEMORY_POOL_INC         :=
MEMORY_POOL_SRC         :=
MEMORY_POOL_ASM         :=
MEMORY_POOL_DEF         :=
MEMORY_POOL_TEST        :=
MEMORY_POOL_TESTDEF     :=
MEMORY_POOL_TESTSUPPORT :=
MEMORY_POOL_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

MEMORY_POOL_INC         += $(MEMORY_POOL_COMMON_DIR)/inc
MEMORY_POOL_TESTSUPPORT += $(MEMORY_POOL_COMMON_DIR)/test/support

# --- CHIBIOS ---------------------------------------------------------------- #

ifeq ($(USE_CHIBIOS_IMPLEMENTATION),yes)
MEMORY_POOL_INC         += $(MEMORY_POOL_CHIBIOS_DIR)/inc
MEMORY_POOL_SRC         += $(MEMORY_POOL_CHIBIOS_DIR)/src/memory_pool_implementation.c
MEMORY_POOL_TEST        += $(MEMORY_POOL_CHIBIOS_DIR)/test
endif
