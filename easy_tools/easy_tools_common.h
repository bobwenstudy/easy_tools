#ifndef _EASY_COMMON_H_
#define _EASY_COMMON_H_

#include <stdint.h>
#include <stdio.h>

#include "easy_tools_config.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Apparently this is needed by several Windows compilers */
// #if !defined(__MACH__)
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif /* NULL */
// #endif /* ! Mac OS X - breaks precompiled headers */

/**
 * \brief           Get maximal value between 2 values
 * \param[in]       x: First value
 * \param[in]       y: Second value
 * \retval          Maximal value
 * \hideinitializer
 */
#define EASY_MAX(x, y) ((x) > (y) ? (x) : (y))

/**
 * \brief           Get minimal value between 2 values
 * \param[in]       x: First value
 * \param[in]       y: Second value
 * \retval          Minimal value
 * \hideinitializer
 */
#define EASY_MIN(x, y) ((x) < (y) ? (x) : (y))

/**
 * \brief           Get absolute value of input
 * \param[in]       x: Input value
 * \retval          Absolute value of input
 * \hideinitializer
 */
#define EASY_ABS(x) ((x) >= 0 ? (x) : -(x))

/**
 * \brief           Limit input value between min and max values
 * \param[in]       x: Input value
 * \param[in]       min: Minimum value
 * \param[in]       max: Maximum value
 * \retval          Limited value
 */
#define EASY_LIMIT_MIN_MAX(_x, _min, _max) EASY_MAX(EASY_MIN((_x), (_max)), (_min))

/**
 * \brief           Limit input value between 2 values
 * \param[in]       x: Input value
 * \param[in]       value0: First value
 * \param[in]       value1: Second value
 * \retval          Limited value
 */
#define EASY_LIMIT_CHECK_MIN_MAX(_x, _value0, _value1) EASY_LIMIT_MIN_MAX(_x, EASY_MIN(_value0, _value1), EASY_MAX(_value0, _value1))

#define EASY_SWAP(a, b) (a = (a) + (b), b = (a) - (b), a = (a) - (b))

#define EASY_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define EASY_UNUSED(_x) (void)(_x)

#define __EASY_WEAK__ __attribute__((weak))

#define __EASY_STATIC_INLINE__ static inline

#define EASY_MATH_PI 3.14159265358979323846f // pi

#define EASY_MATH_COS(_phase) cos(_phase)
#define EASY_MATH_SIN(_phase) sin(_phase)

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _EASY_COMMON_H_ */
