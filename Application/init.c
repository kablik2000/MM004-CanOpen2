/*! @file init.c
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Michal Zahalka \n
 *
 * $Revision: 1113 $
 * $Date: 2019-02-18 20:19:41 +0100 (Mon, 18 Feb 2019) $   \n
 */

/* Includes ------------------------------------------------------------------*/

// Standard includes
#include <stdint.h>


#include "main.h"
#include "stm32f0xx_conf.h"
#include "boards/board.h"

#include "utils.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private function ----------------------------------------------------------*/

/**
 * @brief  Background task
 * @param  pvParameters not used
 * @retval None
 */
void main_backgroundTask(void * pvParameters)
{
	board_LED_Init();
	board_BTN_Init();

//	board_ADC_Init();
//	watchdog_Init();

	// Main program loop
	while (1)
	{
		vTaskDelay(500 / portTICK_PERIOD_MS);

		LL_GPIO_TogglePin(board_LED_DBG_PORT, board_LED_DBG_PIN);
	}
}



/* *****END OF FILE****/

