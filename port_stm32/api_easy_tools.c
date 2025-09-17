#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "easy_api.h"
#include "main.h"

static int isr_closed_cnt = 0;
int easy_hw_interrupt_disable(void)
{
    __disable_irq();

    ++isr_closed_cnt;
    return isr_closed_cnt;
}

void easy_hw_interrupt_enable(int level)
{
    isr_closed_cnt--;
    if (isr_closed_cnt < 0)
    {
        isr_closed_cnt = 0;
    }
    if (isr_closed_cnt == 0)
    {
        __enable_irq();
    }
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

uint32_t easy_tools_api_timer_get_current(void)
{
    return HAL_GetTick();
}

void easy_tools_api_delay(uint32_t ms)
{
    HAL_Delay(ms);
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
}
