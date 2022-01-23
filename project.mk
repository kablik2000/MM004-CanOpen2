#############################################################################
# Target and translator setting
#############################################################################
CORTEX_Mx?=0

BUILD_DATE_ISO8601?=00000
VERSION?=12.3

OPTIM_LEVEL=-O0
#arm-none-eabi-gcc  -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -ffunction-sections
#                   -fdata-sections  -g3 -DUSE_FULL_LL_DRIVER -DARM_MATH_CM0 -DSTM32F030x8 -DSTM32F030x6
#                   -std=gnu11 -Wstrict-prototypes -ffunction-sections -MMD -MP
#                   -MF"Drivers/api-generic/time/alarmtimer.d"
#                   -MT"Drivers/api-generic/time/alarmtimer.o"
#                   -c -o "Drivers/api-generic/time/alarmtimer.o" "../Drivers/api-generic/time/alarmtimer.c"

  USERCFLAGS =-DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DARM_MATH_CM0 -DFREERTOS_USED
  USERCFLAGS +=-D__CORTEX_SC # req. by Drivers/Target/CMSIS/STM32F0xx/cmsis_gcc.h
  USERCFLAGS +=-DVECT_TAB_OFFSET=0x0
  USERCFLAGS +=-fmessage-length=0 -ffunction-sections -fdata-sections  -g3
#LDSPECS= -static -specs=nano.specs -specs=nosys.specs

SW_IDENT=TP2100063
PROJ_IDENT=MM004
HELP_STRING=CanOpen

MCU_DEVICE=STM32F042x6

#############################################################################
# SW components identification
#############################################################################

USR_DEFINES += $(IDENT_DEFINES)

#############################################################################
# Program (*.out / *.elf) name
#############################################################################

EXECS_BASE=$(SW_IDENT)_$(PROJ_IDENT)-$(HELP_STRING)_$(VERSION)

ifeq ($(TARGET),release)
  EXECS=$(EXECS_BASE)_$(BUILD_DATE_ISO8601)
else
  EXECS=$(EXECS_BASE)_DEBUG
endif

#############################################################################
# Include headers
#############################################################################
INCLUDE=-IApplication/
INCLUDE+=-IApplication/config/
INCLUDE+=-IUtils/
INCLUDE+=-IDrivers/Common/
INCLUDE+=-IDrivers/BSP/
INCLUDE+=-IDrivers/System/
INCLUDE+=-IDrivers/BSP/Common/
INCLUDE+=-IDrivers/api-generic/
INCLUDE+=-IDrivers/api-generic

## Drivers/Common/tmdio

#############################################################################
# API - Makefile files
#############################################################################

STM32_LIBDIR:=${CURDIR}/Drivers/STM32F0xx
export STM32_LIBDIR

FREERTOS_LIBDIR:=${CURDIR}/Drivers/thirdparty/freertos
export FREERTOS_LIBDIR

include $(STM32_LIBDIR)/make/STM32F0xx.mk
include $(FREERTOS_LIBDIR)/make/freertos.mk

INCLUDE+=$(STM32_LIB_INCLUDES)\
         $(FREERTOS_LIB_INCLUDES)

#############################################################################
# C sources
#############################################################################
## MCU periphery related sources
C_SRC=  Application/main.c \
        Application/stm32f0xx_it.c \
        Application/init.c

C_SRC+= \
        Drivers/BSP/boards/mm004/system_stm32f0xx.c \
        Drivers/BSP/boards/mm004/board_gpio.c \
        Drivers/System/cpu_utils.c \
        Drivers/System/dbg_fnc.c \
        Drivers/Common/delay.c

C_SRC+= \
        $(STM32_LIB_C_SRC) \
        $(FREERTOS_LIB_C_SRC)




#############################################################################
# Asm sources
#############################################################################

#ASM_SRC= Drivers/Target/STM32F0xx/startup/startup_stm32f030x8.S
ASM_SRC= \
        $(STM32_LIB_ASM_SRC)

#############################################################################
# Libraries
#############################################################################
# directory path to the object files to allow
# using only *.C and *.obj module name without a relative path
# within the linker script *.ld (to reside the module into a memory section)
LIBDIR=-L$(OBJDIR)

# user-specific libs
LIBDIR+=-Llib


# directory path to the object files to allow
# using only *.C and *.obj module name without a relative path
# within the linker script *.ld (to reside the module into a memory section)
LIBDIR+=-L$(OBJDIR)


#build/api.h: $(CARMEN_API_PATH)/api.mk
#	@$(PYTHON) -c "exec(\"print ('#ifndef API_H\\n#define API_H\\n\\n#define API_VERSION $(API_VERSION)u\\n\\n#endif /* API_H */\\n')\")" > $@

#############################################################################
# Linker script - code running from FLASH / ROM
#############################################################################

#LDSCRIPT=Drivers/Target/STM32F0xx/linker/STM32F030C8x_flash.ld
LDSCRIPT=Drivers/STM32F0xx/linker/STM32F042C4Tx_FLASH.ld

#############################################################################
# Delete user files
#############################################################################
.PHONY : user_clean
user_clean:
	@echo User clean


#############################################################################
# Pre compilation code
#############################################################################
 .PHONY: user_pre_compilation
user_pre_compilation: stm32_lib_pre_compilation freertos_lib_pre_compilation
	@echo User pre compilation

#############################################################################
# user part of post_compilation
#############################################################################
.PHONY: user_post_compilation
user_post_compilation:
	@echo User post compilation

#############################################################################
# Add information into buildlog after compilation
#############################################################################
.PHONY : userInfo
userInfo:
	@echo VERSION = $(VERSION)
	@echo OPTIMIZATION = $(OPTIM_LEVEL)

############################################################################
# Release build
############################################################################
.PHONY : release
release:
	$(MAKE) clean
	$(MAKE) TARGET=release

### EOF ###
