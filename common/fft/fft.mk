################################################################################
# Fft makefile                                                        #
#                                                                              #
# This file provides:                                                          #
# - FFT_INC           Directories to search for Fft headers  #
# - FFT_SRC           Fft source files                       #
# - FFT_ASM           Fft assembly files                     #
# - FFT_DEF           Fft preprocessor definitions           #
# - FFT_TEST          Fft test directories                   #
# - FFT_TESTDEF       Fft test defines                       #
# - FFT_TESTSUPPORT   Fft test support directories           #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

FFT_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

FFT_INC         :=
FFT_SRC         :=
FFT_ASM         :=
FFT_DEF         :=
FFT_TEST        :=
FFT_TESTDEF     :=
FFT_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

FFT_INC         += $(FFT_DIR)/inc
FFT_SRC         += $(FFT_DIR)/src/fft.c
