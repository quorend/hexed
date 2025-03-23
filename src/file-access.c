#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "file-access.h"
#include "buffer.h"

int file_access_loadFile(char *path)
{
    FILE *fp;
    struct stat statbuf;
    int file_desc;

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

    /* Allocate memory for buffer */
    buffer_ctx.buf = malloc(statbuf.st_size);
    if (buffer_ctx.buf == NULL)
    {
        fclose(fp);
        return 1;
    }

    buffer_ctx.buf_len = statbuf.st_size;

    /* Load file contents into buffer */
    fread(buffer_ctx.buf, sizeof(uint8_t), statbuf.st_size, fp);

    fclose(fp);

    return 0;
}
