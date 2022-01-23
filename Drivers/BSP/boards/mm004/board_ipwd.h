/*! @file board_ipwd.h
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Michal \n
 * 
 * $Revision:$ 
 * $LastChangedBy:$
 * $Date:$   \n
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DRIVERS_BSP_BOARDS_IPWDT_BOARD_IPWD_H_
#define DRIVERS_BSP_BOARDS_IPWDT_BOARD_IPWD_H_
/* Includes ------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_conf.h"

/* Exported types ------------------------------------------------------------*/
/**
 * @ingroup BOARD_GPIO_CONFIG
 * @defgroup BOARD_ui extension connector
 * @brief xxx
 * @{
 */

typedef enum
{
	LED_RED,
	LED_GREEN,
} enLED;

/* Exported constants --------------------------------------------------------*/

#define board_EEPROM_SCL_PIN			LL_GPIO_PIN_6
#define board_EEPROM_SCL_PORT			GPIOB

#define board_EEPROM_SDA_PIN			LL_GPIO_PIN_7
#define board_EEPROM_SDA_PORT			GPIOB

#define board_LED_G_PIN					LL_GPIO_PIN_10		//!< Pin
#define board_LED_G_PORT				GPIOA				//!< Port

#define board_LED_R_PIN					LL_GPIO_PIN_11		//!< Pin
#define board_LED_R_PORT				GPIOA				//!< Port

#define board_LED_DBG_PIN				LL_GPIO_PIN_9		//!< Pin
#define board_LED_DBG_PORT				GPIOB				//!< Port

#define board_BTN_PIN					LL_GPIO_PIN_0
#define board_BTN_PORT					GPIOA

#define board_INPUT_1_PIN				LL_GPIO_PIN_10
#define board_INPUT_1_PORT				GPIOB

#define board_INPUT_2_PIN				LL_GPIO_PIN_11
#define board_INPUT_2_PORT				GPIOB
//
//
#define board_INPUT_COMP1_PIN			LL_GPIO_PIN_1		//!< Elektromer
#define board_INPUT_COMP1_PORT			GPIOA

#define board_INPUT_COMP2_PIN			LL_GPIO_PIN_3		//!< Pwr fault
#define board_INPUT_COMP2_PORT			GPIOA
#define board_INPUT_COMP2_CHANNEL		LL_ADC_CHANNEL_3
//
//
#define board_ADC_A2_PIN				LL_GPIO_PIN_2
#define board_ADC_A2_PORT				GPIOA
#define board_ADC_A2_CHANNEL			LL_ADC_CHANNEL_2

#define board_ADC_A4_PIN				LL_GPIO_PIN_4
#define board_ADC_A4_PORT				GPIOA
#define board_ADC_A4_CHANNEL			LL_ADC_CHANNEL_4
//
//
#define board_RELE1_PIN					LL_GPIO_PIN_9
#define board_RELE1_PORT				GPIOA

#define board_RELE2_PIN					LL_GPIO_PIN_6
#define board_RELE2_PORT				GPIOA

/* Exported macro ------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

int32_t board_inputs_Init(void);
int32_t board_outputs_Init(void);

int32_t board_LED_Init(void);
int32_t board_BTN_Init(void);

void board_gpio(void);
int32_t board_ADC_Init(void);

// ADC
int32_t adc_GetPowerSupply(void);



#endif /* DRIVERS_BSP_BOARDS_IPWDT_BOARD_IPWD_H_ */
/* *****END OF FILE****/
