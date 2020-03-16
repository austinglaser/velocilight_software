################################################################################
# Build rules for nRF5x microcontrollers                                       #
# Modeled after rules.mk in ChibiosRT (https://github.com/ChibiOS/ChibiOS)     #
#                                                                              #
# Uses the following variables:                                                #
#   - PROJECT              Project name (no spaces).                           #
#                                                                              #
#   - CSRC                 C Source Files.                                     #
#   - ASMSRC               Assembly sources.                                   #
#   - HEAP_SIZE            Size of memory for the heap. If unset, uses 0.      #
#                                                                              #
#   - OPT                  Compilation options                                 #
#   - LDOPT                Linker options. Should be comma-separated           #
#   - DEFS                 Preprocessor definitions (not prefixed with '-D')   #
#                                                                              #
#   - BUILD_DIR            Directory for build products.                       #
#   - INCDIR               Directories to search for headers.                  #
#   - LIBDIR               Directories to search for libraries.                #
#                                                                              #
#   - MCU                  The cortex type.                                    #
#   - DEVICE               The device type.                                    #
#   - VARIANT              The device variant.                                 #
#                                                                              #
#   - SOFTDEVICE           Hex file to use as the softdevice for programming.  #
#   - APP_ADDR             Address at which the application should be flashed. #
################################################################################

# --- CONFIGURATION ---------------------------------------------------------- #

# Options
OPT   += -mthumb -ffunction-sections -fdata-sections -fno-common
LDOPT := $(LDOPT),--gc-sections

# Commands
TARGET := arm-none-eabi
CC     := $(TARGET)-gcc
CP     := $(TARGET)-objcopy
LD     := $(TARGET)-gcc
AS     := $(TARGET)-gcc -x assembler-with-cpp
OD     := $(TARGET)-objdump
SZ     := $(TARGET)-size
HEX    := $(CP) -O ihex
BIN    := $(CP) -O binary
FLASH  := JLinkExe

# Heap size
HEAP_SIZE ?= 0
DEFS      += __HEAP_SIZE=$(HEAP_SIZE)

# Flash script location
FLASH_SCRIPT  := $(BUILD_DIR)/flash.jlink
EFLASH_SCRIPT := $(BUILD_DIR)/eflash.jlink
FLASH_DEVICE  := $(DEVICE)_$(VARIANT)
FLASH_FLAGS   := -If swd \
                 -Speed auto \
                 -Device $(FLASH_DEVICE)

# All paths where source files live
SRCPATHS := $(sort               \
                $(dir $(CSRC))   \
                $(dir $(EXTSRC)) \
                $(dir $(ASMSRC)) \
                $(dir $(ASMXSRC)))

# Generate flags for command-line-defined values
DDEFS   := $(patsubst %,-D%,$(DEFS))
IINCDIR := $(patsubst %,-I%,$(INCDIR) $(EXTINCDIR))
LLIBDIR := $(patsubst %,-L%,$(LIBDIR))

# Output directories
OBJDIR  := $(BUILD_DIR)/obj
LSTDIR  := $(BUILD_DIR)/lst
DEPDIR  := $(BUILD_DIR)/dep

SUBDIRS := $(OBJDIR) $(LSTDIR) $(DEPDIR)
DIRS    := $(BUILD_DIR) $(SUBDIRS)

# Output files
OUTFILES       := $(BUILD_DIR)/$(PROJECT).elf \
                  $(BUILD_DIR)/$(PROJECT).hex \
                  $(BUILD_DIR)/$(PROJECT).bin \
                  $(BUILD_DIR)/$(PROJECT).dmp

# Object files
COBJS    := $(addprefix $(OBJDIR)/, $(notdir $(CSRC:.c=.o)))
EXTOBJS  := $(addprefix $(OBJDIR)/, $(notdir $(EXTSRC:.c=.o)))
ASMOBJS  := $(addprefix $(OBJDIR)/, $(notdir $(ASMSRC:.s=.o)))
ASMXOBJS := $(addprefix $(OBJDIR)/, $(notdir $(ASMXSRC:.S=.o)))
OBJS     := $(COBJS) $(EXTOBJS) $(ASMOBJS) $(ASMXOBJS)

# Flags
MCFLAGS := -mcpu=$(MCU)
ODFLAGS := -x --syms
ASFLAGS  = $(MCFLAGS) $(OPT) -Wa,-amhls=$(LSTDIR)/$(notdir $(<:.s=.lst)) $(DDEFS)
CFLAGS   = $(MCFLAGS) $(OPT) -Wa,-amhls=$(LSTDIR)/$(notdir $(<:.c=.lst)) $(DDEFS)
LDFLAGS  = $(MCFLAGS) $(OPT) $(LLIBDIR) \
          -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map,--cref,--no-warn-mismatch,--script=$(LD_SCRIPT)$(LDOPT)

# Generate dependency info
ASFLAGS += -MD -MP -MF $(DEPDIR)/$(@F).d
CFLAGS  += -MD -MP -MF $(DEPDIR)/$(@F).d

# Where to look for sources
VPATH := $(SRCPATHS)

# --- RULES ------------------------------------------------------------------ #

nordic-release: $(OBJS) $(OUTFILES)

$(OBJS): | $(DIRS)

$(BUILD_DIR):
	@echo Compiler options
	@echo $(CC) -c $(CFLAGS) $(OPT) $(WARN) $(IINCDIR) main.c -o main.o
	@mkdir -p $@

$(SUBDIRS):
	@mkdir -p $@

$(COBJS) : $(OBJDIR)/%.o : %.c $(MAKEFILE_LIST)
	@echo Compiling $(<F)
	@$(CC) -c $(CFLAGS) $(OPT) $(WARN) $(IINCDIR) $< -o $@

$(EXTOBJS) : $(OBJDIR)/%.o : %.c $(MAKEFILE_LIST)
	@echo Compiling $(<F)
	@$(CC) -c $(CFLAGS) $(OPT) $(IINCDIR) $< -o $@

$(ASMOBJS) : $(OBJDIR)/%.o : %.s $(MAKEFILE_LIST)
	@echo Compiling $(<F)
	@$(AS) -c $(ASFLAGS) $(IINCDIR) $< -o $@

$(ASMXOBJS) : $(OBJDIR)/%.o : %.S $(MAKEFILE_LIST)
	@echo Compiling $(<F)
	@$(CC) -c $(ASFLAGS) $(IINCDIR) $< -o $@

$(BUILD_DIR)/$(PROJECT).elf : $(OBJS) $(LD_SCRIPT)
	@echo Linking $@
	@$(LD) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/$(PROJECT).hex : $(BUILD_DIR)/$(PROJECT).elf $(LD_SCRIPT)
	@echo Creating $@
	@$(HEX) $< $@

$(BUILD_DIR)/$(PROJECT).bin : $(BUILD_DIR)/$(PROJECT).elf $(LD_SCRIPT)
	@echo Creating $@
	@$(BIN) $< $@

$(BUILD_DIR)/$(PROJECT).dmp : $(BUILD_DIR)/$(PROJECT).elf $(LD_SCRIPT)
	@echo Creating $@
	@$(OD) $(ODFLAGS) $< > $@
	@echo
	@$(SZ) $<
	@echo
	@echo Done

.PHONY: flash
flash: $(FLASH_SCRIPT) $(OUTFILES)
	@$(FLASH) $(FLASH_FLAGS) $<

.PHONY: eflash
eflash: $(EFLASH_SCRIPT) $(OUTFILES)
	@$(FLASH) $(FLASH_FLAGS) $<

$(FLASH_SCRIPT): $(MAKEFILE_LIST) | $(BUILD_DIR)
	@echo "connect"                              >  $@
ifneq ($(SOFTDEVICE),)
	@echo "loadfile $(SOFTDEVICE)"               >> $@
endif
	@echo "loadfile $(BUILD_DIR)/$(PROJECT).hex" >> $@
	@echo "r"                                    >> $@
	@echo "g"                                    >> $@
	@echo "exit"                                 >> $@

$(EFLASH_SCRIPT): $(MAKEFILE_LIST) | $(BUILD_DIR)
	@echo "connect"                              >  $@
	@echo "erase"                                >> $@
ifneq ($(SOFTDEVICE),)
	@echo "loadfile $(SOFTDEVICE)"               >> $@
endif
	@echo "loadfile $(BUILD_DIR)/$(PROJECT).hex" >> $@
	@echo "r"                                    >> $@
	@echo "g"                                    >> $@
	@echo "exit"                                 >> $@

.PHONY: clean
clean:
	@echo Cleaning
	@echo
	rm -rf $(BUILD_DIR)
	@echo

# Include the dependency files, should be last non-comment line
-include $(wildcard $(DEPDIR)/*)
