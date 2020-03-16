################################################################################
# Tests for modules-general                                                    #
################################################################################

# --- PROJECT ROOT DIRECTORY ------------------------------------------------- #

# Root directory is the one this makefile resides in
ROOT_DIR    := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- PROJECT DIRECTORIES ---------------------------------------------------- #

CEEDLING_BUILDDIR   := $(ROOT_DIR)/build
SUPPORT_DIR         := $(ROOT_DIR)/support

# --- OPTIONS ---------------------------------------------------------------- #

# Delete files on failed target completion
.DELETE_ON_ERROR:

# --- MODULES ---------------------------------------------------------------- #

# Test all modules
USE_CHIBIOS_IMPLEMENTATION := yes
USE_MOCK_HAL               := yes
USE_MOCK_RT                := yes

USE_I2C_AL                  := yes
USE_BYTESWAP               := yes
USE_C_EXCEPTION            := yes
USE_COLOR                  := yes
USE_EEPROM                 := yes
USE_ERROR                  := yes
USE_ENSURE                 := yes
USE_LOG                    := yes
USE_MEMORY_POOL            := yes
USE_MPU9250                := yes
USE_PROJECT_INFO           := yes
USE_RGB_LED                := yes
USE_SYSTEM_INFO            := yes
USE_UTIL                   := yes
include modules.mk

include chibios/config/config.mk

# --- TEST CONFIGURATION ----------------------------------------------------- #

TESTBASECONFIG      := $(SUPPORT_DIR)/ceedling.yml

TESTSRC     := $(MODULES_SRC) \
               $(CONFIG_SRC)

TESTINC     := $(MODULES_INC) \
               $(CONFIG_INC)

TESTTEST    := $(MODULES_TEST) \
               $(CONFIG_TEST)

TESTDEF     := $(MODULES_TESTDEF) \
               $(CONFIG_TESTDEF)

TESTSUPPORT := $(MODULES_TESTSUPPORT) \
               $(CONFIG_TESTSUPPORT)

TESTHELPERS := $(MODULES_TESTHELPERS) \
               $(CONFIG_TESTHELPERS)


# --- PROJECT COMPILATION ---------------------------------------------------- #

all: ceedling-test
test: ceedling-test
coverage: ceedling-coverage

clean: ceedling-clean
	@rm -rf $(CEEDLING_BUILDDIR)

include $(ROOT_DIR)/ceedling/rules.mk

print-%:
	@echo '$*=$($*)'
