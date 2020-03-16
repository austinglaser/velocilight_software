################################################################################
# Mpu9250 makefile                                                        #
#                                                                              #
# This file provides:                                                          #
# - MPU9250_INC           Directories to search for Mpu9250 headers  #
# - MPU9250_SRC           Mpu9250 source files                       #
# - MPU9250_ASM           Mpu9250 assembly files                     #
# - MPU9250_DEF           Mpu9250 preprocessor definitions           #
# - MPU9250_TEST          Mpu9250 test directories                   #
# - MPU9250_TESTDEF       Mpu9250 test defines                       #
# - MPU9250_TESTSUPPORT   Mpu9250 test support directories           #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

MPU9250_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

MPU9250_COMMON_DIR  := $(MPU9250_DIR)/common
MPU9250_CHIBIOS_DIR := $(MPU9250_DIR)/chibios
MPU9250_NORDIC_DIR  := $(MPU9250_DIR)/nordic

# --- INITIALIZATION --------------------------------------------------------- #

MPU9250_INC         :=
MPU9250_SRC         :=
MPU9250_ASM         :=
MPU9250_DEF         :=
MPU9250_TEST        :=
MPU9250_TESTDEF     :=
MPU9250_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

MPU9250_INC         += $(MPU9250_COMMON_DIR)/inc
MPU9250_SRC         += $(MPU9250_COMMON_DIR)/src/mpu9250.c
MPU9250_TEST        += $(MPU9250_COMMON_DIR)/test
MPU9250_TESTSUPPORT += $(MPU9250_COMMON_DIR)/test/support

# --- CHIBIOS----------------------------------------------------------------- #

ifeq ($(USE_CHIBIOS_IMPLEMENTATION),yes)
MPU9250_INC         += $(MPU9250_CHIBIOS_DIR)/inc
MPU9250_SRC         += $(MPU9250_CHIBIOS_DIR)/src/mpu9250_port.c
MPU9250_TEST        += $(MPU9250_CHIBIOS_DIR)/test
endif

# --- NORDIC ----------------------------------------------------------------- #

ifeq ($(USE_NORDIC_IMPLEMENTATION),yes)
MPU9250_INC         += $(MPU9250_NORDIC_DIR)/inc
MPU9250_SRC         += $(MPU9250_NORDIC_DIR)/src/mpu9250_port.c
MPU9250_TEST        += $(MPU9250_NORDIC_DIR)/test
endif
