#############################################################################
# Default target (has to be the first one found)
#############################################################################
.PHONY : default
default:
	$(MAKE) all

#############################################################################
# Set default Variables
#############################################################################

SHELL=cmd.exe

EXE_EXTENSION = elf
MAP_EXTENSION = map

############################################################
# Default definition of build tools
############################################################
MACH ?= arm-none-eabi-
ifeq ($(CPP),cc -E)
CPP = $(MACH)g++
endif
ifeq ($(CC),cc)
CC = $(MACH)gcc
endif
ifeq ($(AS),as)
AS = $(MACH)as
endif
ifeq ($(LD),ld)
LD = $(MACH)gcc
endif
## nm - list symbols from object files
NM = $(MACH)nm
## The gnu objcopy utility copies the contents of an object file to another
OBJCOPY = $(MACH)objcopy
OBJDUMP = $(MACH)objdump
READELF = $(MACH)readelf
SIZE = $(MACH)size

############################################################
# Default definition of tools
############################################################
# GNU and other exernal tools
CAT ?= cat
CP ?= cp -v
MV ?= mv -f
PYTHON ?= python
RM ?= rm -fv
TEE ?= tee
ZIP ?= zip -X
GIT ?= git

#############################################################################
# Working directories
#############################################################################
BUILDDIR_ROOT ?= Build
BUILDDIR ?= $(BUILDDIR_ROOT)/$(TARGET)
ASMDIR ?= $(BUILDDIR)/asm
LSTDIR ?= $(BUILDDIR)/lst
OBJDIR ?= $(BUILDDIR)/obj
DISTDIR ?= Dist
TARDIR ?= $(DISTDIR)/$(TARGET)

USR_HOME_PATH ?= $(HOMEDRIVE)$(HOMEPATH)
#############################################################################
# Time stamps and related garbage
#############################################################################

# TODO
