################################################################################
# Ceedling makefile                                                            #
################################################################################

# --- DIRECTORIES ------------------------------------------------------------ #

CEEDLING_DIR	:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
SCRIPTS_DIR	:= $(CEEDLING_DIR)/scripts

# --- CONFIG VALIDATION ------------------------------------------------------ #

ifeq ($(CEEDLING_BUILDDIR),)
    $(error CEEDLING_BUILDDIR must be set)
endif

ifeq ($(TESTBASECONFIG),)
    $(error TESTBASECONFIG must be set)
endif

# --- HELPERS ---------------------------------------------------------------- #

empty   :=
space   := $(empty) $(empty)
comma   := ,

# --- FILES ------------------------------------------------------------------ #

CEEDDEFINES     := $(subst $(space),$(comma),$(sort $(TESTDEF)))
CEEDSOURCEDIRS  := $(subst $(space),$(comma),$(sort $(dir $(TESTSRC)) $(addsuffix /,$(TESTINC))))
CEEDTESTDIRS    := $(subst $(space),$(comma),$(sort $(addsuffix /,$(TESTTEST))))
CEEDSUPPORTDIRS := $(subst $(space),$(comma),$(sort $(addsuffix /,$(TESTSUPPORT))))
CEEDHELPERS     := $(subst $(space),$(comma),$(sort $(TESTHELPERS)))

# --- CONFIGURATION ---------------------------------------------------------- #

PATHCONF    := $(SCRIPTS_DIR)/ceedling-configurator.py
TEST_CONFIG := $(CEEDLING_BUILDDIR)/project.yml

PATHCONF_ARGS   := --source-paths="$(CEEDSOURCEDIRS)" \
                   --test-paths="$(CEEDTESTDIRS)" \
                   --support-paths="$(CEEDSUPPORTDIRS)" \
                   --build-dir="$(CEEDLING_BUILDDIR)" \
                   --define="$(CEEDDEFINES)" \
                   --unity-helpers="$(CEEDHELPERS)"

ifeq ($(USE_C_EXCEPTION),yes)
PATHCONF_ARGS += --cexception-dir="$(dir $(C_EXCEPTION_DIR))"
endif

# --- RULES ------------------------------------------------------------------ #

ceedling-test: $(TEST_CONFIG) | $(CEEDLING_BUILDDIR)
	@CEEDLING_MAIN_PROJECT_FILE=$(TEST_CONFIG) rake test:all

ceedling-coverage: $(TEST_CONFIG) | $(CEEDLING_BUILDDIR)
	@CEEDLING_MAIN_PROJECT_FILE=$(TEST_CONFIG) rake gcov:all

$(TEST_CONFIG): $(TESTBASECONFIG) $(MAKEFILE_LIST) | $(CEEDLING_BUILDDIR)
	@$(PATHCONF) $(PATHCONF_ARGS) $< $@

$(CEEDLING_BUILDDIR):
	@mkdir -p $@

ceedling-clean:
	@CEEDLING_MAIN_PROJECT_FILE=$(TEST_CONFIG) rake clean
	@rm -fR $(CEEDLINB_BUILDDIR)
