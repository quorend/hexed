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

#include "buffer.h"
#include "cutest/CuTest.h"

void buffer_init(struct Buffer_Ctx *buffer_ctx)
{
    buffer_ctx->buf = NULL;
    buffer_ctx->first_row = 0;
    buffer_ctx->point_pos = 0;

    return;
}

uint64_t buffer_getPosition(struct Buffer_Ctx *buffer_ctx)
{
    return buffer_ctx->point_pos;
}

static void TestBufInit(CuTest *tc)
{
    struct Buffer_Ctx buffer_ctx;

    buffer_init(&buffer_ctx);

    CuAssertPtrEquals(tc, NULL, buffer_ctx.buf);
    CuAssertULongEquals(tc, 0, buffer_ctx.first_row);
    CuAssertULongEquals(tc, 0, buffer_ctx.point_pos);

    return;
}

CuSuite *buffer_GetSuite(void)
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestBufInit);
    return suite;
}
