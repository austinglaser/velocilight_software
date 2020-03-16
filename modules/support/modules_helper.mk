################################################################################
# Modules Helper Utilities                                                     #
#                                                                              #
# Provides utilities to help simplify module inclusion                         #
################################################################################

include $(MODULES_DIR)/support/gmsl

append_to       = $(eval $(call uc,$1)_$3 += $($(call uc,$2)_$3))

should_include  = $(call seq,yes,$(USE_$(call uc,$1)))

mk_include      = $(eval include $1/$(call lc,$2)/$(call lc,$2).mk)

module_include  = $(if $(call should_include,$2),              \
                      $(call mk_include,$1,$2)                 \
                      $(call append_to,MODULES,$2,INC)         \
                      $(call append_to,MODULES,$2,SRC)         \
                      $(call append_to,MODULES,$2,ASM)         \
                      $(call append_to,MODULES,$2,DEF)         \
                      $(call append_to,MODULES,$2,TEST)        \
                      $(call append_to,MODULES,$2,TESTDEF)     \
                      $(call append_to,MODULES,$2,TESTSUPPORT) \
                      $(call append_to,MODULES,$2,TESTHELPERS))

module          = $(call module_include,$(strip $1),$(strip $2))
