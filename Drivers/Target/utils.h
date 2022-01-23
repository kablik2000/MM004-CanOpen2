/*! @file utils.h
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Michal Zahalka <michal.zahalka@vupee.cz> \n
 * 
 * $Revision: 940 $ 
 * $LastChangedBy: michal.zahalka $
 * $Date: 2018-11-09 14:00:03 +0100 (Fri, 09 Nov 2018) $   \n
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DRIVERS_TARGET_UTILS_H_
#define DRIVERS_TARGET_UTILS_H_
/* Includes ------------------------------------------------------------------*/
#include "api-types.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#if (configDEBUG >= 1)
#define debugStop()			__asm("BKPT #0\n")	// Break into the debugger x is an expression evaluating to an integer in the range 0-255 (8-bit value).
#else
#define debugStop()
#endif /*configDEBUG*/


/**
 * @brief This macro is used to test fatal errors.
 *
 * The macro tests if the expression is false. If it is, a fatal error is
 * detected and the application hangs up. If TEST_SUITE_DEFINE_ASSERT_MACRO
 * is defined, a unit test version of the macro is used, to allow execution
 * of further tests after a false expression.
 *
 * @param expr  Expression to evaluate and supposed to be nonzero.
 */
#if defined(FREERTOS_USED)
#  define Assert(expr)		configASSERT(expr)
#elif defined(_ASSERT_ENABLE_) || defined(configASSERT)
#  if defined(TEST_SUITE_DEFINE_ASSERT_MACRO)
// Assert() is defined in unit_test/suite.h
#    include "unit_test/suite.h"
#  else
#    define Assert(expr)	\
	{						\
		if (!(expr))		\
			{				\
			debugStop();	\
			while (true);	\
			}				\
	}
#  endif
#else
#  define Assert(expr) 		((void) 0)
#endif


/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

#endif /* DRIVERS_TARGET_UTILS_H_ */
/* *****END OF FILE****/
