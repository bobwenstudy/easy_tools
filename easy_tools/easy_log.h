#ifndef _EASY_LOG_H_
#define _EASY_LOG_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "easy_tools_common.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

#define EASY_LOG_IMPL_LEVEL_NONE 0U
#define EASY_LOG_IMPL_LEVEL_ERR  1U
#define EASY_LOG_IMPL_LEVEL_WRN  2U
#define EASY_LOG_IMPL_LEVEL_INF  3U
#define EASY_LOG_IMPL_LEVEL_DBG  4U

#define EASY_LOG_LEVEL EASY_CONFIG_DEBUG_LOG_LEVEL
// #define EASY_LOG_LEVEL EASY_LOG_IMPL_LEVEL_DBG

__EASY_STATIC_INLINE__ char easy_log_level_to_char(int level)
{
    switch (level)
    {
    case EASY_LOG_IMPL_LEVEL_ERR:
        return 'E';
    case EASY_LOG_IMPL_LEVEL_WRN:
        return 'W';
    case EASY_LOG_IMPL_LEVEL_INF:
        return 'I';
    case EASY_LOG_IMPL_LEVEL_DBG:
        return 'D';
    default:
        return '?';
    }
}

#if EASY_CONFIG_DEBUG_LOG_WITH_NEWLINE
#define __EASY_LOG_IMPL_RAW(fmt, ...)  easy_tools_api_log(fmt "\n", ##__VA_ARGS__);
#else
#define __EASY_LOG_IMPL_RAW(fmt, ...)  easy_tools_api_log(fmt, ##__VA_ARGS__);
#endif

#define __EASY_LOG_IMPL_TO_PRINT(_fun, _line, _level, fmt, ...)                                                                                                \
    do                                                                                                                                                         \
    {                                                                                                                                                          \
        __EASY_LOG_IMPL_RAW("%c: "                                                                                                                              \
                           "%s():%d: " fmt,                                                                                                                    \
                           easy_log_level_to_char(_level), _fun, _line, ##__VA_ARGS__);                                                                        \
    } while (false);

#if EASY_CONFIG_DEBUG_LOG_SIMPLE
#define __EASY_LOG_IMPL(_level, fmt, ...) __EASY_LOG_IMPL_RAW(fmt, ##__VA_ARGS__)
#else
#define __EASY_LOG_IMPL(_level, ...) __EASY_LOG_IMPL_TO_PRINT(__func__, __LINE__, _level, __VA_ARGS__)
#endif

#define EASY_LOG_IMPL_ERR(...) __EASY_LOG_IMPL(EASY_LOG_IMPL_LEVEL_ERR, __VA_ARGS__)
#define EASY_LOG_IMPL_WRN(...) __EASY_LOG_IMPL(EASY_LOG_IMPL_LEVEL_WRN, __VA_ARGS__)
#define EASY_LOG_IMPL_INF(...) __EASY_LOG_IMPL(EASY_LOG_IMPL_LEVEL_INF, __VA_ARGS__)
#define EASY_LOG_IMPL_DBG(...) __EASY_LOG_IMPL(EASY_LOG_IMPL_LEVEL_DBG, __VA_ARGS__)

#if EASY_LOG_LEVEL >= EASY_LOG_IMPL_LEVEL_ERR
#define EASY_LOG_ERR(fmt, ...) EASY_LOG_IMPL_ERR(fmt, ##__VA_ARGS__)
#else
#define EASY_LOG_ERR(fmt, ...)
#endif
#if EASY_LOG_LEVEL >= EASY_LOG_IMPL_LEVEL_WRN
#define EASY_LOG_WRN(fmt, ...) EASY_LOG_IMPL_WRN(fmt, ##__VA_ARGS__)
#else
#define EASY_LOG_WRN(fmt, ...)
#endif
#if EASY_LOG_LEVEL >= EASY_LOG_IMPL_LEVEL_INF
#define EASY_LOG_INF(fmt, ...) EASY_LOG_IMPL_INF(fmt, ##__VA_ARGS__)
#else
#define EASY_LOG_INF(fmt, ...)
#endif
#if EASY_LOG_LEVEL >= EASY_LOG_IMPL_LEVEL_DBG
#define EASY_LOG_DBG(fmt, ...) EASY_LOG_IMPL_DBG(fmt, ##__VA_ARGS__)
#else
#define EASY_LOG_DBG(fmt, ...)
#endif

#define EASY_LOG_ASSERT(condition)                                                                                                                             \
    do                                                                                                                                                         \
    {                                                                                                                                                          \
        if (!(condition))                                                                                                                                      \
            easy_tools_log_api_assert(__FILE__, __LINE__);                                                                                                     \
    } while (0)

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _EASY_LOG_H_ */
