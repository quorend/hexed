#include "buffer.h"

struct Buffer_Ctx buffer_ctx;

void buffer_init(void)
{
    buffer_ctx.buf = NULL;
    buffer_ctx.point.position = 0;

    return;
}

uint64_t buffer_getPosition(void)
{
    return buffer_ctx.point.position;
}
