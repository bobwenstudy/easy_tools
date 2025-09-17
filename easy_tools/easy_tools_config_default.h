#ifndef _EASY_TOOLS_CONFIG_DEFAULT_H_
#define _EASY_TOOLS_CONFIG_DEFAULT_H_

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Fuction options.
 * For heap function enable.
 */
#ifndef EASY_CONFIG_FUNCTION_HEAP
#define EASY_CONFIG_FUNCTION_HEAP 1
#endif

/**
 * Fuction options.
 * For task function enable.
 */
#ifndef EASY_CONFIG_FUNCTION_TASK
#define EASY_CONFIG_FUNCTION_TASK 1
#endif

/**
 * Debug options.
 * For log level. EASY_LOG_IMPL_LEVEL_NONE, EASY_LOG_IMPL_LEVEL_ERR,
 * EASY_LOG_IMPL_LEVEL_WRN, EASY_LOG_IMPL_LEVEL_INF, EASY_LOG_IMPL_LEVEL_DBG
 */
#ifndef EASY_CONFIG_DEBUG_LOG_LEVEL
#define EASY_CONFIG_DEBUG_LOG_LEVEL EASY_LOG_IMPL_LEVEL_DBG
#endif

/**
 * Debug options.
 * For log info print.
 */
#ifndef EASY_CONFIG_DEBUG_LOG_SIMPLE
#define EASY_CONFIG_DEBUG_LOG_SIMPLE 1
#endif

/**
 * Debug options.
 * Auto add newline at the end of log info.
 */
#ifndef EASY_CONFIG_DEBUG_LOG_WITH_NEWLINE
#define EASY_CONFIG_DEBUG_LOG_WITH_NEWLINE 0
#endif

/**
 * If task function is enabled, heap function will be enabled automatically.
 */
#if EASY_CONFIG_FUNCTION_TASK
#undef EASY_CONFIG_FUNCTION_HEAP
#define EASY_CONFIG_FUNCTION_HEAP 1
#endif

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _EASY_TOOLS_CONFIG_DEFAULT_H_ */
