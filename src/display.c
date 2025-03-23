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
