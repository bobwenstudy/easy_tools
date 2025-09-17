#ifndef _EASY_HEAP_H_
#define _EASY_HEAP_H_

/** Includes -----------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

/** Define -------------------------------------------------------------------*/

/** Exported functions -------------------------------------------------------*/
void *easy_heap_malloc(uint32_t xWantedSize);
void easy_heap_free(void *pv);
void easy_heap_init(uint32_t *heap, uint32_t size);

uint32_t easy_heap_get_remain_size(void);
int easy_heap_check_empty(void);

#endif /*!< _EASY_HEAP_H_ */
