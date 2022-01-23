#############################################################################
# dump
#############################################################################
.PHONY: dump
dump : $(EXECS).dump #  $(EXECS).dumpUW
$(EXECS).dump : $(EXECS).$(EXE_EXTENSION) link
	@echo Generating an ELF dump
	@$(OBJDUMP) -S -z -w $(TARDIR)/$(EXECS).$(EXE_EXTENSION) --section=.isr_vector --section=.hot --section=.text >$(TARDIR)/$(EXECS).dump
	@echo Done


#############################################################################
# symbols
#############################################################################
.PHONY: symbols
symbols : $(EXECS).symbols
$(EXECS).symbols : $(EXECS).$(EXE_EXTENSION) link
	@echo Generating the table of symbols
	@$(OBJDUMP) -t -w $(TARDIR)/$(EXECS).$(EXE_EXTENSION) >$(TARDIR)/$(EXECS).symbols


#############################################################################
# MAKE VERSION
#############################################################################
.PHONY: versions
versions:
	-@$(MAKE) -version
	-@$(CC) --version
	-@$(GIT) --version
	-@$(CP) --version
	-@$(RM) --version
	-@$(TEE) --version
	-@$(PYTHON) --version --version
	@echo CFLAGS=$(CFLAGS)
ifneq ($(CPP_SRC),)
	@echo CPPFLAGS=$(CPPFLAGS)
endif
	@echo ASFLAGS=$(ASFLAGS)
	@echo LDFLAGS=$(LDFLAGS)
	@echo TIMESTAMP=$(TIMESTAMP)
ifneq ($(GIT_IDENT),)
	@echo GIT_IDENT=$(GIT_IDENT)
endif

#############################################################################
# Memory utilization information
#############################################################################
.PHONY: meminfo
meminfo: $(TARDIR)/$(EXECS).$(MAP_EXTENSION) #build_tools/helpers/alloc_space_info.py
	@echo MemInfo do nothing
#	@$(PYTHON) build_tools/helpers/alloc_space_info.py --map $<


#############################################################################
# DEBUG make target
#############################################################################
.PHONY: debug
debug:
	@$(OBJDUMP) -d -w $(TARDIR)/$(EXECS).$(EXE_EXTENSION) > $(TARDIR)/$(EXECS).asm

	@$(READELF) -e $(TARDIR)/$(EXECS).$(EXE_EXTENSION) > $(TARDIR)/$(EXECS)_headers.txt
	@$(READELF) -x 1 $(TARDIR)/$(EXECS).$(EXE_EXTENSION) > $(TARDIR)/$(EXECS).hex1
	@$(READELF) -x 2 $(TARDIR)/$(EXECS).$(EXE_EXTENSION) > $(TARDIR)/$(EXECS).hex2
	@$(READELF) -x 3 $(TARDIR)/$(EXECS).$(EXE_EXTENSION) > $(TARDIR)/$(EXECS).hex3
	@$(READELF) -x 4 $(TARDIR)/$(EXECS).$(EXE_EXTENSION) > $(TARDIR)/$(EXECS).hex4
	@$(READELF) -x 5 $(TARDIR)/$(EXECS).$(EXE_EXTENSION) > $(TARDIR)/$(EXECS).hex5

	@$(OBJCOPY) -O ihex $(TARDIR)/$(EXECS).$(EXE_EXTENSION) $(TARDIR)/$(EXECS)_intelhex.hex
	@$(OBJCOPY) -O srec $(TARDIR)/$(EXECS).$(EXE_EXTENSION) $(TARDIR)/$(EXECS)_motorola.srec

#############################################################################
# size informations
#############################################################################
.PHONY: baseInfo
baseInfo: versions $(EXECS).$(EXE_EXTENSION)
	@$(SIZE) $(SIZEFLAGS) $(TARDIR)/$(EXECS).$(EXE_EXTENSION)
#size :Here I have the code size (text), constant data (data) and global variables or statically allocated variables (bss),
#      all in hexadecimal. The sum of text+data+bss is shown in dec(imal) and hex(adecimal).

#############################################################################
# HELP make target to describe other effective targets
#############################################################################
.PHONY: help
help: userHelp baseHelp

.PHONY: baseHelp
baseHelp:
	@echo +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	@echo  Available targets are
	@echo +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	@echo  all:     Build all sources and link them (the default target)
	@echo  clean:   Remove all temporary build products - logs, object files, map and exe files
	@echo +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

