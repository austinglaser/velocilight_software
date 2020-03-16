################################################################################
# Project makefile                                                             #
#                                                                              #
# This file provides:                                                          #
# - PROJECT_VSRC          Project verilog files                                #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

PROJECT_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

PROJECT_VSRC := $(PROJECT_DIR)/clk_pass.v
