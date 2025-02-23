#include <stdio.h>
#include <string.h>

#define VERSION "1.0.0"

static void print_version(char *name);
static void print_help(void);

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
                        print_help();
                    }
                }
                else
                {
                    /* Short option */
                }
            }
            else
            {
                /* Filename */
            }
        }
    }
    else
    {
        printf("Lots of work to do...\r\n");
    }

    return 0;
}

static void print_version(char *name)
{
    printf("%s\r\nversion %s\r\n", name, VERSION);

    return;
}

static void print_help(void)
{
    printf("*Help text*\r\n");

    return;
}
