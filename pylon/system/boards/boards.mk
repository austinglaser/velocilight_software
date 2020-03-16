################################################################################
# General board selection makefile                                             #
#                                                                              #
# A makefile including this should define:                                     #
# - REVISION                Board hardware revsion                             #
#                                                                              #
# This file provides:                                                          #
# - BOARDS_DIR              The top-level boards directory                     #
# - BOARD_MK                The board file for the specific revision/node      #
################################################################################

# --- BOARD ROOT DIRECTORY --------------------------------------------------- #

# Boards directory is the one this makefile resides in
BOARDS_DIR	:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- BOARD SELECTION -------------------------------------------------------- #

# Ensure board specifications are defined
ifeq ($(REVISION),)
$(error REVISION undefined)
endif

# Board makefile
BOARD_MK := $(BOARDS_DIR)/$(PROJECT)_v$(REVISION)/board.mk

# Ensure project board file exists
ifneq ("$(wildcard $(BOARD_MK))","")
include $(BOARD_MK)
else
$(error no available board for $(PROJECT) v$(REVISION)))
endif
