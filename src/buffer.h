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

extern struct Buffer_Ctx buffer_ctx;

void buffer_init(void);

uint64_t buffer_getPosition(void);

#endif /* __BUFFER_H__ */
