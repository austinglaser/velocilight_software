################################################################################
# Perlin makefile                                                              #
#                                                                              #
# This file provides:                                                          #
# - PERLIN_INC           Directories to search for Perlin headers              #
# - PERLIN_SRC           Perlin source files                                   #
# - PERLIN_ASM           Perlin assembly files                                 #
# - PERLIN_DEF           Perlin preprocessor definitions                       #
# - PERLIN_TEST          Perlin test directories                               #
# - PERLIN_TESTDEF       Perlin test defines                                   #
# - PERLIN_TESTSUPPORT   Perlin test support directories                       #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

PERLIN_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

PERLIN_INC         :=
PERLIN_SRC         :=
PERLIN_ASM         :=
PERLIN_DEF         :=
PERLIN_TEST        :=
PERLIN_TESTDEF     :=
PERLIN_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

PERLIN_INC += $(PERLIN_DIR)/inc
PERLIN_SRC += $(PERLIN_DIR)/src/perlin.c
