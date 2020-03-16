################################################################################
# Project makefile                                                             #
#                                                                              #
# This file provides:                                                          #
# - PROJECT_VSRC          Project verilog files                                #
# - PROJECT_TEST          Project verilog files                                #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

PROJECT_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

PROJECT_VSRC :=
PROJECT_VSRC += $(PROJECT_DIR)/top.v

PROJECT_TEST :=
PROJECT_TEST += $(PROJECT_DIR)/test_spi_pass.v
