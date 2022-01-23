#############################################################################
# Auxiliary symbols and variables
#############################################################################

FREERTOS_LIB_PATH:=$(FREERTOS_LIBDIR)

FREERTOS_LIB_HEAP?=1

#############################################################################
#
#############################################################################

FREERTOS_LIB_C_SRC= \
        $(FREERTOS_LIB_PATH)/croutine.c \
        $(FREERTOS_LIB_PATH)/event_groups.c \
        $(FREERTOS_LIB_PATH)/list.c \
        $(FREERTOS_LIB_PATH)/queue.c \
        $(FREERTOS_LIB_PATH)/stream_buffer.c \
        $(FREERTOS_LIB_PATH)/tasks.c \
        $(FREERTOS_LIB_PATH)/timers.c \
        $(FREERTOS_LIB_PATH)/portable/GCC/ARM_CM0/port.c

# heap_1 - the very simplest, does not permit memory to be freed
ifeq ($(FREERTOS_LIB_HEAP),1)
  FREERTOS_LIB_C_SRC+= $(FREERTOS_LIB_PATH)/portable/MemMang/heap_1.c
endif
# heap_2 - permits memory to be freed, but not does coalescence adjacent free blocks.
ifeq ($(FREERTOS_LIB_HEAP),2)
  FREERTOS_LIB_C_SRC+= $(FREERTOS_LIB_PATH)/portable/MemMang/heap_2.c
endif
# heap_3 - simply wraps the standard malloc() and free() for thread safety
ifeq ($(FREERTOS_LIB_HEAP),3)
  FREERTOS_LIB_C_SRC+= $(FREERTOS_LIB_PATH)/portable/MemMang/heap_3.c
endif
# heap_4 - coalescences adjacent free blocks to avoid fragmentation. Includes absolute address placement option
ifeq ($(FREERTOS_LIB_HEAP),4)
  FREERTOS_LIB_C_SRC+= $(FREERTOS_LIB_PATH)/portable/MemMang/heap_4.c
endif
# heap_5 - as per heap_4, with the ability to span the heap across multiple non-adjacent memory areas
ifeq ($(FREERTOS_LIB_HEAP),5)
  FREERTOS_LIB_C_SRC+= $(FREERTOS_LIB_PATH)/portable/MemMang/heap_5.c
endif

#############################################################################
# Include headers
#############################################################################
FREERTOS_LIB_INCLUDES= \
      -I$(FREERTOS_LIB_PATH)/include/\
      -I$(FREERTOS_LIB_PATH)/portable/GCC/ARM_CM0/


#############################################################################
#
#############################################################################

FREERTOS_LIB_VERSION:=$(subst -, ,$(shell cd $(FREERTOS_LIB_PATH) && git describe --long --dirty --tags))
FREERTOS_LIB_COMMIT:= $(strip $(word 3, $(FREERTOS_LIB_VERSION)))
FREERTOS_LIB_COMMITS_PAST:= $(strip $(word 2, $(FREERTOS_LIB_VERSION)))
FREERTOS_LIB_DIRTY := $(strip $(word 4, $(FREERTOS_LIB_VERSION)))

ifneq ($(FREERTOS_LIB_COMMITS_PAST), 0)
         FREERTOS_LIB_BUILD_INFO_COMMITS := .$(FREERTOS_LIB_COMMITS_PAST)
endif

ifneq ($(FREERTOS_LIB_DIRTY),)
         FREERTOS_LIB_BUILD_INFO_DIRTY :=+
endif

STM32_LIB_VERSION_TAG :=$(strip $(word 1, $(STM32_LIB_VERSION)))
STM32_LIB_BUILD_INFO := $(STM32_LIB_COMMIT)$(STM32_LIB_BUILD_INFO_COMMITS)$(STM32_LIB_BUILD_INFO_DIRTY)
export STM32_LIB_VERSION_TAG STM32_LIB_BUILD_INFO

#############################################################################
# export make target
#############################################################################
.PHONY: freertos_lib_pre_compilation
freertos_lib_pre_compilation:
	@echo FREERTOS_LIB_VERSION = $(FREERTOS_LIB_VERSION)
	@echo FREERTOS_LIB_BUILD_INFO = $(FREERTOS_LIB_BUILD_INFO)
	@echo FREERTOS_LIB_VERSION_TAG = $(FREERTOS_LIB_VERSION_TAG)
	@echo FREERTOS_LIB_PATH = $(FREERTOS_LIB_PATH)
	@echo FREERTOS_LIB_ASM_SRC = $(FREERTOS_LIB_ASM_SRC)
	@echo FREERTOS_LIB_INCLUDES = $(FREERTOS_LIB_INCLUDES)
