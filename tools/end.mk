############################################################
#               main make include                          #
############################################################

# Default definitions
TARGET ?= debug

TOPDIR?=$(error Error: TOPDIR is not defined!)

GCC_DUMPVERSION :=$(shell $(CC) -dumpversion)

#############################################################################
# optimalization options
# Align functions to 8 byte (minor speed up)
#############################################################################




#############################################################################
# includes
#############################################################################

ifeq ($(CORTEX_Mx),4)
  include ${TOPDIR}/cortex_m4.mk
endif

include ${TOPDIR}/default.mk
include ${TOPDIR}/clean.mk
include ${TOPDIR}/targets.mk
include ${TOPDIR}/compiler.mk
include ${TOPDIR}/ident.mk
include ${TOPDIR}/info.mk


#############################################################################
# Dependency tree
# Note: workaround for filtering of possible \:\ in Windows paths added
#############################################################################
.PHONY : depend
depend: $(C_OBJ) $(CPP_OBJ) $(ASM_OBJ) $(USR_DEPENDS)
	@echo Creating the dependency tree...
	@cat $(DEPEND) $(USR_DEPENDS) | $(PYTHON) -c "exec(\"import sys\nfor line in sys.stdin:\n    sys.stdout.write(line.replace(r'\:\', r':\'))\")">$(BUILDDIR)/.depend

-include $(BUILDDIR)/.depend


#############################################################################
# Post-linkage tasks:
#############################################################################
.PHONY: post
post:
	$(MAKE) user_post_compilation
