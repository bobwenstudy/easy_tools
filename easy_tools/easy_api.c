#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "easy_api.h"
#include "easy_log.h"

/**
 * @brief If you want to use log function, you must implement the following
 * function in your code.
 */
__EASY_WEAK__ void easy_tools_api_log(const char *format, ...)
{
}

/**
 * @brief If you want to use assert function, you must implement the following
 * function in your code.
 */
__EASY_WEAK__ void easy_tools_api_assert(const char *file, int line)
{
    while (1)
    {
    }
}

/**
 * @brief If you env will sleep/wfi, you must regiter the system timer interface
 * with the following functions.
 */
__EASY_WEAK__ void easy_tools_api_timer_start(uint32_t ms)
{
}

/**
 * @brief If you env will sleep/wfi, you must regiter the system timer interface
 * with the following functions.
 */
__EASY_WEAK__ void easy_tools_api_timer_stop(void)
{
}

/**
 * @brief If you want to use timer function, you must implement the following
 * function in your code. The clock source must be same with
 * <easy_tools_api_timer_start> and <easy_tools_api_timer_stop> functions.
 */
__EASY_WEAK__ uint32_t easy_tools_api_timer_get_current(void)
{
    return 0;
}

/**
 * @brief If you want to use delay function, you must implement the following
 * function in your code.
 */
__EASY_WEAK__ void easy_tools_api_delay(uint32_t ms)
{
}

/**
 * @brief If use heap, you must implement the following function in your code.
 */
__EASY_WEAK__ void easy_tools_api_heap_init(struct easy_heap_ptr *heap)
{
}

/**
 * @brief For some init process.
 */
__EASY_WEAK__ void easy_tools_api_init(void)
{
}
