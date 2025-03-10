#include <stdio.h>

#include "display.h"

#define HEADER "\e[0;33m87654321  " \
    "0011 2233 4455 6677 8899 aabb ccdd eeff  " \
    "0123456789abcdef\e[0;0m\r\n"

void display_draw(void)
{
    printf("%s", HEADER);

    return;
}
