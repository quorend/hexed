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
#include <stdlib.h>
#include <unistd.h>

#include "file-access.h"
#include "buffer.h"
#include "terminal.h"
#include "input.h"

#define VERSION "1.0.0"

static void print_version(char *name);
static void print_help(char *name);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        /* Process each argument */
        for (int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                /* Options */
                if (argv[i][1] == '-')
                {
                    /* Long option */
                    if (strcmp(argv[i], "--version") == 0)
                    {
                        print_version(argv[0]);
                    }
                    else if (strcmp(argv[i], "--help") == 0)
                    {
                        print_help(argv[0]);
                    }
                }
                else
                {
                    /* Short option */
                    if (strcmp(argv[i], "-v") == 0)
                    {
                        print_version(argv[0]);
                    }
                    else if (strcmp(argv[i], "-h") == 0)
                    {
                        print_help(argv[0]);
                    }
                }
            }
            else
            {
                /* Filename */
                struct Buffer_Ctx buffer_ctx;
                int rc = 0;

                buffer_init(&buffer_ctx);

                rc = file_access_loadFile(&buffer_ctx, argv[1]);
                if (rc != 0)
                {
                    printf("ERR: file_access_loadFile()\r\n");
                    return 0;
                }

                set_input_mode();

                rc = input_accept(&buffer_ctx, STDIN_FILENO);
                if (rc > 0)
                {
                    printf("ERR: input_accept(): %s\r\n", strerror(rc));
                }
                else if (rc < 0)
                {
                    printf("ERR: file_access_saveFile(): %d\r\n", rc);
                }

                free(buffer_ctx.buf);
            }
        }
    }
    else
    {
        print_help(argv[0]);
    }

    return 0;
}

static void print_version(char *name)
{
    printf("%s v%s\r\n", strrchr(name, '/') + 1, VERSION);

    return;
}

static void print_help(char *name)
{
    printf(
        "%s [OPTIONS] [PATH TO FILE]\r\n"
        "\r\n"
        "OPTIONS:\r\n"
        "-h --help\r\n"
        "           Display this help text.\r\n"
        "-v --version\r\n"
        "           Display version information.\r\n",
        strrchr(name, '/') + 1
        );

    return;
}
