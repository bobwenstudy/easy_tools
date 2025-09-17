#include <stdio.h>
#include <stdlib.h>

#include "easy_tools.h"

#if EASY_CONFIG_FUNCTION_TASK
struct easy_task user_task1;
struct easy_task user_task2;

static int test_msg_consumed_user_task1 = 0;
static int test_msg_consumed_user_task2 = 0;

int user_task1_func(struct easy_msg *msg)
{
    EASY_LOG_DBG("user_task1(), id: 0x%x, len: %d\n", msg->id, msg->param_len);
    for (int i = 0; i < msg->param_len; i++)
    {
        EASY_LOG_DBG("0x%x:", ((uint8_t *)msg->param)[i]);
    }
    if (msg->param_len)
    {
        EASY_LOG_DBG("\n");
    }

    if (test_msg_consumed_user_task1 == 0)
    {
        test_msg_consumed_user_task1 = 1;
        EASY_LOG_DBG("EASY_TASK_HDL_SAVED\n");
        return EASY_TASK_HDL_SAVED;
    }

    return EASY_TASK_HDL_CONSUMED;
}

void user_task1_test(void)
{
    struct easy_task *p_task = &user_task1;

    p_task->func = user_task1_func;
    easy_task_create(p_task);

    easy_task_send_msg(p_task, easy_msg_alloc(1, 0, NULL));
    easy_task_send_msg(p_task, easy_msg_alloc(2, 0, NULL));
    uint8_t data[10];
    for (int i = 0; i < sizeof(data); i++)
    {
        data[i] = i;
    }
    easy_task_send_msg(p_task, easy_msg_alloc(0x10, sizeof(data), data));
    for (int i = 0; i < sizeof(data); i++)
    {
        data[i] = i + 0x10;
    }
    easy_task_send_msg(p_task, easy_msg_alloc(0x11, sizeof(data), data));
}

int user_task2_func(struct easy_msg *msg)
{
    EASY_LOG_DBG("user_task2(), id: 0x%x, len: %d\n", msg->id, msg->param_len);
    for (int i = 0; i < msg->param_len; i++)
    {
        EASY_LOG_DBG("0x%x:", ((uint8_t *)msg->param)[i]);
    }
    if (msg->param_len)
    {
        EASY_LOG_DBG("\n");
    }

    if (test_msg_consumed_user_task2 == 0 && msg->id > 0x10)
    {
        test_msg_consumed_user_task2 = 1;
        EASY_LOG_DBG("EASY_TASK_HDL_SAVED\n");
        return EASY_TASK_HDL_SAVED;
    }

    return EASY_TASK_HDL_CONSUMED;
}

void user_task2_test(void)
{
    struct easy_task *p_task = &user_task2;

    p_task->func = user_task2_func;
    easy_task_create(p_task);

    easy_task_send_msg(p_task, easy_msg_alloc(8, 0, NULL));
    easy_task_send_msg(p_task, easy_msg_alloc(9, 0, NULL));
    uint8_t data[20];
    for (int i = 0; i < sizeof(data); i++)
    {
        data[i] = i;
    }
    easy_task_send_msg(p_task, easy_msg_alloc(0x50, sizeof(data), data));
    for (int i = 0; i < sizeof(data); i++)
    {
        data[i] = i + 0x10;
    }
    easy_task_send_msg(p_task, easy_msg_alloc(0x51, sizeof(data), data));

#define TEST_ALLOC_LEN 100
    struct easy_msg *msg = easy_msg_alloc_len(0x51, TEST_ALLOC_LEN);
    for (int i = 0; i < TEST_ALLOC_LEN; i++)
    {
        msg->param[i] = i + 0x50;
    }
    easy_task_send_msg(p_task, msg);
}

void test_task(void)
{
    EASY_LOG_INF("Heap Remain Size: 0x%x\n", easy_heap_get_remain_size());

    user_task1_test();
    user_task2_test();

    // Test task delete
    // easy_task_delete(&user_task1);
    // easy_task_delete(&user_task2);

    EASY_LOG_DBG("Task Start Work!\n");
}

static int check_task_end;
static int task_check_end(void)
{
    if (easy_task_check_empty())
    {
        EASY_LOG_DBG("Task End Work!\n");
        EASY_LOG_DBG("Heap Remain Size: 0x%x\n", easy_heap_get_remain_size());
        if (!easy_heap_check_empty())
        {
            EASY_LOG_DBG("Something Error!\n");
        }

        return 1;
    }

    return 0;
}

void test_task_polling(void)
{
    // verify task work end.
    if (!check_task_end)
    {
        check_task_end = task_check_end();
    }
}

#else
void test_task(void)
{
}
void test_task_polling(void)
{
}
#endif
