#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stddef.h>

struct Buffer_Ctx {
    /* Buffer contents */
    uint8_t *buf;
    /* Number of bytes in buffer */
    size_t buf_len;

    /* Determine which address to show at the top of the address frame */
    size_t first_row;

    uint64_t point_pos;
    
};

void buffer_init(struct Buffer_Ctx *buffer_ctx);

uint64_t buffer_getPosition(struct Buffer_Ctx *buffer_ctx);

#endif /* __BUFFER_H__ */
