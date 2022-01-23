/*! @file cpu_utils.c
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Ing. Michal Zahalka \n
 * 
 * $Revision: 779 $ 
 * $Date: 2018-09-26 10:33:39 +0200 (Wed, 26 Sep 2018) $   \n
 */

/********************** IMPORTANT **********************************************
 To use this module, the following steps should be followed :

 1- in the FreeRTOSConfig.h file enable the following macros :
 - #define configUSE_IDLE_HOOK	        1
 - #define configUSE_TICK_HOOK	        1

 2- in the FreeRTOSConfig.h define the following macros :
 - #define traceTASK_SWITCHED_IN()  extern void StartIdleMonitor(void); \
                                         StartIdleMonitor()
 - #define traceTASK_SWITCHED_OUT() extern void EndIdleMonitor(void); \
                                         EndIdleMonitor()
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "global_includes.h"
/* Private typedef -----------------------------------------------------------*/
#define CALCULATION_PERIOD 1000 //XXX
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

xTaskHandle xIdleHandle = NULL;
volatile uint32_t FreeRTOS_CPU_Usage = 0;
uint32_t FreeRTOS_CPU_IdleStartTime = 0;
uint32_t FreeRTOS_CPU_IdleSpentTime = 0;
uint32_t FreeRTOS_CPU_TotalIdleTime = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**
 * @brief  Application Idle Hook
 * This function is called on each cycle of the idle task.  It is essential that
 * code added to this hook function never attempts to block in any way
 * @note The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
 *        FreeRTOSConfig.h.
 * @param  None
 * @retval None
 */

void vApplicationIdleHook(void)
{
	if (xIdleHandle == NULL)
	{
		/* Store the handle to the idle task. */
		xIdleHandle = xTaskGetCurrentTaskHandle();
	}
}

/**
 * @brief  Application Idle Hook
 * This function is called from an interrupt context (the RTOS tick
 *  interrupt),	so only ISR safe API functions can be used (those that end
 *  in "FromISR()"
 * @note The RTOS tick hook function is enabled by setting configUSE_TICK_HOOK to
 *        1 in FreeRTOSConfig.h.
 * @param  None
 * @retval None
 */
void vApplicationTickHook(void)
{
	static int tick = 0;

	if (tick++ > CALCULATION_PERIOD)
	{
		tick = 0;

		if (FreeRTOS_CPU_TotalIdleTime > 1000)
		{
			FreeRTOS_CPU_TotalIdleTime = 1000;

		}
		FreeRTOS_CPU_Usage = (100 - (FreeRTOS_CPU_TotalIdleTime * 100) / CALCULATION_PERIOD);
		FreeRTOS_CPU_TotalIdleTime = 0;
	}
}


/**
 * @brief  Start Idle monitor
 */
void StartIdleMonitor(void)
{
	if (xTaskGetCurrentTaskHandle() == xIdleHandle)
	{
		FreeRTOS_CPU_IdleStartTime = xTaskGetTickCount();
	}
}

/**
 * @brief  Stop Idle monitor
 */
void EndIdleMonitor(void)
{
	if (xTaskGetCurrentTaskHandle() == xIdleHandle)
	{
		/* Store the handle to the idle task. */
		FreeRTOS_CPU_IdleSpentTime = xTaskGetTickCount() - FreeRTOS_CPU_IdleStartTime;
		FreeRTOS_CPU_TotalIdleTime += FreeRTOS_CPU_IdleSpentTime;
	}
}

/**
 * @brief  Stop Idle monitor
 */
uint16_t FreeRTOS_GetCPUUsage(void)
{
	return (uint16_t) FreeRTOS_CPU_Usage;
}

/**
 * @brief
 * @param pxTask
 * @param pcTaskName
 */
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName)
{
//	(void) pcTaskName;
	(void) pxTask;

	/* Run time stack overflow checking is performed if
	 configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	 function is called if a stack overflow is detected.  pxCurrentTCB can be
	 inspected in the debugger if the task name passed into this function is
	 corrupt. */
	taskDISABLE_INTERRUPTS();
//	syslog_Add(SyslogCategory_FreeRTOS, SyslogType_Error, "%s stack Overflow", pcTaskName);
	// TODO použít BackUp memory pro uložení stavu a zpracování po startu...
//	system_Reset(0);
	__asm__("BKPT 0");
	for (;;)
		;
}

/**
 * @brief
 */
void vApplicationMallocFailedHook(void)
{
	/* The malloc failed hook is enabled by setting
	 configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

	 Called if a call to pvPortMalloc() fails because there is insufficient
	 free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	 internally by FreeRTOS API functions that create tasks, queues, software
	 timers, and semaphores.  The size of the FreeRTOS heap is set by the
	 configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	taskDISABLE_INTERRUPTS();
//	syslog_Add(SyslogCategory_FreeRTOS, SyslogType_Error, "Application Malloc Failed");
//	system_Reset(5000);
	for (;;)
		;
}


/*************** (C) COPYRIGHT 2015 *****END OF FILE****/
