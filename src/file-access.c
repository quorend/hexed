#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "file-access.h"
#include "cutest/CuTest.h"
#include "buffer.h"

int file_access_loadFile(const char *path)
{
    FILE *fp;
    struct stat statbuf;
    int file_desc;
    size_t bytes_read = 0;

    /* Open file */
    fp = fopen(path, "r");
    if (!fp)
    {
        return 1;
    }

    /* Get file descriptor */
    file_desc = fileno(fp);
    if (file_desc == -1)
    {
        fclose(fp);
        return 1;
    }

    /* Get file stats (filesize) */
    fstat(file_desc, &statbuf);
    buffer_ctx.buf_len = statbuf.st_size;

    /* Allocate memory for buffer */
    buffer_ctx.buf = malloc(buffer_ctx.buf_len);
    if (buffer_ctx.buf == NULL)
    {
        fclose(fp);
        return 1;
    }

    /* Load file contents into buffer */
    bytes_read = fread(buffer_ctx.buf, sizeof(uint8_t), buffer_ctx.buf_len, fp);
    if (bytes_read != buffer_ctx.buf_len)
    {
        fclose(fp);
        return 1;
    }

    fclose(fp);

    return 0;
}

void TestBufLen(CuTest *tc)
{
    struct stat st;
    const char path[] = "src/main.c";

    if (file_access_loadFile(path))
    {
        CuFail(tc, "Failed to load file");
        return;
    }

    stat(path, &st);

    CuAssertIntEquals(tc, st.st_size, buffer_ctx.buf_len);
}

CuSuite *file_access_GetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestBufLen);
    return suite;
}
