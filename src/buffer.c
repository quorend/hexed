#include <stdint.h>

#include "buffer.h"

struct Buffer_Ctx buffer_ctx;

uint64_t buffer_getPosition(void)
{
    return buffer_ctx.point.position;
}
