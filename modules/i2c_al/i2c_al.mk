################################################################################
# I2C Abstraction Layer Makefile                                               #
#                                                                              #
# This file provides:                                                          #
# - I2C_AL_INC           Directories to search for I2C_AL headers                #
# - I2C_AL_SRC           I2C_AL source files                                     #
# - I2C_AL_ASM           I2C_AL assembly files                                   #
# - I2C_AL_DEF           I2C_AL preprocessor definitions                         #
# - I2C_AL_TEST          I2C_AL test directories                                 #
# - I2C_AL_TESTDEF       I2C_AL test defines                                     #
# - I2C_AL_TESTSUPPORT   I2C_AL test support directories                         #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

I2C_AL_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

I2C_AL_COMMON_DIR  := $(I2C_AL_DIR)/common
I2C_AL_CHIBIOS_DIR := $(I2C_AL_DIR)/chibios

# --- INITIALIZATION --------------------------------------------------------- #

I2C_AL_INC         :=
I2C_AL_SRC         :=
I2C_AL_ASM         :=
I2C_AL_DEF         :=
I2C_AL_TEST        :=
I2C_AL_TESTDEF     :=
I2C_AL_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

I2C_AL_INC += $(I2C_AL_COMMON_DIR)/inc

# --- CHIBIOS ---------------------------------------------------------------- #

ifeq ($(USE_CHIBIOS_IMPLEMENTATION),yes)
I2C_AL_INC  += $(I2C_AL_CHIBIOS_DIR)/inc
I2C_AL_SRC  += $(I2C_AL_CHIBIOS_DIR)/src/i2c_al_port.c
I2C_AL_TEST += $(I2C_AL_CHIBIOS_DIR)/test
endif
