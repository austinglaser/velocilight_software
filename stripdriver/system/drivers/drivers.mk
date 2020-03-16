################################################################################
# Driver makefile                                                              #
#                                                                              #
# This file provides:                                                          #
# - DRIVER_INC              Directories to search for driver headers           #
# - DRIVER_SRC              Driver source files                                #
# - DRIVER_ASM              Driver assembly files                              #
# - DRIVER_DEF              Driver preprocessor definitions                    #
################################################################################

# --- DRIVER DIRECTORIES ----------------------------------------------------- #

# Driver directory is the one this makefile resides in
DRIVER_DIR	:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

DRIVER_INC_DIR		:= $(DRIVER_DIR)/inc
DRIVER_SRC_DIR		:= $(DRIVER_DIR)/src
DRIVER_TEST_DIR		:= $(DRIVER_DIR)/test
DRIVER_TESTSUPPORT_DIR	:= $(DRIVER_DIR)/test/support

# --- DRIVER HEADERS --------------------------------------------------------- #

DRIVER_INC		:=
DRIVER_INC		+= $(DRIVER_INC_DIR)

# --- DRIVER SOURCES --------------------------------------------------------- #

DRIVER_SRC		:=

# --- DRIVER ASSEMBLY -------------------------------------------------------- #

DRIVER_ASM		:=

# --- DRIVER DEFINITIONS ----------------------------------------------------- #

DRIVER_DEF		:=

# --- DRIVER TESTS ----------------------------------------------------------- #

DRIVER_TEST		:=
DRIVER_TEST		+= $(DRIVER_TEST_DIR)

DRIVER_TESTSUPPORT	:=
DRIVER_TESTSUPPORT	+= $(DRIVER_TESTSUPPORT_DIR)
