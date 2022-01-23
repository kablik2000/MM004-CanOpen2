/**
 * @verbatim FreeRTOS Overvie
 * RAM:
 *   Scheduler	236 bytes (can easily be reduced by using smaller data types).
 *   Queue		76 bytes + queue storage area
 *   Task		64 bytes (includes 4 characters for the task name) + the task stack size.
 *
 * ROM:
 *   The RTOS kernel itself required about 5 to 10 KBytes of ROM space
 *
 * Starting time:
 *   Configure the CPU clocks for the performance level required.
 *    - Typically requires a few register writes, followed by a short delay for clocks
 *      to lock. This will take in the order of a few microseconds
 *
 *   Initialize static and global variables that contain only the value zero (bss).
 *    - Typically hundred write accesses to be performed within a very tight assembly loop.
 *      This will add in the region of a few microseconds
 *
 *   Initialize variables that contain a value other than zero.
 *    - Including FreeRTOS in an application would typically not add any extra time to this step
 *
 *   Perform any other hardware set up required.
 *    - Typically require a few milliseconds only
 *
 *   Create application queues, semaphores and mutexes.
 *    - Typically the majority of queues, semaphores and mutexes will be created prior to the RTOS scheduler being started
 *    - cca 500 CPU cycles
 *
 *   Create application tasks
 *    - cca 1100 CPU cycles
 *
 *   Start the RTOS scheduler
 *    - cca 1200 CPU cycles
 *
 * @endverbatim
 *
 *
 * @verbatim Memory management
 *   @link http://www.freertos.org/a00111.html
 *   heap_1 - the very simplest, does not permit memory to be freed
 *   heap_2 - permits memory to be freed, but not does coalescence adjacent free blocks.
 *   heap_3 - simply wraps the standard malloc() and free() for thread safety
 *   heap_4 - coalescences adjacent free blocks to avoid fragmentation. Includes absolute address placement option
 *   heap_5 - as per heap_4, with the ability to span the heap across multiple non-adjacent memory areas
 *
 * @endverbatim
 *
 * $Revision: 1113 $
 * $Date: 2019-02-18 20:19:41 +0100 (Mon, 18 Feb 2019) $   \n

 */

/* Includes ------------------------------------------------------------------*/

// Standard includes
#include <stdint.h>


#include "errno.h"
#include "main.h"
#include "stm32f0xx_conf.h"
#include "boards/board.h"

#include "utils.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

static TaskHandle_t Task_Handle;
/* Private function prototypes -----------------------------------------------*/

/* TODO: Implement this function for any hardware specific clock configuration
 * that was not already performed before main() was called.
 */
static void prvSetupHardware(void);
void SystemClock_Config(void);

extern void main_backgroundTask(void * pvParameters);
extern void hw_Init(void);
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
#if 0
	PWR_PVDLevelConfig(PWR_PVDLevel_3);   // PVD level 2,5V
	PWR_PVDCmd(ENABLE);

#if (configDEBUG == 1)
	DBGMCU_APB1PeriphConfig(DBGMCU_IWDG_STOP, ENABLE);   // Zastaví WatchDog, když je stoplé jádro - TODO podmíněný překlad Debug!
	DBGMCU_APB1PeriphConfig(DBGMCU_TIM7_STOP, ENABLE);
#endif /*configDEBUG*/

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	/*		IWDG counter clock Frequency = LsiFreq/32
	 Counter Reload Value = time[ms] /IWDG counter clock period
	 = 0.25s / (256/LsiFreq)
	 = LsiFreq/(32 * 4)
	 = LsiFreq/128
	 */
	IWDG_SetPrescaler(IWDG_Prescaler_256);   // RL == 0xFFF - 32,768s
	IWDG_SetReload(0xFFF);
	IWDG_ReloadCounter();
#if (!(configDISABLE_AUTORESTART == 1)&&(configDEBUG == 1))
//	IWDG_Enable();
#endif /*configDISABLE_AUTORESTART*/
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
#endif
	/* Configure the system ready to run the demo.  The clock configuration
	 can be done here if it was not done before main() was called. */
	prvSetupHardware();

	/* Create Task -----------------------------------------------------------*/

	/* Create background task */
	xTaskCreate(main_backgroundTask,
			(const char * const) "Background",
			256,
			NULL,
			1,
			&Task_Handle);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();
	/* If all is well, the scheduler will now be running, and the following line
	 will never be reached.  If the following line does execute, then there was
	 insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	 to be created.  See the memory management section on the FreeRTOS web site
	 for more details.  http://www.freertos.org/a00111.html */

	/* Infinite loop */
	while (1)
	{

	}
}

/**
 * @brief Nastavení LowLevel vrstvy HW
 */
static void prvSetupHardware(void)
{
	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	/* Vector table defined in system_stm32xxx.c file */
//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0xC000);
	/* Ensure all priority bits are assigned as preemption priority bits.
	 http://www.freertos.org/RTOS-Cortex-M3-M4.html */

//	NVIC_SetPriorityGrouping(3);	//NVIC_PRIORITYGROUP_4 - Nastavit jednou a už s tim nevrklat!!!!!
#if (defined configDEBUG )&& (configDEBUG >= 1)

	//	__HAL_DBGMCU_FREEZE_IWDG();		// Freeze WatchDog
//	__HAL_DBGMCU_FREEZE_TIM7();		// Freeze TIM7 - FreeRtos Task Runtime counter

//	DBGMCU_APB1PeriphConfig(DBGMCU_TIM9_STOP, ENABLE);   //Beeper
#endif /*configDEBUG*/

	SystemClock_Config();

}
//---------------------------------------------------------------

/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSI48)
 *            SYSCLK(Hz)                     = 48000000
 *            HCLK(Hz)                       = 48000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            HSI Frequency(Hz)              = 48000000
 *            PREDIV                         = 2
 *            PLLMUL                         = 2
 *            Flash Latency(WS)              = 1
 * @param  None
 * @retval None
 */
void SystemClock_Config(void)
{
	/* Set FLASH latency */
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

	/* Enable HSI48 and wait for activation*/
	LL_RCC_HSI48_Enable();
	while (LL_RCC_HSI48_IsReady() != 1)
	{
	};

	/* Main PLL configuration and activation */
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI48, LL_RCC_PLL_MUL_2, LL_RCC_PREDIV_DIV_2);

	LL_RCC_PLL_Enable();
	while (LL_RCC_PLL_IsReady() != 1)
	{
	};

	/* Sysclk activation on the main PLL */
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	};

	/* Set APB1 prescaler */
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

	/* Set systick to 1ms in using frequency set to 48MHz */
	/* This frequency can be calculated through LL RCC macro */
	/* ex: __LL_RCC_CALC_PLLCLK_FREQ (HSI48_VALUE, LL_RCC_PLL_MUL_2, LL_RCC_PREDIV_DIV_2) */
	LL_Init1msTick(48000000);

	/* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
	LL_SetSystemCoreClock(48000000);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
