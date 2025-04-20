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

#include <stdio.h>

#include "display.h"
#include "buffer.h"

#define CLR "\e[1;1H\e[2J"
#define HEADER "\e[0;33m          " \
    "0011 2233 4455 6677 8899 aabb ccdd eeff  " \
    "0123456789abcdef\e[0;0m\r\n"

void display_draw(void)
{
    size_t addr = buffer_ctx.window.first_row;
    uint8_t *buff_p = buffer_ctx.buf;

    (void)addr;
    (void)buff_p;

    printf("%s", CLR);
    printf("%s", HEADER);

    while (0) /* There are still more bytes to print */
    {
        /* Print address */

        /* Print bytes */

        /* Print ASCII */
    }

    return;
}
