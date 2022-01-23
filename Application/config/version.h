/*! @file version.h
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Michal \n
 * 
 * $Revision: 1113 $ 
 * $Date: 2019-02-18 20:19:41 +0100 (Mon, 18 Feb 2019) $   \n
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APPLICATION_CONFIG_VERSION_H_
#define APPLICATION_CONFIG_VERSION_H_
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* APP definition file - processed by BuildNumber.exe  */

#undef APP_ID_NUMBER
#define APP_ID_NUMBER         			SW100613
#undef APP_SHORT_NAME
#define APP_SHORT_NAME        			VpIpWd20
#undef APP_LONG_NAME
#define APP_LONG_NAME         			VpIpWd20

#undef APP_VER_MAJOR
#define APP_VER_MAJOR         			1
#undef APP_VER_MINOR
#define APP_VER_MINOR         			30

#undef APP_BUILD_DATE
#define APP_BUILD_DATE        			202012282246
#undef APP_BUILD_NUMBER
#define APP_BUILD_NUMBER      			1043
/* End APP definition file */


#ifndef PRODUCT_COMPANY
#  define PRODUCT_COMPANY 			Vupee
#endif

#ifndef PRJ_SYSNAME
#  define PRJ_SYSNAME			FreeRTOS
#endif


#define PRJ_LICENCE					"\nCopyright (C) 2017 Teiimo GmbH"\
									"\nCopyright (C) 2017 VUPEE,s.r.o."

#define PRJ_KERNEL_LICENCE			"This product uses the FreeRTOS.org real time kernel V9.0.0"\
									"\nCopyright (C) 2016 Real Time Engineers Ltd."

#define PRJ_KERNEL_LICENCE_LINK		"The FreeRTOS sourcecode is licensed by GNU General Public License"\
									"\nSource code can be obtained by visiting www.FreeRTOS.org\n"

/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

#endif /* APPLICATION_CONFIG_VERSION_H_ */
/*************** (C) COPYRIGHT 2016 *****END OF FILE****/
