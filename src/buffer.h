#ifndef __BUFFER_H__
#define __BUFFER_H__

struct Buffer_Ctx{
    /* Buffer contents */
    uint8_t *buf;

    struct {
        uint64_t position;
    } point;
    
};

extern struct Buffer_Ctx buffer_ctx;

uint64_t buffer_getPosition(void);

#endif /* __BUFFER_H__ */
