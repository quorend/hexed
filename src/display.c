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

#define HOME "\e[1;1H"
#define CLR "\e[2J"
#define RESET_COLORS "\e[0;0m"

#define HEADER "\e[0;33m            " \
    "0011 2233 4455 6677 8899 aabb ccdd eeff  " \
    "0123456789abcdef\e[0;0m\r\n"

#define BYTE_HEX "%02X"
#define BYTE_HEX_HIGHLIGHT "\e[41m%02X\e[m"
#define BYTE_CHAR "%c"
#define BYTE_CHAR_HIGHLIGHT "\e[41m%c\e[m"

#define ASCII_STR_LEN 17 /* 16 characters plus NULL character */

#define MODE_R_0 "\e[33mR\e[m"
#define MODE_R_1 "\e[41mR\e[m"
#define MODE_E_0 "\e[33mE\e[m"
#define MODE_E_1 "\e[41mE\e[m"
#define MODE_W_0 "\e[33mW\e[m"
#define MODE_W_1 "\e[41mW\e[m"
#define ADVANCE_0 " \e[33mA\e[m"
#define ADVANCE_1 " \e[41mA\e[m"

void display_draw(struct Buffer_Ctx *buffer_ctx, bool clear)
{
    /* Used for printing the hex byte counts in the left column. */
    size_t addr = buffer_ctx->first_row;
    /* A pointer to the buffer that holds the file contents. */
    uint8_t *buff = buffer_ctx->buf;
    /* A buffer to hold the current row's ascii representation for printing. */
    char ascii[ASCII_STR_LEN];

    printf("%s", HOME);

    if (clear == true)
    {
        printf("%s", CLR);
    }
    printf("%s", HEADER);

    /* TODO: Use terminal height to determine this. */
    while ((addr < 0x200) && (addr < buffer_ctx->buf_len))
    {
        memset(ascii, '\0', ASCII_STR_LEN);

        /* Print address */
        printf("0x%08zX  ", addr);

        /* Print bytes */
        for(uint8_t i = 0; i < 16; i++)
        {
            /* Flag to indicate no ASCII should be printed for this byte. */
            bool no_ascii = false;

            if ((addr + i) < buffer_ctx->buf_len)
            {
                if ((addr + i) != buffer_getPosition(buffer_ctx))
                {
                    printf(BYTE_HEX, buff[addr + i]);
                }
                else
                {
                    printf(BYTE_HEX_HIGHLIGHT, buff[addr + i]);
                }
            }
            else
            {
                /* Don't try to print bytes beyond the length of the buffer. */
                printf("  ");
                no_ascii = true;
            }

            /* Print a space between pairs of bytes. */
            if((i % 2) == 1)
            {
                printf(" ");
            }

            if (no_ascii == false)
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
        printf(" ");
        for (uint8_t i = 0; ascii[i] != '\0'; i++)
        {
            if (i > 0xF)
            {
                break;
            }

            if ((addr + i) != buffer_getPosition(buffer_ctx))
            {
                printf(BYTE_CHAR, ascii[i]);
            }
            else
            {
                printf(BYTE_CHAR_HIGHLIGHT, ascii[i]);
            }
        }
        printf("\r\n");

        addr += 0x10;
    }

    /* Print footer */
    printf(buffer_ctx->mode == MODE_OVERWRITE ? MODE_W_1 : MODE_W_0);
    printf(buffer_ctx->mode == MODE_INSERT ? MODE_E_1 : MODE_E_0);
    printf(buffer_ctx->mode == MODE_READ ? MODE_R_1 : MODE_R_0);
    printf(buffer_ctx->advance == true ? ADVANCE_1 : ADVANCE_0);
    printf(RESET_COLORS "\r\n");

    return;
}
