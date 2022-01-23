#############################################################################
# Auxiliary symbols and variables
#############################################################################

STM32_LIB_PATH:=$(STM32_LIBDIR)
STM32_LIB_LL_PATH?=$(STM32_LIB_PATH)/STM32F0xx_LL_Driver
STM32_LIB_HAL_PATH?=$(STM32_LIB_PATH)/STM32F0xx_HAL_Driver


#############################################################################
#
#############################################################################

MCU_DEVICE?=$(error Select first the target STM32F0xx device used in your application!)

ifeq ($(MCU_DEVICE),STM32F030x6)
endif
ifeq ($(MCU_DEVICE),STM32F030x8)
endif
ifeq ($(MCU_DEVICE),STM32F031x6)
endif
ifeq ($(MCU_DEVICE),STM32F038xx)
endif
ifeq ($(MCU_DEVICE),STM32F042x6)
endif
ifeq ($(MCU_DEVICE),STM32F048xx)
endif
ifeq ($(MCU_DEVICE),STM32F051x8)
endif
ifeq ($(MCU_DEVICE),STM32F058xx)
endif
ifeq ($(MCU_DEVICE),STM32F070x6)
endif
ifeq ($(MCU_DEVICE),STM32F070xB)
endif
ifeq ($(MCU_DEVICE),STM32F071xB)
endif
ifeq ($(MCU_DEVICE),STM32F072xB)
endif
ifeq ($(MCU_DEVICE),STM32F078xx)
endif
ifeq ($(MCU_DEVICE),STM32F091xC)
endif
ifeq ($(MCU_DEVICE),STM32F098xx)
endif
ifeq ($(MCU_DEVICE),STM32F030xC)
endif

#############################################################################
# Include headers
#############################################################################
STM32_LIB_INCLUDES= \
      -I$(STM32_LIB_PATH)/\
      -I$(STM32_LIB_PATH)/Core/\
      -I$(STM32_LIB_PATH)/Device/\
      -I$(STM32_LIB_HAL_PATH)/Inc/\
      -I$(STM32_LIB_LL_PATH)/Inc/

#############################################################################
# C Library sources
#############################################################################

# LowLevel library
STM32_LIB_C_SRC= \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_usart.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_utils.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_rcc.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_rtc.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_spi.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_tim.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_gpio.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_i2c.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_pwr.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_crs.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_dac.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_dma.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_exti.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_adc.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_comp.c \
        $(STM32_LIB_LL_PATH)/Src/stm32f0xx_ll_crc.c

# HAL library

ifeq ($(HAL_RCC_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_rcc.c
endif

ifeq ($(HAL_GPIO_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_gpio.c
endif

ifeq ($(HAL_DMA_MODULE_ENABLED),1)
 STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_dma.c
endif

ifeq ($(HAL_CORTEX_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_cortex.c
endif

ifeq ($(HAL_ADC_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_adc.c
endif

ifeq ($(HAL_CAN_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_can.c
endif

ifeq ($(HAL_CEC_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_cec.c
endif

ifeq ($(HAL_COMP_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_comp.c
endif

ifeq ($(HAL_CRC_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_crc.c
endif

ifeq ($(HAL_DAC_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_dac.c
endif

ifeq ($(HAL_FLASH_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_flash.c
endif

ifeq ($(HAL_I2C_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_i2c.c
endif

ifeq ($(HAL_I2S_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_i2s.c
endif

ifeq ($(HAL_IRDA_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_irda.c
endif

ifeq ($(HAL_IWDG_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_iwdg.c
endif

ifeq ($(HAL_PCD_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_pcd.c
endif

ifeq ($(HAL_PWR_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_pwr.c
endif
ifeq ($(HAL_RTC_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_rtc.c
endif

ifeq ($(HAL_SMARTCARD_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_smartcard.c
endif

ifeq ($(HAL_SMBUS_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_smbus.c
endif

ifeq ($(HAL_SPI_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_spi.c
endif

ifeq ($(HAL_TIM_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_tim.c
endif

ifeq ($(HAL_TSC_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_tsc.c
endif

ifeq ($(HAL_UART_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_uart.c
endif

ifeq ($(HAL_USART_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_usart.c
endif

ifeq ($(HAL_WWDG_MODULE_ENABLED),1)
STM32_LIB_C_SRC+=$(STM32_LIB_HAL_PATH)/src/stm32f0xx_hal_wwdg.c
endif

#############################################################################
# CPP sources
#############################################################################

STM32_LIB_CPP_SRC?=

#############################################################################
# Asm sources
#############################################################################

ifeq ($(MCU_DEVICE),STM32F030x6)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f030x6.S
endif
ifeq ($(MCU_DEVICE),STM32F030x8)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f030x8.S
endif
ifeq ($(MCU_DEVICE),STM32F031x6)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f031x6.S
endif
ifeq ($(MCU_DEVICE),STM32F038xx)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f038xx.S
endif
ifeq ($(MCU_DEVICE),STM32F042x6)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f042x6.S
endif
ifeq ($(MCU_DEVICE),STM32F048xx)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f048xx.S
endif
ifeq ($(MCU_DEVICE),STM32F051x8)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f051x8.S
endif
ifeq ($(MCU_DEVICE),STM32F058xx)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f058xx.S
endif
ifeq ($(MCU_DEVICE),STM32F070x6)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f070x6.S
endif
ifeq ($(MCU_DEVICE),STM32F070xB)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f070xb.S
endif
ifeq ($(MCU_DEVICE),STM32F071xB)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f071xb.S
endif
ifeq ($(MCU_DEVICE),STM32F072xB)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f072xb.S
endif
ifeq ($(MCU_DEVICE),STM32F078xx)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f078xx.S
endif
ifeq ($(MCU_DEVICE),STM32F091xC)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f091xc.S
endif
ifeq ($(MCU_DEVICE),STM32F098xx)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f098xx.S
endif
ifeq ($(MCU_DEVICE),STM32F030xC)
  STM32_LIB_ASM_SRC= $(STM32_LIB_PATH)/startup/startup_stm32f030xc.S
endif

#############################################################################
#
#############################################################################

CORTEX_Mx:=0

# add thumb instructions flags to CPUMODE
# add floating point unit and endianity flags to CPUMODE according the CPU type
CPUMODE:= -mcpu=cortex-m0 -mthumb -mfloat-abi=soft


STM32_LIB_ASFLAGS:= -DCPUTYPE_ARM_M0=1 -DCPUTYPE_ARM_M=0 -D$(MCU_DEVICE)=1
STM32_LIB_CFLAGS:= $(ASFLAGS)

#############################################################################
#
#############################################################################

STM32_LIB_VERSION:=$(subst -, ,$(shell cd $(STM32_LIB_PATH) && git describe --long --dirty --tags))
STM32_LIB_COMMIT:= $(strip $(word 3, $(STM32_LIB_VERSION)))
STM32_LIB_COMMITS_PAST:= $(strip $(word 2, $(STM32_LIB_VERSION)))
STM32_LIB_DIRTY := $(strip $(word 4, $(STM32_LIB_VERSION)))

ifneq ($(STM32_LIB_COMMITS_PAST), 0)
         STM32_LIB_BUILD_INFO_COMMITS := .$(STM32_LIB_COMMITS_PAST)
endif

ifneq ($(STM32_LIB_DIRTY),)
         STM32_LIB_BUILD_INFO_DIRTY :=+
endif

STM32_LIB_VERSION_TAG :=$(strip $(word 1, $(STM32_LIB_VERSION)))
STM32_LIB_BUILD_INFO := $(STM32_LIB_COMMIT)$(STM32_LIB_BUILD_INFO_COMMITS)$(STM32_LIB_BUILD_INFO_DIRTY)
export STM32_LIB_VERSION_TAG STM32_LIB_BUILD_INFO

#############################################################################
# export make target
#############################################################################


.PHONY: stm32_lib_pre_compilation
stm32_lib_pre_compilation:
	@echo STM32_LIB_VERSION = $(STM32_LIB_VERSION)
	@echo STM32_LIB_BUILD_INFO = $(STM32_LIB_BUILD_INFO)
	@echo STM32_LIB_VERSION_TAG = $(STM32_LIB_VERSION_TAG)
	@echo STM32_LIB_PATH = $(STM32_LIB_PATH)
	@echo STM32_LIB_ASM_SRC = $(STM32_LIB_ASM_SRC)
	@echo STM32_LIB_INCLUDES = $(STM32_LIB_INCLUDES)
