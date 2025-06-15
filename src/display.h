#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdbool.h>

#include "buffer.h"

/**
 * @brief Draw the user interface.
 * @param[in] buffer_ctx buffer context structure
 * @param[in] clear true if the display should be cleared before drawing
 * @return void
 */
void display_draw(struct Buffer_Ctx *buffer_ctx, bool clear);

#endif /* __DISPLAY_H__ */
