#############################################################################
# Build flags and switches
#############################################################################


LINKER_OPTIMIZATION ?= -Wl,--gc-sections
# to debug try this: LINKER_OPTIMIZATION = -Wl,--gc-sections,--print-gc-sections


#############################################################################
# get informations from git
#############################################################################
GIT_IDENT?= $(shell git rev-parse --verify HEAD)

GIT_CHANGES=$(shell git diff --name-status)
ifneq ($(GIT_CHANGES),)
GIT_IDENT+=+
endif

export GIT_IDENT

#############################################################################
# Time stamps- ISO8601
# https://en.wikipedia.org/wiki/ISO_8601
#############################################################################
TIMESTAMP?=$(shell $(PYTHON) -c "exec(\"import datetime\nprint(datetime.datetime.now(datetime.timezone.utc).isoformat('T','seconds'))\")")
TIMESTAMP:=$(TIMESTAMP)
export TIMESTAMP

ifneq ($(TIMESTAMP),)
  TS_YEAR:=$(shell $(PYTHON) -c "exec(\"import datetime\nprint(datetime.datetime.fromisoformat('$(TIMESTAMP)').year) \")")
  TS_MONTH:=$(shell $(PYTHON) -c "exec(\"import datetime\nprint(datetime.datetime.fromisoformat('$(TIMESTAMP)').month) \")")
  TS_MDAY:=$(shell $(PYTHON) -c "exec(\"import datetime\nprint(datetime.datetime.fromisoformat('$(TIMESTAMP)').day) \")")
  TS_HOUR:=$(shell $(PYTHON) -c "exec(\"import datetime\nprint(datetime.datetime.fromisoformat('$(TIMESTAMP)').hour) \")")
  TS_MIN:=$(shell $(PYTHON) -c "exec(\"import datetime\nprint(datetime.datetime.fromisoformat('$(TIMESTAMP)').minute) \")")
  TS_SEC:=$(shell $(PYTHON) -c "exec(\"import datetime\nprint(datetime.datetime.fromisoformat('$(TIMESTAMP)').second) \")")
  export S_YEAR TS_MONTH TS_MDAY TS_HOUR TS_MIN TS_SEC
endif

#############################################################################
#
#############################################################################

LDSCRIPT?=$(error Error:LDSCRIPT is not defined!)
CPUMODE?=$(error Error:CPUMODE is not defined!)

#############################################################################
# optimalization options
# Align functions to 8 byte (minor speed up)
#############################################################################

#OPTIM_LEVEL += -O2

#ifeq ($(ALIGN_FUNCTIONS),1)
#	OPTIM_LEVEL += -falign-functions=8
#endif

#Options Controlling the Preprocessor - https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html
#Options to Request or Suppress Warnings - https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

  # -g: Produce debugging information
  # -Wa,option: Pass option as an option to the assembler
  # -adhln:
  #  a: turn on listings
  #  d: omit debugging directives; n: omit forms processing
  #  h: include high-level source
  #  l: include assembly
  CPPFLAGS+= $(CPUMODE) -Wall -Wundef #-fomit-frame-pointer
  #CPPFLAGS+= -Wa,-adhln -g
#MZ  CPPFLAGS+= -g -Wa,-a,-ad
  #CPPFLAGS+=-save-temps
  CPPFLAGS+= -fno-strict-aliasing -MD
  CPPFLAGS+= -DCHAR_BIT=8
  CPPFLAGS+= $(OPTIM_LEVEL)
  CPPFLAGS+= $(SW_APP_DEFINES)
  CPPFLAGS+= $(USR_DEFINES)
  CPPFLAGS+= $(USERCFLAGS)

ifeq ($(STACK_REPORT),1)
  CPPFLAGS+= -fstack-usage
endif

#  CPPFLAGS += -fno-unwind-tables
  CPPFLAGS += -DCPP_EXCEPTIONS=$(CPP_EXCEPTIONS) -DUSE_CPP_EXCEPTIONS=$(CPP_EXCEPTIONS)

  CFLAGS= $(CPPFLAGS)
# Options Controlling C Dialect -https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html
  CFLAGS+=-std=gnu11
#Options to Request or Suppress Warnings - https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
  CFLAGS+=-Werror=incompatible-pointer-types

  ASFLAGS+= $(CPUMODE) -x assembler-with-cpp -MD
  ASFLAGS+= -DCHAR_BIT=8
  ASFLAGS+= $(USR_DEFINES)
  ASFLAGS+= $(USERCFLAGS)
  ASFLAGS+= $(OPTIM_LEVEL)
ifeq ($(POKE_FUNCTION_NAMES),1)
  ASFLAGS+= -DASM_POKE_FUNCTION_NAME
endif

#  arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -ffunction-sections
#                    -fdata-sections  -g3 -T ../Drivers/Target/STM32F0xx/linker/STM32F030C8x_flash.ld -Xlinker
#                    --gc-sections -Wl,-Map,"MM003-SHT.map" -Xlinker --cref -Wl,-gc-sections
#                    -o "MM003-SHT.elf" $(OBJS) $(USER_OBJS) $(LIBS)

# ---------
# -fdata-sections  -g3 -T ../Drivers/Target/STM32F0xx/linker/STM32F042C4Tx_FLASH.ld
# -Xlinker --gc-sections -Wl,-Map,"MM004-CanOpen.map"
# -Xlinker --cref --specs=nano.specs --specs=nosys.specs
# -Wl,-gc-sections -o "MM004-CanOpen.elf"  ./Drivers/thirdparty/freertos/portable/MemMang/heap_1.o  ./Drivers/thirdparty/freertos/portable/GCC/ARM_CM0/port.o   ...atd...
# ---------
  LDFLAGS= $(CPUMODE) -g3 -Xlinker --gc-sections -Wl,-Map,$(TARDIR)/$(EXECS).$(MAP_EXTENSION),-n,-gc-sections
# .ld script should be passed to linker directly as "-T<path>"
# instead of "-Wl,-T<path>", to avoid 1K RAM loss for ".data.impure_data"
  LDFLAGS+=-T $(LDSCRIPT)
#  LDFLAGS+= -Wl,--no-wchar-size-warning,--cref
  LDFLAGS+= $(LINKER_OPTIMIZATION)
  LDFLAGS+= $(OPTIM_LEVEL)
#  LDFLAGS+= $(UNWIND_LDFLAGS)

LDSPECS?= -Xlinker --cref \
   -specs=nano.specs \
   -specs=nosys.specs
  # -specs=rdimon.specs

 LDFLAGS+= $(LDSPECS)

#Gcc >= 8
  GCCGEN=$(word 1, $(subst ., ,$(GCC_DUMPVERSION)))
  ifeq ($(shell expr $(GCCGEN) \>= 8), 1)
    LDFLAGS+= -mbe32
  else
    CPPFLAGS+= -mstructure-size-boundary=8
  endif

SIZEFLAGS?=--format=berkeley --totals
