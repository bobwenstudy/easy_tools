#include "windows.h"
#include <stdio.h>
#include <string.h>

#include "easy_tools.h"

extern int example_test(void);
extern int example_user(void);

extern void test_ringbuffer(void);
extern void test_data_ringbuffer(void);
extern void test_pool_ringbuffer(void);

extern void test_task(void);
extern void test_task_polling(void);

extern void test_timer(void);

static void test_work(void)
{
    EASY_LOG_INF("Test work\r\n");

    // test buffer management
    test_ringbuffer();
    test_data_ringbuffer();
    test_pool_ringbuffer();

    // test task management
    test_task();

    // test timer management
    test_timer();
}

static void test_work_polling(void)
{
    // task polling
    test_task_polling();
}

int main(void)
{
    // initialize easy tools
    easy_tools_init();

    EASY_LOG_INF("Application running\r\n");

    test_work();

    while (1)
    {
        // polling work
        easy_tools_polling_work();

        test_work_polling();

        /* Artificial sleep to offload win process */
        Sleep(1);
    }
    return 0;
}
