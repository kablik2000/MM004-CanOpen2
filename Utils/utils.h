/*! @file utils.h
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Michal \n
 * 
 * $Revision: 246 $ 
 * $Date: 2018-05-30 14:26:58 +0200 (Wed, 30 May 2018) $   \n
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "compiler.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */



double strtodbl(char* str);
char * ftoa(double f, char * buf, int precision);
long int atolIgnoreDp(register char *);


#endif /* UTILS_UTILS_H_ */
/*************** (C) COPYRIGHT 2016 *****END OF FILE****/
