##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
USE_OPTIMIZATION	:= -O0 -ggdb
ifeq ($(USE_OPT),)
  USE_OPT = $(USE_OPTIMIZATION) -fomit-frame-pointer -falign-functions=16
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT = 
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
  USE_LDOPT = -lm
endif

# Enable this if you want link time optimizations (LTO)
ifeq ($(USE_LTO),)
  USE_LTO = yes
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

# If enabled, this option makes the build process faster by not compiling
# modules not used in the current configuration.
ifeq ($(USE_SMART_BUILD),)
  USE_SMART_BUILD = no
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x400
endif

# Stack size to the allocated to the Cortex-M main/exceptions stack. This
# stack is used for processing interrupts and exceptions.
ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
  USE_EXCEPTIONS_STACKSIZE = 0x400
endif

# Enables the use of FPU on Cortex-M4 (no, softfp, hard).
ifeq ($(USE_FPU),)
  USE_FPU = hard
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Imported source files and paths
# NOTE: Platform-specific includes are in board.mk
# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
# RTOS files (optional).
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/rt/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC := $(STARTUPSRC) \
        $(KERNSRC) \
        $(PORTSRC) \
        $(OSALSRC) \
        $(HALSRC) \
        $(PLATFORMSRC) \
        $(MODULES_SRC) \
        $(BOARD_SRC) \
        $(DRIVER_SRC) \
        $(CHIBIOS)/os/hal/lib/streams/chprintf.c \
        $(APP_SRC)

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC :=

# C sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACSRC :=

# C++ sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACPPSRC :=

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCSRC :=

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCPPSRC :=

# List ASM source files here
ASMSRC := $(STARTUPASM) $(PORTASM) $(OSALASM) \
          $(BOARD_ASM) \
          $(DRIVER_ASM) \
          $(APP_ASM)

INCDIR := $(STARTUPINC) $(KERNINC) $(PORTINC) $(OSALINC) \
          $(HALINC) $(PLATFORMINC) \
          $(CHIBIOS)/os/various \
          $(CHIBIOS)/os/hal/lib/streams \
          $(MODULES_INC) \
          $(BOARD_INC) \
          $(DRIVER_INC) \
          $(APP_INC)

#
# Project, sources and paths
##############################################################################

##############################################################################
# Test configuration
#

TESTBASECONFIG := $(SUPPORT_DIR)/ceedling.yml

TESTSRC := $(MODULES_SRC) \
           $(MODULES_CHIBIOS_SRC) \
           $(DRIVER_SRC) \
           $(APP_SRC)

TESTINC	:= $(MODULES_INC) \
           $(DRIVER_INC) \
           $(APP_INC) \
           $(BOARD_INC) \
           $(STARTUPINC) $(KERNINC) $(PORTINC) $(OSALINC) \
           $(HALINC) $(PLATFORMINC)

TESTTEST := $(MODULES_TEST) \
            $(MODULES_CHIBIOS_TEST) \
            $(DRIVER_TEST) \
            $(APP_TEST)

TESTDEF  := $(MODULES_TESTDEF) \
            $(DRIVER_TESTDEF) \
            $(APP_TESTDEF)

TESTSUPPORT := $(MODULES_TESTSUPPORT) \
               $(DRIVER_TESTSUPPORT) \
               $(APP_TESTSUPPORT)

#
# Test configuration
##############################################################################

##############################################################################
# Compiler settings
#

MCU  = $(BOARD_MCU)

#TRGT = arm-elf-
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
LD   = $(TRGT)gcc
#LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
AR   = $(TRGT)ar
OD   = $(TRGT)objdump
SZ   = $(TRGT)size
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT =

# THUMB-specific options here
TOPT = -mthumb -DTHUMB

# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes

# Define C++ warning options here
CPPWARN = -Wall -Wextra

#
# Compiler settings
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS = $(BOARD_DEF) $(DRIVER_DEF) $(TEST_DEF) $(APP_DEF) \
        -DENSURE_MODE=ENSURE_MODE_C_EXCEPTION
ifeq ($(DEBUG), true)
UDEFS += -DDEBUG
endif

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR =

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

#
# End of user defines
##############################################################################

release: all

RULESPATH = $(MODULES_DIR)/chibios/rules
include $(RULESPATH)/rules.mk

test: ceedling-test
coverage: ceedling-coverage

TESTPATH := $(MODULES_DIR)/ceedling
include $(TESTPATH)/rules.mk
