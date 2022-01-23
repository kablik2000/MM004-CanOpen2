/*! @file dbg_fnc.h
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Ing. Michal Zahalka \n
 * 
 * $Revision: 240 $ 
 * $Date: 2018-05-30 14:22:16 +0200 (Wed, 30 May 2018) $   \n
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DRIVERS_SYSTEM_DBG_FNC_H_
#define DRIVERS_SYSTEM_DBG_FNC_H_
/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
void prvGetRegistersFromStack(uint32_t *pulFaultStackAddress);


#endif /* DRIVERS_SYSTEM_DBG_FNC_H_ */
/*************** (C) COPYRIGHT 2015 *****END OF FILE****/
