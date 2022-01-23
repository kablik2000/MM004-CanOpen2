ifneq ($(CORTEX_Mx),4)
endif

# add floating point unit and endianity flags to CPUMODE according the CPU type
    CPUMODE ?= -mcpu=cortex-m4
    CPUMODE+= -mfloat-abi=hard
    ASFLAGS ?= -DCPUTYPE_ARM_M4=1 -DCPUTYPE_ARM_M=1 -DSTM32G474xx=1
    CPPFLAGS ?= -DCPUTYPE_ARM_M4=1 -DCPUTYPE_ARM_M=1 -DSTM32G474xx=1