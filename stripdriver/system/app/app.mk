################################################################################
# Application Makefile                                                         #
#                                                                              #
# This file provides:                                                          #
# - APP_INC                 Directories to search for application headers      #
# - APP_SRC                 Application source files                           #
# - APP_ASM                 Application assembly files                         #
# - APP_SRC                 Application preprocessor definitions               #
################################################################################

# --- APP DIRECTORIES -------------------------------------------------------- #

# Board directory is the one this makefile resides in
APP_DIR	:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

APP_INC_DIR		:= $(APP_DIR)/inc
APP_SRC_DIR		:= $(APP_DIR)/src
APP_TEST_DIR		:= $(APP_DIR)/test
APP_TESTSUPPORT_DIR	:= $(APP_DIR)/test/support

# --- APP HEADERS ------------------------------------------------------------ #

APP_INC		:=
APP_INC		+= $(APP_INC_DIR)

# --- APP SOURCES ------------------------------------------------------------ #

APP_SRC		:=
APP_SRC		+= $(APP_SRC_DIR)/main.c

# --- APP ASSEMBLY ----------------------------------------------------------- #

APP_ASM		:=

# --- APP DEFINITIONS -------------------------------------------------------- #

APP_DEF		:=

# --- APP TESTS -------------------------------------------------------------- #

APP_TEST	:=
APP_TEST	+= $(APP_TEST_DIR)

APP_TESTSUPPORT	:=
APP_TESTSUPPORT	+= $(APP_TESTSUPPORT_DIR)
