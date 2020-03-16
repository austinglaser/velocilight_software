################################################################################
# App makefile                                                                 #
#                                                                              #
# This file provides:                                                          #
# - APP_INC           Directories to search for App headers                    #
# - APP_SRC           App source files                                         #
# - APP_ASM           App assembly files                                       #
# - APP_DEF           App preprocessor definitions                             #
# - APP_TEST          App test directories                                     #
# - APP_TESTDEF       App test defines                                         #
# - APP_TESTSUPPORT   App test support directories                             #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# App directory is the one this makefile resides in
APP_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

APP_INC_DIR  := $(APP_DIR)/inc
APP_SRC_DIR  := $(APP_DIR)/src
APP_TEST_DIR := $(APP_DIR)/test

# --- HEADERS ---------------------------------------------------------------- #

APP_INC :=
APP_INC += $(APP_INC_DIR)

# --- SOURCES ---------------------------------------------------------------- #

APP_SRC :=
APP_SRC += $(APP_SRC_DIR)/main.c
APP_SRC += $(APP_SRC_DIR)/array.c
APP_SRC += $(APP_SRC_DIR)/array_cart_snake.c

# --- ASSEMBLY --------------------------------------------------------------- #

APP_ASM :=

# --- DEFINITIONS ------------------------------------------------------------ #

APP_DEF :=

# --- TESTS ------------------------------------------------------------------ #

APP_TEST :=
APP_TEST := $(APP_TEST_DIR)

APP_TESTDEF :=

APP_TESTSUPPORT :=
