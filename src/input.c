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
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#include "input.h"
#include "display.h"
#include "file-access.h"
#include "cutest/CuTest.h"

#define check_ec() \
do\
{\
    if (ec == -1)\
    {\
        rc = errno;\
        break;\
    }\
}\
while(0)

int input_accept(struct Buffer_Ctx *buffer_ctx, int fd)
{
    unsigned char c = '\0';
    ssize_t ec = 0;
    int rc = 0;

    display_draw(buffer_ctx, true);

    while (buffer_ctx->buf != NULL)
    {
        ec = read(fd, &c, 1);
        check_ec();

        if (c == '\033') /* ESC character */
        {
            ec = read(fd, &c, 1);
            check_ec();

            if (c == '[')
            {
                ec = read(fd, &c, 1);
                check_ec();

                switch (c)
                {
                case 'A': /* UP arrow */
                    if (buffer_getPosition(buffer_ctx) > 0xF)
                    {
                        buffer_ctx->point_pos -= 0x10;
                    }
                    break;
                case 'B': /* DOWN arrow */
                    if (buffer_getPosition(buffer_ctx) < buffer_ctx->buf_len - 0x10)
                    {
                        buffer_ctx->point_pos += 0x10;
                    }
                    break;
                case 'C': /* RIGHT arrow */
                    if (buffer_getPosition(buffer_ctx) < buffer_ctx->buf_len - 1)
                    {
                        buffer_ctx->point_pos++;
                    }
                    break;
                case 'D': /* LEFT arrow */
                    if (buffer_getPosition(buffer_ctx) > 0)
                    {
                        buffer_ctx->point_pos--;
                    }
                    break;
                default:
                    break;
                }
            }

            display_draw(buffer_ctx, false);
        }
        else if (c == '\004') /* C-d */
        {
            break;
        }
        else
        {
            buffer_ctx->buf[buffer_getPosition(buffer_ctx)] = c;
            display_draw(buffer_ctx, false);
        }

    }

    return rc;
}

/*
 * Unit Tests
 */

/**
 * @brief Common setup code for input_accept() tests.
 * @param[in] command_input quoted path to command input file
 * @param[in] buffer_input quoted path to buffer input file
 */
#define INPUT_TEST_SETUP(command_input, buffer_input) \
struct Buffer_Ctx buffer_ctx;\
int fd;\
int rc = 0;\
\
do\
{\
    fd = open(command_input, O_RDONLY);\
    if (fd == -1)\
    {\
        CuFail(tc, "Failed to open input file.");\
        goto __exit__;\
    }\
\
    buffer_init(&buffer_ctx);\
\
    rc = file_access_loadFile(&buffer_ctx, buffer_input);\
    if (rc != 0)\
    {\
        CuFail(tc, "Failed to load file.");\
        goto __close_file__;\
    }\
\
    input_accept(&buffer_ctx, fd);\
\
}\
while(0)

/**
 * @brief Common teardown code for input_accept() tests.
 */
#define INPUT_TEST_TEARDOWN \
do\
{\
    free(buffer_ctx.buf);\
\
__close_file__:\
    if (close(fd) == -1)\
    {\
        CuFail(tc, "Failed to close file descriptor.");\
    }\
\
__exit__:\
}\
while(0)

static void TestInputAcc_simple(CuTest *tc)
{
    /*
     * This command file has a single ASCII 'o' and then the program termination
     * byte. Thus, neither point_pos nor first_row should change from their
     * initial values.
     */

    INPUT_TEST_SETUP("test/input-simple", "test/lorem-ipsum.txt");

    CuAssertSizetEquals(tc, 0, buffer_ctx.point_pos);
    CuAssertSizetEquals(tc, 0x0, buffer_ctx.first_row);

    INPUT_TEST_TEARDOWN;

    return;
}

static void TestInputAcc_navRight1(CuTest *tc)
{
    /*
     * This command file has ASCII characters interspersed among five <right>
     * commands. The file ends with the program termination byte. Thus,
     * point_pos should have the value 5 and first_row should retain its initial
     * value.
     */

    INPUT_TEST_SETUP("test/input-navRight1", "test/lorem-ipsum.txt");

    CuAssertSizetEquals(tc, 5, buffer_ctx.point_pos);
    CuAssertSizetEquals(tc, 0x0, buffer_ctx.first_row);

    INPUT_TEST_TEARDOWN;

    return;
}

CuSuite *input_GetSuite(void)
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestInputAcc_simple);
    SUITE_ADD_TEST(suite, TestInputAcc_navRight1);
    return suite;
}
