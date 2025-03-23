#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stddef.h>

struct Buffer_Ctx{
    /* Buffer contents */
    uint8_t *buf;

    struct {
        /* Determine which address to show at the top of the address frame */
        size_t first_row;
        /* Determine which byte to show first in the byte frame */
        uint8_t *first_byte;
    } window;

    struct {
        uint64_t position;
    } point;
    
};

extern struct Buffer_Ctx buffer_ctx;

void buffer_init(void);

void buffer_allocBuffer(void);

uint64_t buffer_getPosition(void);

#endif /* __BUFFER_H__ */
