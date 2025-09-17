#ifndef _EASY_MSG_H_
#define _EASY_MSG_H_

/** Includes -----------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

#include "easy_dlist.h"

/** Define -------------------------------------------------------------------*/
typedef struct easy_msg
{
    easy_dnode_t node;

    uint16_t id;
    uint16_t param_len;
    uint8_t param[]; ///< Parameter embedded struct. Must be word-aligned.
} easy_msg_t;

/** Exported functions -------------------------------------------------------*/
void *easy_msg_alloc_len(uint16_t id, uint16_t const param_len);
void *easy_msg_alloc(uint16_t id, uint16_t const param_len, void *param);
void easy_msg_free(struct easy_msg *msg);

#endif /*!< _EASY_MSG_H_ */
