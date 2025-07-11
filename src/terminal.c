/*******************************************************************************
 * This file is adapted from the example found at the following page:
 * https://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html
 ******************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "terminal.h"

/* Use this variable to remember original terminal attributes. */
struct termios saved_attributes;

static void reset_input_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);

    return;
}

void set_input_mode(void)
{
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty(STDIN_FILENO))
    {
        fprintf(stderr, "ERR: Not a terminal.\n");
        exit(EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr(STDIN_FILENO, &saved_attributes);
    atexit(reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= (unsigned)~(ICANON|ECHO); /* Clear ICANON and ECHO. */

    /*
     * read() blocks until MIN bytes are available, and returns up to the number
     * of bytes requested.
     */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);

    return;
}
