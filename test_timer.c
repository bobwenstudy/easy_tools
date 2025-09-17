#include <stdio.h>
#include <stdlib.h>

#include "easy_tools.h"

static uint32_t test_cnt;
static easy_timer_t test_user_timer;

void test_timer_callback(easy_timer_t *timer)
{
    uint32_t *user_data = (uint32_t *)timer->user_data;
    *user_data += 1;
    EASY_LOG_INF("Timer callback called: %d\r\n", *user_data);
}

void timer_init(void)
{
    easy_timer_init_timer(&test_user_timer, test_timer_callback, &test_cnt);
    easy_timer_start_timer(&test_user_timer, 0, 1000);

    EASY_LOG_DBG("Timer Start Work!\n");
}

void test_timer(void)
{
    timer_init();
}
