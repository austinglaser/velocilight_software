################################################################################
# Board makefile                                                               #
#                                                                              #
# This file provides:                                                          #
# - BOARD_INC           Directories to search for Board headers                #
# - BOARD_SRC           Board source files                                     #
# - BOARD_ASM           Board assembly files                                   #
# - BOARD_DEF           Board preprocessor definitions                         #
# - BOARD_TEST          Board test directories                                 #
# - BOARD_TESTDEF       Board test defines                                     #
# - BOARD_TESTSUPPORT   Board test support directories                         #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

# Board directory is the one this makefile resides in
BOARD_DIR	:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

BOARD_INC_DIR	:= $(BOARD_DIR)/inc

# --- HEADERS ---------------------------------------------------------------- #

BOARD_INC		:=
BOARD_INC		+= $(BOARD_INC_DIR)

# --- SOURCES ---------------------------------------------------------------- #

BOARD_SRC		:=

# --- ASSEMBLY --------------------------------------------------------------- #

BOARD_ASM		:=

# --- DEFINITIONS ------------------------------------------------------------ #

BOARD_DEF		:=
BOARD_DEF		+= BOARD_PCA10040 CONFIG_NFCT_PINS_AS_GPIOS

# --- TESTS ------------------------------------------------------------------ #

BOARD_TEST		:=

BOARD_TESTDEF		:=

BOARD_TESTSUPPORT	:=

# --- DEVICE CONFIGURATION --------------------------------------------------- #

BOARD_DEVICE    := nrf52832
BOARD_VAR       := xxaa
BOARD_LD_SCRIPT := $(BOARD_DIR)/ld/ble_app_beacon_gcc_nrf52.ld

