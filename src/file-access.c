#include <stdio.h>

#include "file-access.h"
#include "buffer.h"

int file_access_loadFile(char *path)
{
    FILE *fp;

    fp = fopen(path, "r");
    if (!fp)
    {
        return 1;
    }

    fclose(fp);

    return 0;
}
