#############################################################################
# ALL make target to build a program
#############################################################################

.PHONY : all all2 all3 nocheck
all: pre
	$(MAKE) user_pre_compilation | $(TEE) -a $(TARDIR)/$(EXECS).log
	$(MAKE) all2
	$(MAKE) post | $(TEE) -a $(TARDIR)/$(EXECS).log

all2:
ifeq ($(CORTEX_Mx), )
	$(error CORTEX_Mx must be defined in user part of Makefile)
endif
	$(MAKE) builddir | $(TEE) -a $(TARDIR)/$(EXECS).log
	$(MAKE) all3 -j$(THREADS) | $(TEE) -a $(TARDIR)/$(EXECS).log

all3: link dump meminfo symbols

nocheck:
	$(MAKE) pre
	$(MAKE) dump
	$(MAKE) symbols

.PHONY : link
link: $(EXECS).hex baseInfo userInfo

#############################################################################
# Pre-compilation tasks:
#############################################################################

WINBUILDDIR=$(subst /,\,$(BUILDDIR))
WINTARDIR=$(subst /,\,$(TARDIR))

.PHONY: builddir
builddir:
	@echo Build DIR $(WINBUILDDIR), Target DIR $(WINTARDIR)
	@if not exist $(WINBUILDDIR) mkdir $(WINBUILDDIR)
	@if not exist $(WINTARDIR) mkdir $(WINTARDIR)

.PHONY: pre
pre: builddir $(BUILD_IDENT_H)
	@echo Build PRE
	@echo USERNAME=$(USERNAME) | $(TEE) $(TARDIR)/$(EXECS).log
	@echo USERNAME_CLEAN=$(USERNAME_CLEAN) | $(TEE) -a $(TARDIR)/$(EXECS).log
	@echo CFLAGS=$(CFLAGS) | $(TEE) -a $(TARDIR)/$(EXECS).log

.PHONY: FORCE
$(BUILD_IDENT_H): FORCE
	@echo Build FORCE
