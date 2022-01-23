/*! @file delay.h
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DRIVERS_COMMON_DELAY_H_
#define DRIVERS_COMMON_DELAY_H_
/* Includes ------------------------------------------------------------------*/

#ifdef FREERTOS_USED
# include "FreeRTOS.h"
# include "task.h"
#else
# error "Nadefinovat cycle counter"
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void delay_init(unsigned long fcpu_hz);
void delay_ms(unsigned long delay);
void delay_us(uint32_t dwTime);

#endif /* DRIVERS_COMMON_DELAY_H_ */
/*************** (C) COPYRIGHT 2015 *****END OF FILE****/
