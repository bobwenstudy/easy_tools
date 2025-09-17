#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "easy_api.h"
#include "easy_heap.h"
#include "easy_msg.h"

void *easy_msg_alloc_len(uint16_t id, uint16_t const param_len)
{
    __easy_disable_isr();
    struct easy_msg *msg = (struct easy_msg *)easy_heap_malloc(sizeof(struct easy_msg) + param_len);
    __easy_enable_isr();

    if (msg == NULL)
    {
        return NULL;
    }

    memset(msg, 0, sizeof(struct easy_msg) + param_len);

    msg->id = id;
    msg->param_len = param_len;

    return msg;
}

void *easy_msg_alloc(uint16_t id, uint16_t const param_len, void *param)
{
    struct easy_msg *msg = easy_msg_alloc_len(id, param_len);

    if (msg == NULL)
    {
        return NULL;
    }

    memcpy(msg->param, param, param_len);

    return msg;
}

void easy_msg_free(struct easy_msg *msg)
{
    __easy_disable_isr();
    easy_heap_free(msg);
    __easy_enable_isr();
}
