#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdbool.h>

#include "buffer.h"

void display_draw(struct Buffer_Ctx *buffer_ctx, bool clear);

#endif /* __DISPLAY_H__ */
