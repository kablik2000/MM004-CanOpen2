#############################################################################
# C objects
#############################################################################
FILE_C_SRC = $(notdir $(C_SRC))
DIR_C_SRS = $(dir $(C_SRC))
C_OBJ = $(patsubst %.c, $(BUILDDIR)/%.o, $(FILE_C_SRC))
DEPEND = $(patsubst %.c, $(BUILDDIR)/%.d, $(FILE_C_SRC))
vpath %.c $(DIR_C_SRS)

#############################################################################
# CPP objects
#############################################################################
FILE_CPP_SRC = $(notdir $(CPP_SRC))
DIR_CPP_SRS = $(dir $(CPP_SRC))
CPP_OBJ = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(FILE_CPP_SRC))
DEPEND += $(patsubst %.cpp, $(BUILDDIR)/%.d, $(FILE_CPP_SRC))
vpath %.cpp $(DIR_CPP_SRS)

#############################################################################
# Asm objects
#############################################################################
FILE_ASM_SRC = $(notdir $(ASM_SRC))
DIR_ASM_SRS = $(dir $(ASM_SRC))
ASM_OBJ = $(patsubst %.S, $(BUILDDIR)/%.o, $(FILE_ASM_SRC))
DEPEND += $(patsubst %.S, $(BUILDDIR)/%.d, $(FILE_ASM_SRC))
vpath %.S $(DIR_ASM_SRS)

#############################################################################
# All objects and their fellows
#############################################################################
OBJ = $(C_OBJ) $(CPP_OBJ) $(ASM_OBJ)
LST = $(OBJ:.o=.o.lst)
DEP = $(OBJ:.o=.d)

#############################################################################
# Compiling and Assembling
#############################################################################
$(C_OBJ): $(BUILDDIR)/%.o: %.c
	@echo 'Building target: $@'
	@echo Compiling $<
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@ > $@.lst
	@echo 'Finished building target: $@'

$(CPP_OBJ): $(BUILDDIR)/%.o: %.cpp
	@echo 'Building target: $@'
	@echo Compiling $<
	@$(CPP) -c $(CPPFLAGS) $(USERCPPFLAGS) $(INCLUDE) $< -o $@ > $@.lst

$(ASM_OBJ): $(BUILDDIR)/%.o: %.S
	@echo Assembling $<
	@$(CC) -c $(ASFLAGS) $(INCLUDE) $< -o $@

#############################################################################
# Linking
#############################################################################
# Direct gcc to pass such options through to ld when it invokes the
# linker by using the the gcc option -Wl, which has the usage:
# -Wl,<ld-option>[,<ld-option>...]
#############################################################################
$(EXECS).$(EXE_EXTENSION) : depend $(OBJ) $(LDSCRIPT)
	@echo Linking $@
	@echo @$(LD) -o $(TARDIR)/$@ $(LDFLAGS) $(LIBDIR) $(OBJ) $(LIBS)
	@$(LD) -o $(TARDIR)/$@ $(LDFLAGS) $(LIBDIR) $(OBJ) $(LIBS)

$(TARDIR)/$(EXECS).$(MAP_EXTENSION) : $(EXECS).$(EXE_EXTENSION)
	@echo Making $(TARDIR)/$(EXECS).$(MAP_EXTENSION)
# formally it is generated together by $(LD)

#############################################################################
# Output
#############################################################################

#############################################################################
# hex
#############################################################################

$(EXECS).hex : $(EXECS).$(EXE_EXTENSION)
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	@echo Creating the final Intel HEX: $@
	@$(OBJCOPY) -O ihex $(TARDIR)/$(EXECS).$(EXE_EXTENSION) $(BUILDDIR)/$(EXECS).hex
	cp $(BUILDDIR)/$(EXECS).hex $(TARDIR)/$(EXECS).hex
	@echo 'Finished building: $@'

#############################################################################
# hex
#############################################################################

$(EXECS).hex : $(EXECS).$(EXE_EXTENSION)