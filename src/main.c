#include <stdio.h>
#include <string.h>

#include "file-access.h"
#include "buffer.h"

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
                int rc = 0;

                /* Filename */
                buffer_init();

                rc = file_access_loadFile(argv[1]);
                if (rc)
                {
                    printf("ERR: file_access_loadFile()\r\n");
                    return 0;
                }
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
