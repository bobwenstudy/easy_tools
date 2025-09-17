#include <stddef.h>
#include <stdint.h>

#include "easy_api.h"
#include "easy_dlist.h"
#include "easy_heap.h"
#include "easy_task.h"

#if EASY_CONFIG_FUNCTION_TASK
static easy_dlist_t task_list;

void easy_task_send_msg(struct easy_task *task, struct easy_msg *msg)
{
    if (msg == NULL)
    {
        return;
    }
    __easy_disable_isr();
    easy_dlist_append(&task->msg_list, &msg->node);
    __easy_enable_isr();
}

void easy_task_delete(struct easy_task *task)
{
    __easy_disable_isr();
    easy_dlist_remove(&task->node);
    __easy_enable_isr();
}

void easy_task_create(struct easy_task *task)
{
    easy_dlist_init(&(task->msg_list));
    __easy_disable_isr();
    easy_dlist_append(&task_list, &task->node);
    __easy_enable_isr();
}

int easy_task_check_task_empty(void)
{
    return easy_dlist_is_empty(&task_list);
}

int easy_task_check_empty(void)
{
    easy_dnode_t *p_task_head, *p_msg_head, *p_msg_temp;
    struct easy_task *tmp;

    int is_empty = 1;

    __easy_disable_isr();
    if (!easy_dlist_is_empty(&task_list))
    {
        EASY_DLIST_FOR_EACH_NODE(&task_list, p_task_head)
        {
            tmp = (struct easy_task *)p_task_head;

            if (!easy_dlist_is_empty(&(tmp->msg_list)))
            {
                is_empty = 0;
                break;
            }
        }
    }
    __easy_enable_isr();

    return is_empty;
}

void easy_task_polling(void)
{
    easy_dnode_t *p_task_head, *p_msg_head, *p_msg_temp;
    struct easy_task *tmp;

    if (!easy_dlist_is_empty(&task_list))
    {
        EASY_DLIST_FOR_EACH_NODE(&task_list, p_task_head)
        {
            tmp = (struct easy_task *)p_task_head;

            EASY_DLIST_FOR_EACH_NODE_SAFE(&(tmp->msg_list), p_msg_head, p_msg_temp)
            {
                struct easy_msg *msg = (struct easy_msg *)p_msg_head;

                int ret = tmp->func(msg);
                if (ret != EASY_TASK_HDL_CONSUMED)
                {
                    break;
                }

                __easy_disable_isr();
                easy_dlist_remove(p_msg_head);
                __easy_enable_isr();

                easy_msg_free(msg);
            }
        }
    }
}

void easy_task_init(void)
{
    easy_dlist_init(&(task_list));
}

#endif // EASY_CONFIG_FUNCTION_TASK
