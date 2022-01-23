/*! @file compiler.h
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Ing. Michal Zahálka \n
 * 
 * $Revision: 1.0$ 
 * $Date: 30. 10. 2015$   \n
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UTILS_COMPILER_H_
#define UTILS_COMPILER_H_
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <sys/cdefs.h>		// Helper macros for K&R vs. ANSI C compat.
//#include "utils_debug.h"
//#include "symbols.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
//#define LITTLE_ENDIAN		1234
//#define BIG_ENDIAN			4321
//#define PDP_ENDIAN			3412
//#if GCC_VERSION >= 40000
//#endif
/*
 #define __asm__             asm
 */

/**
 * @brief arm-none-eabi-size
 * @note
 * Type		Size in bits	Natural alignment
 * char				8		1 (byte aligned)
 * short			16		2 (halfword aligned)
 * int				32		4 (word aligned)
 * long				32		4 (word aligned)
 * long long		64		4 (word aligned)
 * float			32		4 (word aligned)
 * double			64		4 (word aligned)
 * long double		64		4 (word aligned)
 * all pointers		32		4 (word aligned)
 * bool*			32		4 (word aligned)	* Applies to C++ only.
 *
 *
 * The following remarks apply to all pointer types in C, and to all pointer types except pointers to members in C++:
 *     Adjacent bytes have addresses that differ by one.
 *     The macro NULL expands to the value 0.
 *     Casting between integers and pointers results in no change of representation.
 *     The compiler warns of casts between pointers to functions and pointers to data, except when PCC mode is specified.
 *     The type size_t is defined as unsigned int, except in PCC mode where it is signed.
 *     The type ptrdiff_t is defined as signed int.
 */

/* Exported macro ------------------------------------------------------------*/


#ifndef CHARTOINT
#  define CHARTOINT(ch)				(ch - '0')
#endif	/* !defined(CHARTOINT) */

#ifndef ISDIGIT
#  define ISDIGIT(ch)				('0' <= (unsigned char)ch && (unsigned char)ch <= '9')
#endif	/* !defined(ISDIGIT) */

#ifndef ISNAN
#  define ISNAN(x)					(x != x)
#endif	/* !defined(ISNAN) */

#ifndef ISINF
#  define ISINF(x)					(x != 0.0 && x + x == x)
#endif	/* !defined(ISINF) */

/**
 * @brief Create string from s
 * __XSTRING
 */
#ifndef __STR
#  define ___STR(s)					#s
#  define __STR(s)					___STR(s)
#endif /*__STR*/

/**
 * Indirect macros required for expanded argument pasting, eg. __LINE__.
 * __CONCAT
 */
#ifndef __PASTE
#  define ___PASTE(a,b)				a##b
#  define __PASTE(a,b)				___PASTE(a,b)
#endif /*__PASTE*/

/*! @name Mathematics
 *
 * The same considerations as for clz and ctz apply here but AVR32-GCC does not
 * provide built-in functions to access the assembly instructions abs, min and
 * max and it does not produce them by itself in most cases, so two sets of
 * macros are defined here:
 *   - Abs, Min and Max to apply to constant expressions (values known at
 *     compile time);
 *   - abs, min and max to apply to non-constant expressions (values unknown at
 *     compile time).
 */
//! @{
#define _CHOOSE2(binoper, lexpr, lvar, rexpr, rvar) \
		({ \
				typeof(lexpr) lvar = (lexpr); \
				typeof(rexpr) rvar = (rexpr); \
				lvar binoper rvar ? lvar : rvar; \
		})
#define _CHOOSE(binoper, lexpr, rexpr) \
		_CHOOSE2( \
				binoper, \
				lexpr, __PASTE(_left, __COUNTER__), \
				rexpr, __PASTE(_right, __COUNTER__) \
				)

/*! @brief Takes the absolute value of \a a.
 *
 * @param a Input value.
 *
 * @return Absolute value of \a a.
 *
 * @note More optimized if only used with values known at compile time.
 */
#define Abs(a)					(((a) <  0 ) ? -(a) : (a))

#ifndef Min
/*! @brief Takes the minimal value of \a a and \a b.
 *
 * @param a Input value.
 * @param b Input value.
 *
 * @return Minimal value of \a a and \a b.
 *
 * @note More optimized if only used with values known at compile time.
 */
#  define Min(a, b)					_CHOOSE(<, a, b)
//#  define Min(a, b)				(((a) < (b)) ?  (a) : (b))
#endif /*Min*/

#ifndef Max
/*! @brief Takes the maximal value of \a a and \a b.
 *
 * @param a Input value.
 * @param b Input value.
 *
 * @return Maximal value of \a a and \a b.
 *
 * @note More optimized if only used with values known at compile time.
 */

#  define Max(a, b)					_CHOOSE(>, a, b)
//#  define Max(a, b)				(((a) > (b)) ?  (a) : (b))
#endif /*Max*/
//TODO Rewrite to Thumb2 instr. set!

#ifndef Pow2
/*!
 * \brief Returns 2 raised to the power of n
 *
 * \param [IN] n power value
 * \retval result of raising 2 to the power n
 */
//#  define Pow2( n )				( 1 << n )
#endif /*Pow2*/

//!@}

/*! @name Endianism Conversion
 *
 * The same considerations as for clz and ctz apply here but AVR32-GCC's
 * __builtin_bswap_16 and __builtin_bswap_32 do not behave like macros when
 * applied to constant expressions, so two sets of macros are defined here:
 *   - Swap16, Swap32 and Swap64 to apply to constant expressions (values known
 *     at compile time);
 *   - swap16, swap32 and swap64 to apply to non-constant expressions (values
 *     unknown at compile time).
 */
//! @{
/*! @brief Toggles the endianism of \a u16 (by swapping its bytes).
 *
 * @param u16 uint16_t of which to toggle the endianism.
 *
 * @return Value resulting from \a u16 with toggled endianism.
 *
 * @note More optimized if only used with values known at compile time.
 */
#define Swap16(u16) ((uint16_t)(((uint16_t)(u16) >> 8) |\
                           ((uint16_t)(u16) << 8)))

/*! @brief Toggles the endianism of \a u32 (by swapping its bytes).
 *
 * @param u32 uint32_t of which to toggle the endianism.
 *
 * @return Value resulting from \a u32 with toggled endianism.
 *
 * @note More optimized if only used with values known at compile time.
 */
#define Swap32(u32) ((uint32_t)(((uint32_t)Swap16((uint32_t)(u32) >> 16)) |\
                           ((uint32_t)Swap16((uint32_t)(u32)) << 16)))

/*! @brief Toggles the endianism of \a u64 (by swapping its bytes).
 *
 * @param u64 uint64_t of which to toggle the endianism.
 *
 * @return Value resulting from \a u64 with toggled endianism.
 *
 * @note More optimized if only used with values known at compile time.
 */
#define Swap64(u64) ((uint64_t)(((uint64_t)Swap32((uint64_t)(u64) >> 32)) |\
                           ((uint64_t)Swap32((uint64_t)(u64)) << 32)))

/**
 *  Not-quite-unique ID.
 */
#ifndef __UNIQUE_ID
# define __UNIQUE_ID(prefix)		//__PASTE(__BASE_FILE__,prefix)//__PASTE(__PASTE(__UNIQUE_ID_, prefix), __LINE__)
// __LINE__
// __FILE__
//__BASE_FILE__
// __func__
#endif

//! Count size of array
#ifndef ARRAY_SIZE
#  define ARRAY_SIZE(x)				(sizeof(x)/sizeof(x[0]))
//#  define ARRAY_SIZE(__BUFFER__)				(sizeof(__BUFFER__)/sizeof(*(__BUFFER__)))
#endif /*ARRAY_SIZE*/

#ifndef offsetof
/**
 *
 */
#  define offsetof(T, x) ((size_t) &((T *)0)->x)
#endif

#ifndef container_of
# ifdef __containerof
/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#  define container_of				__containerof
# else
#  error "__containerof not defined!"
# endif
//#define container_of(ptr, type, member) 							\
	({																\
		const __typeof__( ((type *)0)->member ) *__mptr = (ptr);	\
		(type *)( (char *)__mptr - offsetof(type,member) );			\
	})
//#define container_of(p, T, x)		((T *)((char *)(p) - offsetof(T,x)))
#endif /*container_of*/

/**
 * A trick to suppress uninitialized variable warning without generating any
 * code
 */
#define uninitialized_var(x) 		x = x

/*
 * Gets a struct member size
 */
#define member_size(type, member) sizeof(((type *)0)->member)

/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

#endif /* UTILS_COMPILER_H_ */
/*************** (C) COPYRIGHT 2015 *****END OF FILE****/
