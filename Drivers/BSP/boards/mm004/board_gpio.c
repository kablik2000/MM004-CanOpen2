/*! @file board_gpio.c
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Michal \n
 * 
 * $Revision: 497 $ 
 * $Date: 2018-07-07 18:55:49 +0200 (Sat, 07 Jul 2018) $   \n
 */

/* Includes ------------------------------------------------------------------*/
#include "board_ipwd.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/* Private function ----------------------------------------------------------*/

/**
 *
 * @return
 */
int32_t board_LED_Init(void)
{
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

	// GPIO LED Init
	LL_GPIO_InitTypeDef xGPIO_InitStruct;
	xGPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	xGPIO_InitStruct.Speed = LL_GPIO_SPEED_LOW;
	xGPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	xGPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

	xGPIO_InitStruct.Pin = board_LED_G_PIN;
	LL_GPIO_Init(board_LED_G_PORT, &xGPIO_InitStruct);
	xGPIO_InitStruct.Pin = board_LED_R_PIN;
	LL_GPIO_Init(board_LED_R_PORT, &xGPIO_InitStruct);
	xGPIO_InitStruct.Pin = board_LED_DBG_PIN;
	LL_GPIO_Init(board_LED_DBG_PORT, &xGPIO_InitStruct);

	return 0;
}

/**
 *
 * @return
 */
int32_t board_BTN_Init(void)
{
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

	// GPIO LED Init
	LL_GPIO_InitTypeDef xGPIO_InitStruct;
	xGPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	xGPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

	xGPIO_InitStruct.Pin = board_BTN_PIN;
	LL_GPIO_Init(board_BTN_PORT, &xGPIO_InitStruct);

	LL_EXTI_InitTypeDef xEXTI_InitStruct;
	xEXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0;
	xEXTI_InitStruct.LineCommand = ENABLE;
	xEXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	xEXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
	LL_EXTI_Init(&xEXTI_InitStruct);

	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE0);

	NVIC_SetPriority(EXTI0_1_IRQn, 5);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	return 0;
}



/**
 *
 * @return
 */
int32_t board_inputs_Init(void)
{
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

	// GPIO LED Init
	LL_GPIO_InitTypeDef xGPIO_InitStruct;
	xGPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	xGPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

	xGPIO_InitStruct.Pin = board_INPUT_1_PIN;
	LL_GPIO_Init( board_INPUT_1_PORT, &xGPIO_InitStruct);

	xGPIO_InitStruct.Pin = board_INPUT_2_PIN;
	LL_GPIO_Init( board_INPUT_2_PORT, &xGPIO_InitStruct);

	xGPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	xGPIO_InitStruct.Pin = board_INPUT_COMP1_PIN;
	LL_GPIO_Init( board_INPUT_COMP1_PORT, &xGPIO_InitStruct);

	// Power supply voltage measurement
	xGPIO_InitStruct.Pin = board_INPUT_COMP2_PIN;
	LL_GPIO_Init( board_INPUT_COMP2_PORT, &xGPIO_InitStruct);

	return 0;
}

/**
 *
 * @return
 */
int32_t board_outputs_Init(void)
{

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

	// GPIO LED Init
	LL_GPIO_InitTypeDef xGPIO_InitStruct;
	xGPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	xGPIO_InitStruct.Speed = LL_GPIO_SPEED_LOW;
	xGPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	xGPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

	xGPIO_InitStruct.Pin = board_RELE1_PIN;
	LL_GPIO_Init(board_RELE1_PORT, &xGPIO_InitStruct);
	xGPIO_InitStruct.Pin = board_RELE2_PIN;
	LL_GPIO_Init(board_RELE2_PORT, &xGPIO_InitStruct);

	return 0;
}

/**
 *
 * @param i
 * @param state
 */
void board_Output_SetState(uint8_t i, uint8_t state)
{
	GPIO_TypeDef *pxGPIO;
	uint32_t ulPin;
	if (i)
	{
		pxGPIO = board_RELE1_PORT;
		ulPin = board_RELE1_PIN;
	}
	else
	{
		pxGPIO = board_RELE2_PORT;
		ulPin = board_RELE2_PIN;
	}

	switch (state)
	{
		case 1:
			LL_GPIO_SetOutputPin(pxGPIO, ulPin);
			break;
		case 2:
			LL_GPIO_TogglePin(pxGPIO, ulPin);
			break;
		case 0:		//NOBREAK
		default:
			LL_GPIO_ResetOutputPin(pxGPIO, ulPin);
	}
}



/*************** (C) COPYRIGHT 2016 *****END OF FILE****/
