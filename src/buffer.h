#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stddef.h>

struct Buffer_Ctx{
    /* Buffer contents */
    uint8_t *buf;

    struct {
        uint64_t position;
    } point;
    
};

extern struct Buffer_Ctx buffer_ctx;

void buffer_init(void);

void buffer_allocBuffer(void);

uint64_t buffer_getPosition(void);

#endif /* __BUFFER_H__ */
