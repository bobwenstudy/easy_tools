#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "easy_tools.h"

/**
 * @brief Check if need polling work of the easy tools library.
 * For low power case, user must implement <easy_tools_api_timer_start> and
 * <easy_tools_api_timer_stop> to control the timer.
 */
int easy_tools_check_need_polling_work(void)
{
    int need_polling_work = 0;

#if EASY_CONFIG_FUNCTION_TASK
    if (!easy_task_check_empty())
    {
        need_polling_work = 1;
    }
#endif

    return need_polling_work;
}

/**
 * @brief Polling work of the easy tools library.
 */
void easy_tools_polling_work(void)
{
    easy_timer_polling_work();
#if EASY_CONFIG_FUNCTION_TASK
    easy_task_polling();
#endif
}

/**
 * @brief Initialize the easy tools library.
 */
void easy_tools_init(void)
{
    easy_tools_api_init();
#if EASY_CONFIG_FUNCTION_TASK
    easy_task_init();
#endif
#if EASY_CONFIG_FUNCTION_HEAP
    struct easy_heap_ptr heap;
    easy_tools_api_heap_init(&heap);
    easy_heap_init(heap.buf, heap.len);
#endif
}
