#include <stdio.h>

#include "cutest/CuTest.h"

static void RunAllTests(void);

CuSuite *file_access_GetSuite();

int main(void)
{
    RunAllTests();

    return 0;
}

static void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite * suite = CuSuiteNew();

    CuSuiteAddSuite(suite, file_access_GetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\r\n", output->buffer);

    return;
}
