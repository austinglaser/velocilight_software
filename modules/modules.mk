################################################################################
# Module makefile                                                              #
#                                                                              #
# This file provides:                                                          #
# - MODULES_INC    Directories to search for Module headers                    #
# - MODULES_SRC    Module source files                                         #
# - MODULES_ASM    Module assembly files                                       #
# - MODULES_DEF    Module preprocessor definitions                             #
#                                                                              #
# For each included <module>, the including makefile must set the USE_<MODULE> #
# variable to 'yes'. If it is set to any other value (or unset), the sources   #
# for that module will not be included. For instance, to include the 'color'   #
# module:                                                                      #
#                                                                              #
# USE_COLOR := yes                                                             #
#                                                                              #
# It can be left out by any of the following:                                  #
#                                                                              #
# USE_COLOR := no                                                              #
# USE_COLOR := anything-but-yes                                                #
# USE_COLOR :=                                                                 #
#                                                                              #
# or by commenting out the line entirely. The first is preferred for clarity.  #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Module directory is the one this makefile resides in
MODULES_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- HELPERS ---------------------------------------------------------------- #

include $(MODULES_DIR)/support/modules_helper.mk

# --- INITIALIZATION --------------------------------------------------------- #

MODULES_INC         :=
MODULES_SRC         :=
MODULES_ASM         :=
MODULES_DEF         :=
MODULES_TEST        :=
MODULES_TESTDEF     :=
MODULES_TESTSUPPORT :=
MODULES_TESTHELPERS :=

# --- MODULE INCLUSION ------------------------------------------------------- #

$(call module, $(MODULES_DIR), i2c_al)
$(call module, $(MODULES_DIR), byteswap)
$(call module, $(MODULES_DIR), c_exception)
$(call module, $(MODULES_DIR), color)
$(call module, $(MODULES_DIR), eeprom)
$(call module, $(MODULES_DIR), error)
$(call module, $(MODULES_DIR), ensure)
$(call module, $(MODULES_DIR), log)
$(call module, $(MODULES_DIR), memory_pool)
$(call module, $(MODULES_DIR), mpu9250)
$(call module, $(MODULES_DIR), project_info)
$(call module, $(MODULES_DIR), rgb_led)
$(call module, $(MODULES_DIR), system_info)
$(call module, $(MODULES_DIR), util)

# --- CHIBIOS MODULE INCLUSION ----------------------------------------------- #

$(call module, $(MODULES_DIR)/chibios, mock_hal)
$(call module, $(MODULES_DIR)/chibios, mock_rt)

