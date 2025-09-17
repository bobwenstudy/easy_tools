#ifndef _EASY_TOOLS_H_
#define _EASY_TOOLS_H_

#include <stdint.h>
#include <stdio.h>

#include "easy_tools_config.h"

#include "easy_api.h"
#include "easy_log.h"
#include "easy_timer.h"

#include "easy_dlist.h"
#include "easy_slist.h"

#include "easy_heap.h"
#include "easy_msg.h"
#include "easy_task.h"

#include "easy_data_ringbuffer.h"
#include "easy_pool.h"
#include "easy_ringbuffer.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

int easy_tools_check_need_polling_work(void);
void easy_tools_polling_work(void);
void easy_tools_init(void);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _EASY_TOOLS_H_ */
