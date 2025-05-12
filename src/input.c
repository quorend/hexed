/*******************************************************************************
 * MIT License
 *
 * Copyright (c) 2025 Dillon Johnson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#include <unistd.h>

#include "input.h"
#include "display.h"
#include "buffer.h"

void input_accept(void)
{
    unsigned char c;

    display_draw();

    while (1)
    {
        read(STDIN_FILENO, &c, 1);

        if (c == '\033') /* ESC character */
        {
            read(STDIN_FILENO, &c, 1);
            if (c == '[')
            {
                read(STDIN_FILENO, &c, 1);
                switch (c)
                {
                case 'A': /* UP arrow */
                    if (buffer_getPosition() > 0xF)
                    {
                        buffer_ctx.point.position = buffer_getPosition() - 0x10;
                    }
                    break;
                case 'B': /* DOWN arrow */
                    if (buffer_getPosition() < buffer_ctx.buf_len - 0x10)
                    {
                        buffer_ctx.point.position = buffer_getPosition() + 0x10;
                    }
                    break;
                case 'C': /* RIGHT arrow */
                    if (buffer_getPosition() < buffer_ctx.buf_len - 1)
                    {
                        buffer_ctx.point.position++;
                    }
                    break;
                case 'D': /* LEFT arrow */
                    if (buffer_getPosition() > 0)
                    {
                        buffer_ctx.point.position--;
                    }
                    break;
                default:
                    break;
                }
            }

            display_draw();
        }
        else if (c == '\004') /* C-d */
        {
            break;
        }
        else
        {
            buffer_ctx.buf[buffer_getPosition()] = c;
            display_draw();
        }
    }

    return;
}
