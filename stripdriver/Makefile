################################################################################
# Top-level makefile                                                           #
################################################################################

# --- PROJECT ROOT DIRECTORY ------------------------------------------------- #

# Root directory is the one this makefile resides in
ROOT_DIR    := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- PROJECT CONFIGURATION -------------------------------------------------- #

PROJECT     := stripdriver
REVISION    ?= 3p0

# --- PROJECT DIRECTORIES ---------------------------------------------------- #

# Code Directories
COMMON_DIR      := $(realpath $(ROOT_DIR)/..)
SYSTEM_DIR      := $(ROOT_DIR)/system
SUPPORT_DIR     := $(ROOT_DIR)/support
CHIBIOS         := $(COMMON_DIR)/chibios
MOD_DIR         := $(COMMON_DIR)/modules

# Build directories
BUILDDIR        := $(ROOT_DIR)/build_v$(REVISION)
CEEDLING_BUILDDIR   := $(ROOT_DIR)/build_ceedling

# Clean all build output revisions 
clean: BUILDDIR := $(wildcard $(ROOT_DIR)/build*)

# --- OPTIONS ---------------------------------------------------------------- #

# Delete files on failed target completion
.DELETE_ON_ERROR:

# --- MODULES ---------------------------------------------------------------- #

# General
USE_CHIBIOS_IMPLEMENTATION := yes
USE_MOCK_HAL               := yes
USE_MOCK_RT                := yes

USE_BYTESWAP               := yes
USE_C_EXCEPTION            := yes
USE_COLOR                  := yes
USE_EEPROM                 := yes
USE_ENSURE                 := yes
USE_ERROR                  := yes
USE_LOG                    := yes
USE_MEMORY_POOL            := yes
USE_PROJECT_INFO           := yes
USE_RGB_LED                := yes
USE_SYSTEM_INFO            := yes
USE_UTIL                   := yes


include $(MOD_DIR)/modules.mk

# --- PROJECT SECTIONS ------------------------------------------------------- #

# Board
include $(SYSTEM_DIR)/boards/boards.mk

# Drivers
include $(SYSTEM_DIR)/drivers/drivers.mk

# Application
include $(SYSTEM_DIR)/app/app.mk

# --- PROJECT COMPILATION ---------------------------------------------------- #

include $(SUPPORT_DIR)/config.mk

