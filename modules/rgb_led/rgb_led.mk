################################################################################
# RGB_LED makefile                                                             #
#                                                                              #
# This file provides:                                                          #
# - RGB_LED_INC    Directories to search for RGB_LED headers                   #
# - RGB_LED_SRC    RGB_LED source files                                        #
# - RGB_LED_ASM    RGB_LED assembly files                                      #
# - RGB_LED_SRC    RGB_LED preprocessor definitions                            #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# RGB_RGB_LED directory is the one this makefile resides in
RGB_LED_DIR     := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

RGB_LED_COMMON_DIR  := $(RGB_LED_DIR)/common
RGB_LED_CHIBIOS_DIR := $(RGB_LED_DIR)/chibios
RGB_LED_NORDIC_DIR  := $(RGB_LED_DIR)/nordic

# --- INITIALIZATION --------------------------------------------------------- #

RGB_LED_INC         :=
RGB_LED_SRC         :=
RGB_LED_ASM         :=
RGB_LED_DEF         :=
RGB_LED_TEST        :=
RGB_LED_TESTDEF     :=
RGB_LED_TESTSUPPORT :=
RGB_LED_TESTHELPERS :=

# --- COMMON ----------------------------------------------------------------- #

RGB_LED_INC         += $(RGB_LED_COMMON_DIR)/inc
RGB_LED_SRC         += $(RGB_LED_COMMON_DIR)/src/rgb_led.c
RGB_LED_TEST        += $(RGB_LED_COMMON_DIR)/test

# --- CHIBIOS ---------------------------------------------------------------- #

ifeq ($(USE_CHIBIOS_IMPLEMENTATION),yes)
RGB_LED_INC         += $(RGB_LED_CHIBIOS_DIR)/inc
RGB_LED_SRC         += $(RGB_LED_CHIBIOS_DIR)/src/rgb_led_implementation.c
RGB_LED_TEST        += $(RGB_LED_CHIBIOS_DIR)/test
endif

# --- NORDIC ----------------------------------------------------------------- #

ifeq ($(USE_NORDIC_IMPLEMENTATION),yes)
RGB_LED_INC         += $(RGB_LED_NORDIC_DIR)/inc
RGB_LED_SRC         += $(RGB_LED_NORDIC_DIR)/src/rgb_led_implementation.c
RGB_LED_TEST        += $(RGB_LED_NORDIC_DIR)/test
RGB_LED_TESTDEF     += SUPPRESS_INLINE_IMPLEMENTATION
RGB_LED_TESTDEF     += __STATIC_INLINE=
endif
