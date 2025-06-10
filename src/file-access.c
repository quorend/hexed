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
#include <sys/stat.h>
#include <stdlib.h>

#include "file-access.h"
#include "cutest/CuTest.h"

int file_access_loadFile(struct Buffer_Ctx *buffer_ctx, const char *path)
{
    FILE *fp;
    struct stat statbuf;
    size_t bytes_read = 0;

    /* Open file */
    fp = fopen(path, "r");
    if (!fp)
    {
        return 1;
    }

    /* Get file stats (filesize) */
    stat(path, &statbuf);
    buffer_ctx->buf_len = (size_t)statbuf.st_size;

    /* Allocate memory for buffer */
    buffer_ctx->buf = malloc(buffer_ctx->buf_len);
    if (buffer_ctx->buf == NULL)
    {
        fclose(fp);
        return 1;
    }

    /* Load file contents into buffer */
    bytes_read = fread(buffer_ctx->buf, sizeof(uint8_t), buffer_ctx->buf_len, fp);
    if (bytes_read != buffer_ctx->buf_len)
    {
        fclose(fp);
        return 1;
    }

    fclose(fp);

    return 0;
}

static void TestBufLen(CuTest *tc)
{
    struct stat st;
    const char path[] = "src/main.c";
    struct Buffer_Ctx buffer_ctx;

    buffer_init(&buffer_ctx);

    if (file_access_loadFile(&buffer_ctx, path))
    {
        CuFail(tc, "Failed to load file");
        return;
    }

    stat(path, &st);

    CuAssertULongEquals(tc, (size_t)st.st_size, buffer_ctx.buf_len);

    return;
}

CuSuite *file_access_GetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestBufLen);
    return suite;
}
