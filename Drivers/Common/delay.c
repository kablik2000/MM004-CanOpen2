/*! @file delay.c
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Ing. Michal Zahálka \n
 * 
 * $Revision: 1.0$ 
 * $Date: 26. 10. 2015$   \n
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

#include "delay.h"

#ifdef FREERTOS_USED
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//! CPU frequency
#ifndef FREERTOS_USED
static unsigned long s_fcpu_hz;
#endif
#if (defined NUTOS_USED)
extern void NutSleep(unsigned long ms);
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**
 * @brief Initialize the delay driver.
 * @param fcpu_hz: CPU frequency in Hz.
 */
void delay_init(unsigned long fcpu_hz)
{
#ifndef FREERTOS_USED
	s_fcpu_hz = fcpu_hz;
#endif
}

/**
 * @brief Waits during at least the specified delay (in millisecond) before returning.
 * @note that in the case of FreeRTOS, the function will delay the current task for a given number of ms.
 * @param delay:Number of millisecond to wait.
 */
void delay_ms(unsigned long delay)
{
#if (defined FREERTOS_USED)
//  vTaskDelay( (portTickType)TASK_DELAY_MS(delay) );
	vTaskDelay((portTickType) delay / portTICK_RATE_MS);  //FIXME
#elif (defined NUTOS_USED)
			NutSleep(delay);
#else
			cpu_delay_ms(delay, s_fcpu_hz);
#endif
}

/**
 * @brief  Utility function for delay
 * @param  None
 * @retval None
 * NOTE: TODO: implement with clock-independent function.
 */
void delay_us(uint32_t dwTime)
{
	// POZOR na operace před spuštěním FreeRTOSu
//	if((dwTime>1000)&&((dwTime%1000)==0))	// čekání celé milisekundy
//		delay_ms(dwTime/1000);
//	else
//	{
		dwTime *= 1100;		// Specific for FCPU 168 MHz
		while(dwTime--) __NOP();
//	}
}





/*************** (C) COPYRIGHT 2015 *****END OF FILE****/
