#ifndef _EASY_API_H_
#define _EASY_API_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "easy_tools_config.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

// you can use define to implement interrupt disable and enable function, or use
// function.
int easy_hw_interrupt_disable(void);
void easy_hw_interrupt_enable(int level);

#ifndef __easy_disable_isr
#define __easy_disable_isr() int _egui_isr_level = easy_hw_interrupt_disable()
#endif

#ifndef __easy_enable_isr
#define __easy_enable_isr() easy_hw_interrupt_enable(_egui_isr_level)
#endif

struct easy_heap_ptr
{
    void *buf;
    uint32_t len;
};

void easy_tools_api_log(const char *format, ...);
void easy_tools_api_assert(const char *file, int line);
void easy_tools_api_timer_start(uint32_t ms);
void easy_tools_api_timer_stop(void);
uint32_t easy_tools_api_timer_get_current(void);
void easy_tools_api_delay(uint32_t ms);
void easy_tools_api_heap_init(struct easy_heap_ptr *heap);
void easy_tools_api_init(void);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _EASY_API_H_ */
