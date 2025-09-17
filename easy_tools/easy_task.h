/**
 * @file           inkvs.h
 * @author         Injoinic
 * @version        v0.0.1
 * @date           2022-12-29
 * @copyright      Copyright(c) 2022 Injoinic Technology
 * @brief          Injoinic Key Value Storage(INKVS)
 *
 */
#ifndef _EASY_TASK_H_
#define _EASY_TASK_H_

/** Includes -----------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

#include "easy_dlist.h"
#include "easy_msg.h"

/** Define -------------------------------------------------------------------*/
enum easy_task_hdl_result
{
    EASY_TASK_HDL_CONSUMED = 0, ///< consumed, msg and ext are freed by the kernel
    EASY_TASK_HDL_SAVED,        ///< not consumed, will be pushed in the saved queue
};

typedef int (*easy_task_func_t)(struct easy_msg *msg);

typedef struct easy_task
{
    easy_dnode_t node;

    easy_dnode_t msg_list;

    easy_task_func_t func;
} easy_task_t;

/** Exported functions -------------------------------------------------------*/

void easy_task_send_msg(struct easy_task *task, struct easy_msg *msg);

void easy_task_delete(struct easy_task *task);

void easy_task_create(struct easy_task *task);

void easy_task_polling(void);

int easy_task_check_empty(void);

void easy_task_init(void);

#endif /*!< _EASY_TASK_H_ */
