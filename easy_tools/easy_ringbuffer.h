#ifndef _EASY_RINGBUFFER_H_
#define _EASY_RINGBUFFER_H_

#include <stddef.h>
#include <stdint.h>

typedef struct easy_ringbuffer
{
    uint32_t total_size;  /* Number of buffers */
    uint32_t read_index;  /* Read. Read index */
    uint32_t write_index; /* Write. Write index */
    uint8_t *buffer;
} easy_ringbuffer_t;

#define EASY_RINGBUFFER_DEFINE(_name, _num)                                                                                                                    \
    static uint8_t _name##_data_storage[_num];                                                                                                                 \
    static easy_ringbuffer_t _name = {.total_size = _num, .write_index = 0, .read_index = 0, .buffer = (void *)_name##_data_storage}

#define EASY_RINGBUFFER_INIT(_name, _num) easy_ringbuffer_init(&_name, _num, (void *)_name##_data_storage)

/**
 * @brief  Returns the size of the RINGBUF in bytes.
 * @param  [in] ringbuf: The ringbuf to be used.
 * @return The size of the RINGBUF.
 */
static inline uint32_t easy_ringbuffer_total_size(easy_ringbuffer_t *ringbuf)
{
    return ringbuf->total_size;
}

/**
 * @brief  Reset the RINGBUF.
 * @param  [in] ringbuf: The ringbuf to be used.
 */
static inline void easy_ringbuffer_reset(easy_ringbuffer_t *ringbuf)
{
    ringbuf->write_index = 0;
    ringbuf->read_index = 0;
}

/**
 * @brief  Initialize the RINGBUF.
 * @param  [in] ringbuf: The ringbuf to be used.
 * @param  [in] total_size: The total size of the RINGBUF.
 * @param  [in] buffer: The buffer to be used.
 */
static inline void easy_ringbuffer_init(easy_ringbuffer_t *ringbuf, uint32_t total_size, uint8_t *buffer)
{
    ringbuf->total_size = total_size;
    ringbuf->write_index = 0;
    ringbuf->read_index = 0;
    ringbuf->buffer = buffer;
}

/**
 * @brief  Check if the RINGBUF is empty.
 * @param  [in] ringbuf: The ringbuf to be used.
 * @return 1 if the RINGBUF is empty, 0 otherwise.
 */
static inline int easy_ringbuffer_is_empty(easy_ringbuffer_t *ringbuf)
{
    return ringbuf->read_index == ringbuf->write_index;
}

/**
 * @brief  Returns the used size of the RINGBUF in bytes.
 * @param  [in] ringbuf: The ringbuf to be used.
 * @return The used size of the RINGBUF in bytes.
 */
static inline uint32_t easy_ringbuffer_size(easy_ringbuffer_t *ringbuf)
{
    return ringbuf->write_index >= ringbuf->read_index ? ringbuf->write_index - ringbuf->read_index
                                                       : (ringbuf->total_size << 1) - (ringbuf->read_index - ringbuf->write_index);
}

/**
 * @brief  Returns the free size of the RINGBUF in bytes.
 * @param  [in] ringbuf: The ringbuf to be used.
 * @return The free size of the RINGBUF in bytes.
 */
static inline uint32_t easy_ringbuffer_reserve_size(easy_ringbuffer_t *ringbuf)
{
    return ringbuf->total_size - easy_ringbuffer_size(ringbuf);
}

/**
 * @brief  Check if the RINGBUF is full.
 * @param  [in] ringbuf: The ringbuf to be used.
 */
static inline int easy_ringbuffer_is_full(easy_ringbuffer_t *ringbuf)
{
    return easy_ringbuffer_size(ringbuf) == ringbuf->total_size;
}

/**
 * @brief  Put data into the RINGBUF.
 * @param  [in] ringbuf: The ringbuf to be used.
 * @param  [in] buffer: The buffer to be put into the RINGBUF.
 * @param  [in] len: The length of the buffer.
 * @return The length of the buffer put into the RINGBUF.
 */
uint32_t easy_ringbuffer_put(easy_ringbuffer_t *ringbuf, uint8_t *buffer, uint32_t len);

/**
 * @brief  Get data from the RINGBUF.
 * @param  [in] ringbuf: The ringbuf to be used.
 * @param  [in] buffer: The buffer to be put into the RINGBUF.
 * @param  [in] len: The length of the buffer.
 * @return The length of the buffer get from the RINGBUF.
 */
uint32_t easy_ringbuffer_get(easy_ringbuffer_t *ringbuf, uint8_t *buffer, uint32_t len);

#endif /* _EASY_RINGBUFFER_H_ */