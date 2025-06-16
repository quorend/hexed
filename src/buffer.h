#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stddef.h>

/**
 * @struct Buffer_Ctx
 * @brief Contains context information about the buffer. This information is
 *        used e.g. for navigating and displaying the buffer.
 */
struct Buffer_Ctx {
    /* Buffer contents */
    uint8_t *buf;
    /* Number of bytes in buffer */
    size_t buf_len;
    /* Determine which address to show at the top of the address frame */
    size_t first_row;
    /* Position of point as offset from the begining of buffer */
    size_t point_pos;
};

/**
 * @brief Initialize Buffer_Ctx struct.
 * @param[in,out] buffer_ctx structure to initialize
 * @return void
 */
void buffer_init(struct Buffer_Ctx *buffer_ctx);

/**
 * @brief Get position of point (cursor).
 * @param[in] buffer_ctx buffer context structure
 * @return position of point as offset from the begining of buffer
 */
size_t buffer_getPosition(struct Buffer_Ctx *buffer_ctx);

#endif /* __BUFFER_H__ */
