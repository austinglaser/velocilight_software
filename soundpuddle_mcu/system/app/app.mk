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
APP_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

APP_INC         :=
APP_SRC         :=
APP_ASM         :=
APP_DEF         :=
APP_TEST        :=
APP_TESTDEF     :=
APP_TESTSUPPORT :=

# --- COMMON ----------------------------------------------------------------- #

APP_INC         += $(APP_DIR)/inc

APP_SRC         += $(APP_DIR)/src/main.c

APP_SRC         += $(APP_DIR)/src/arduinohsv/arduinohsv.c
APP_SRC         += $(APP_DIR)/src/array.c
APP_SRC         += $(APP_DIR)/src/framebuffer.c
APP_SRC         += $(APP_DIR)/src/led_colors.c
APP_SRC         += $(APP_DIR)/src/memory.c
APP_SRC         += $(APP_DIR)/src/music.c
APP_SRC         += $(APP_DIR)/src/ramtest.c
#APP_SRC         += $(APP_DIR)/src/soundpuddle.c
APP_TEST        += $(APP_DIR)/test
APP_TESTSUPPORT += $(APP_DIR)/test/support
