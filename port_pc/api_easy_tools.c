#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "easy_api.h"
#include "windows.h"

int easy_hw_interrupt_disable(void)
{
    return 0;
}

void easy_hw_interrupt_enable(int level)
{
    return;
}

void easy_tools_api_log(const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);
}

void easy_tools_api_assert(const char *file, int line)
{
#if EASY_CONFIG_DEBUG_LOG_LEVEL >= EASY_LOG_IMPL_LEVEL_DBG
    static char s_buf[0x200];
    memset(s_buf, 0, sizeof(s_buf));
    sprintf(s_buf,
            "vvvvvvvvvvvvvvvvvvvvvvvvvvvv\n\nAssert@ file = %s, line = "
            "%d\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n",
            file, line);
    printf("%s", s_buf);
#endif

    while (1)
    {
    };
}

void easy_tools_api_timer_start(uint32_t ms)
{
}

void easy_tools_api_timer_stop(void)
{
}

static LARGE_INTEGER freq, sys_start_time;
static uint32_t get_tick(void);

uint32_t easy_tools_api_timer_get_current(void)
{
    return get_tick();
}

void easy_tools_api_delay(uint32_t ms)
{
    Sleep(ms);
}

/**
 * \brief           Get current tick in ms from start of program
 * \return          uint32_t: Tick in ms
 */
static uint32_t get_tick(void)
{
    LONGLONG ret;
    LARGE_INTEGER now;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&now);
    ret = now.QuadPart - sys_start_time.QuadPart;
    return (uint32_t)((ret * 1000) / freq.QuadPart);
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
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&sys_start_time);
}
