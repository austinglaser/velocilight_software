################################################################################
# Fpga makefile                                                        #
#                                                                              #
# This file provides:                                                          #
# - FPGA_INC           Directories to search for Fpga headers  #
# - FPGA_SRC           Fpga source files                       #
# - FPGA_ASM           Fpga assembly files                     #
# - FPGA_DEF           Fpga preprocessor definitions           #
# - FPGA_TEST          Fpga test directories                   #
# - FPGA_TESTDEF       Fpga test defines                       #
# - FPGA_TESTSUPPORT   Fpga test support directories           #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

FPGA_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# --- INITIALIZATION --------------------------------------------------------- #

FPGA_INC         :=
FPGA_SRC         :=
FPGA_ASM         :=
FPGA_DEF         :=
FPGA_TEST        :=
FPGA_TESTDEF     :=
FPGA_TESTSUPPORT :=
FPGA_BLOBS       :=

# --- COMMON ----------------------------------------------------------------- #

FPGA_INC         += $(FPGA_DIR)/inc
FPGA_INC         += $(FPGA_DIR)/$(FPGA_IMAGE)

FPGA_SRC         += $(FPGA_DIR)/src/fpga.c
FPGA_SRC         += $(FPGA_DIR)/src/fpga_image.c

FPGA_MAP_SRC     := $(FPGA_DIR)/$(FPGA_IMAGE)/fpga_map.c
ifneq ("$(wildcard $(FPGA_MAP_SRC))","")
FPGA_SRC         += $(FPGA_MAP_SRC)
endif

FPGA_BLOBS       += $(FPGA_DIR)/$(FPGA_IMAGE)/fpga_blob.bin

FPGA_TEST_DIR   := $(FPGA_DIR)/$(FPGA_IMAGE)/test
ifneq ("$(wildcard $(FPGA_TEST_DIR))","")
FPGA_TEST        += $(FPGA_TEST_DIR)
endif
