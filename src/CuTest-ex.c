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

#include "CuTest-ex.h"

void CuAssertSizetEquals_LineMsg(CuTest* tc, const char* file, int line,
                                 const char* message, size_t expected,
                                 size_t actual)
{
    char buf[STRING_MAX];
    if (expected == actual) return;
    sprintf(buf, "expected <%zu> but was <%zu>", expected, actual);
    CuFail_Line(tc, file, line, message, buf);
}

void CuAssertUint8tEquals_LineMsg(CuTest* tc, const char* file, int line,
                                 const char* message, uint8_t expected,
                                 uint8_t actual)
{
    char buf[STRING_MAX];
    if (expected == actual) return;
    sprintf(buf, "expected <%hhu> but was <%hhu>", expected, actual);
    CuFail_Line(tc, file, line, message, buf);
}
