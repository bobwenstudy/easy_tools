#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "easy_api.h"
#include "rtthread.h"

int easy_hw_interrupt_disable(void)
{
    return rt_hw_interrupt_disable();
}

void easy_hw_interrupt_enable(int level)
{
    rt_hw_interrupt_enable(level);
}

static void easy_tools_api_log_va(const char *format, va_list argptr)
{
    static char log_printf_buffer[0x100];

    rt_vsnprintf(log_printf_buffer, sizeof(log_printf_buffer), format, argptr);

    rt_kprintf(log_printf_buffer);
}

void easy_tools_api_log(const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    easy_tools_api_log_va(format, argptr);
    va_end(argptr);
}

void easy_tools_api_assert(const char *file, int line)
{
#if EASY_CONFIG_DEBUG_LOG_LEVEL >= EASY_LOG_IMPL_LEVEL_DBG
    static char s_buf[0x200];
    memset(s_buf, 0, sizeof(s_buf));
    rt_sprintf(s_buf,
               "vvvvvvvvvvvvvvvvvvvvvvvvvvvv\n\nAssert@ file = %s, line = "
               "%d\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n",
               file, line);
    rt_kprintf("%s", s_buf);
#endif

    while (1)
    {
    };
}

static rt_timer_t api_timer = RT_NULL;
static void api_timer_timeout(void *parameter)
{
    // do nothing
    // rt_kprintf("api_timer_timeout\n");
}

void easy_tools_api_timer_start(uint32_t ms)
{
    /* reset the timeout of thread timer and start it */
    int32_t diff_time = ms - easy_tools_api_timer_get_current();
    if (diff_time < 0)
    {
        diff_time = 0;
    }
    diff_time = rt_tick_from_millisecond(diff_time);
    rt_timer_control(api_timer, RT_TIMER_CTRL_SET_TIME, &diff_time);
    rt_timer_start(api_timer);
}

void easy_tools_api_timer_stop(void)
{
    rt_timer_stop(api_timer);
}

uint32_t easy_tools_api_timer_get_current(void)
{
    return rt_tick_get_millisecond();
}

void easy_tools_api_delay(uint32_t ms)
{
    rt_thread_mdelay(ms);
}

#if EASY_CONFIG_FUNCTION_HEAP
static uint8_t user_heap[0x1000];
void easy_tools_api_heap_init(struct easy_heap_ptr *heap)
{
    heap->buf = user_heap;
    heap->len = sizeof(user_heap);
}
#endif

void easy_tools_api_init(void)
{
    api_timer = rt_timer_create("easy_api", api_timer_timeout, RT_NULL, 1000, RT_TIMER_FLAG_SOFT_TIMER);
}
