/*! @file configTypes.h
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Michal Zahalka <michal.zahalka@vupee.cz> \n
 * 
 * $Revision: 941 $ 
 * $Date: 2018-11-09 14:01:24 +0100 (Fri, 09 Nov 2018) $   \n
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APPLICATION_CONFIG_CONFIGTYPES_H_
#define APPLICATION_CONFIG_CONFIGTYPES_H_
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "arm_math.h"

/* Exported types ------------------------------------------------------------*/
typedef uint8_t BOOL;	//fixme std BOOL!!
typedef _Bool bool_t;

// TODO standard type!!
//typedef long BaseType_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#ifndef NULL
#  define NULL ((void *)0)
#endif /*NULL*/



/* Byte order conversions */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define htobs(d)  (d)		//!< host to network short
#define htobl(d)  (d)		//!< host to network long
#define btohs(d)  (d)		//!< network to host short
#define btohl(d)  (d)		//!< network to host long
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define htobs(d)  (d<<8|d>>8)
#define htobl(d)  (d<<24|((d<<8)&0x00ff0000)|((d>>8)&0x0000ff00)|((d>>24)&0x000000ff))
#define btohs(d)  (d<<8|d>>8)
#define btohl(d)  (d<<24|((d<<8)&0x00ff0000)|((d>>8)&0x0000ff00)|((d>>24)&0x000000ff))
#else
#error "Unknown byte order"
#endif


#ifndef bTRUE
#  define bTRUE			(1)//( ( BaseType_t ) 1 )
#endif
#ifndef bFALSE
#  define bFALSE		(0)//( ( BaseType_t ) 0 )
#endif

/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

#endif /* APPLICATION_CONFIG_CONFIGTYPES_H_ */
/*************** (C) COPYRIGHT 2017 *****END OF FILE****/
