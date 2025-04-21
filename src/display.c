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
#include <string.h>

#include "display.h"
#include "buffer.h"

#define CLR "\e[1;1H\e[2J"
#define HEADER "\e[0;33m            " \
    "0011 2233 4455 6677 8899 aabb ccdd eeff  " \
    "0123456789abcdef\e[0;0m\r\n"
#define ASCII_STR_LEN 17 /* 16 characters plus NULL character */

void display_draw(void)
{
    /* Used for printing the hex byte counts in the left column. */
    size_t addr = buffer_ctx.window.first_row;
    /* A pointer to the buffer that holds the file contents. */
    uint8_t *buff = buffer_ctx.buf;
    /* A buffer to hold the current row's ascii representation for printing. */
    char ascii[ASCII_STR_LEN];

    printf("%s", CLR);
    printf("%s", HEADER);

    while (addr < 0x200) /* TODO: Use terminal height to determine this. */
    {
        memset(ascii, '\0', ASCII_STR_LEN);

        /* Print address */
        printf("0x%08zX  ", addr);

        /* Print bytes */
        for(uint8_t i = 0; i < 16; i++)
        {
            printf("%02X", buff[addr + i]);
            if((i % 2) == 1)
            {
                printf(" ");
            }

            {
                char temp[2];
                if ((buff[addr + i] > 0x1F) && (buff[addr + i] < 0x7F))
                {
                    snprintf(temp, 2, "%c", buff[addr + i]);
                }
                else
                {
                    /* Use period instead of printing special characters. */
                    snprintf(temp, 2, ".");
                }
                strcat(ascii, temp);
            }
        }

        /* Print ASCII */
        printf(" %s\r\n", ascii);

        addr += 0x10;
    }

    return;
}
