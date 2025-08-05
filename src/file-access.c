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
#include <string.h>

#include "file-access.h"
#include "cutest/CuTest.h"

static int save_backup(struct Buffer_Ctx *buffer_ctx);
static int save_buffer(struct Buffer_Ctx *buffer_ctx);

int file_access_loadFile(struct Buffer_Ctx *buffer_ctx, const char *path)
{
    FILE *fp;
    int rc = 0;
    struct stat statbuf;
    size_t bytes_read = 0;

    /* Save file path */
    buffer_ctx->path = path;

    /* Open file */
    fp = fopen(path, "r");
    if (!fp)
    {
        rc = 1;
        goto __exit__;
    }

    /* Get file stats (filesize) */
    stat(path, &statbuf);
    buffer_ctx->buf_len = (size_t)statbuf.st_size;

    /* Allocate memory for buffer */
    buffer_ctx->buf = malloc(buffer_ctx->buf_len);
    if (buffer_ctx->buf == NULL)
    {
        rc = 2;
        goto __fclose__;
    }

    /* Load file contents into buffer */
    bytes_read = fread(buffer_ctx->buf, sizeof(uint8_t), buffer_ctx->buf_len, fp);
    if (bytes_read != buffer_ctx->buf_len)
    {
        free(buffer_ctx->buf);
        rc = 3;
        goto __fclose__;
    }

__fclose__:
    fclose(fp);
__exit__:
    return rc;
}

int file_access_saveFile(struct Buffer_Ctx *buffer_ctx)
{
    int rc = 0;

    /* Copy file to file~ */
    rc = save_backup(buffer_ctx);
    if (rc != 0)
    {
        goto __exit__;
    }

    /* Write buffer to file */
    rc = save_buffer(buffer_ctx);

__exit__:
    return rc;
}

/**
 * @brief Back-up original file.
 * @param[in] buffer_ctx context containing buffer
 * @return 0 on success, otherwise non-zero
 */
static int save_backup(struct Buffer_Ctx *buffer_ctx)
{
    FILE *fp;
    FILE *fp_bak;
    struct stat statbuf;
    size_t buf_sz;
    int rc = 0;
    uint8_t byte_bak;
    char *path_bak;

    /* Allocate enough space for the path, plus '~' , plus '\0' */
    path_bak = malloc(strlen(buffer_ctx->path) + 2);
    if (path_bak == NULL)
    {
        rc = -1;
        goto __exit__;
    }

    path_bak[0] = '\0';
    strcat(path_bak, buffer_ctx->path);
    strcat(path_bak, "~");

    fp = fopen(buffer_ctx->path, "r");
    if (fp == NULL)
    {
        rc = -2;
        goto __malloc__;
    }

    fp_bak = fopen(path_bak, "w");
    if (fp_bak == NULL)
    {
        rc = -3;
        goto __fopen_1__;
    }

    stat(buffer_ctx->path, &statbuf);
    buf_sz = (size_t)statbuf.st_size;

    for (size_t i = 0; i < buf_sz; i++)
    {
        size_t rv;

        rv = fread(&byte_bak, 1, 1, fp);
        if (rv != 1)
        {
            rc = -4;
            goto __fopen_2__;
        }

        rv = fwrite(&byte_bak, 1, 1, fp_bak);
        if (rv != 1)
        {
            rc = -5;
            goto __fopen_2__;
        }
    }

__fopen_2__:
    fclose(fp_bak);
__fopen_1__:
    fclose(fp);
__malloc__:
    free(path_bak);
__exit__:
    return rc;
}

/**
 * @brief Write buffer out to file.
 * @param[in] buffer_ctx context containing buffer
 * @return 0 on success, otherwise non-zero
 */
static int save_buffer(struct Buffer_Ctx *buffer_ctx)
{
    FILE *fp;
    size_t bytes_written;
    int rc = 0;

    fp = fopen(buffer_ctx->path, "w");
    if (fp == NULL)
    {
        rc = -6;
        goto __exit__;
    }

    bytes_written = fwrite(buffer_ctx->buf, 1, buffer_ctx->buf_len, fp);
    if (bytes_written != buffer_ctx->buf_len)
    {
        rc = -7;
        goto __fclose__;
    }

__fclose__:
    fclose(fp);
__exit__:
    return rc;
}

/*
 * Unit Tests
 */

static void TestBufLen(CuTest *tc)
{
    struct stat st;
    const char path[] = "src/main.c";
    struct Buffer_Ctx buffer_ctx;

    buffer_init(&buffer_ctx);

    if (file_access_loadFile(&buffer_ctx, path) != 0)
    {
        CuFail(tc, "Failed to load file");
        return;
    }

    stat(path, &st);

    CuAssertSizetEquals(tc, (size_t)st.st_size, buffer_ctx.buf_len);

    return;
}

CuSuite *file_access_GetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestBufLen);
    return suite;
}
