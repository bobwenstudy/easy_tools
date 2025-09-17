#ifndef _EASY_TIMER_H_
#define _EASY_TIMER_H_

#include <stdint.h>

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

#define EASY_TIMER_ZERO (0)

typedef struct easy_timer easy_timer_t;

typedef void (*easy_timer_callback_func)(easy_timer_t *);

struct easy_timer
{
    struct easy_timer *next;
    uint32_t expiry_time;
    easy_timer_callback_func callback;
    uint32_t period;
    void *user_data;
};

void easy_timer_polling_work(void);
int easy_timer_start_timer(easy_timer_t *handle, uint32_t ms, uint32_t period);
void easy_timer_stop_timer(easy_timer_t *handle);
void easy_timer_init_timer(easy_timer_t *handle, easy_timer_callback_func callback, void *user_data);
int easy_timer_check_timer_start(easy_timer_t *handle);
void easy_timer_init(void);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /*!< _EASY_TIMER_H_ */
