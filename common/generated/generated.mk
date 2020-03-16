################################################################################
# Generated makefile                                                        #
#                                                                              #
# This file provides:                                                          #
# - GENERATED_INC           Directories to search for Generated headers  #
# - GENERATED_SRC           Generated source files                       #
# - GENERATED_ASM           Generated assembly files                     #
# - GENERATED_DEF           Generated preprocessor definitions           #
# - GENERATED_TEST          Generated test directories                   #
# - GENERATED_TESTDEF       Generated test defines                       #
# - GENERATED_TESTSUPPORT   Generated test support directories           #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

GENERATED_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

GENERATED_INC         :=
GENERATED_SRC         :=
GENERATED_ASM         :=
GENERATED_DEF         :=
GENERATED_TEST        :=
GENERATED_TESTDEF     :=
GENERATED_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

GENERATED_SRC         += $(GENERATED_DIR)/src/hamming_q15_len4096.c
GENERATED_SRC         += $(GENERATED_DIR)/src/hamming_q15_len2048.c
GENERATED_SRC         += $(GENERATED_DIR)/src/hamming_q15_len1024.c
GENERATED_SRC         += $(GENERATED_DIR)/src/hamming_q15_len512.c
GENERATED_SRC         += $(GENERATED_DIR)/src/hamming_q15_len256.c
GENERATED_SRC         += $(GENERATED_DIR)/src/hamming_q15_len128.c
GENERATED_SRC         += $(GENERATED_DIR)/src/hamming_q15_len64.c
GENERATED_SRC         += $(GENERATED_DIR)/src/hamming_q15_len32.c
GENERATED_SRC         += $(GENERATED_DIR)/src/strip_map_octave_len4096.c
GENERATED_INC         += $(GENERATED_DIR)/inc
