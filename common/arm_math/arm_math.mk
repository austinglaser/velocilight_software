################################################################################
# ArmMath makefile                                                             #
#                                                                              #
# This file provides:                                                          #
# - ARM_MATH_INC           Directories to search for ArmMath headers           #
# - ARM_MATH_SRC           ArmMath source files                                #
# - ARM_MATH_ASM           ArmMath assembly files                              #
# - ARM_MATH_DEF           ArmMath preprocessor definitions                    #
# - ARM_MATH_TEST          ArmMath test directories                            #
# - ARM_MATH_TESTDEF       ArmMath test defines                                #
# - ARM_MATH_TESTSUPPORT   ArmMath test support directories                    #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

ARM_MATH_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

ARM_MATH_INC         :=
ARM_MATH_SRC         :=
ARM_MATH_ASM         :=
ARM_MATH_DEF         :=
ARM_MATH_TEST        :=
ARM_MATH_TESTDEF     :=
ARM_MATH_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

ARM_MATH_SRC         += $(wildcard $(ARM_MATH_DIR)/src/*.c)
ARM_MATH_ASM         += $(APP_DIR)/src/arm_bitreversal2.s
