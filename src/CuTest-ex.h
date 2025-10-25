#ifndef __CUTEST_EX_H__
#define __CUTEST_EX_H__

#include <stdint.h>

#include "cutest/CuTest.h"

#define CuAssertSizetEquals(tc,ex,ac) \
    CuAssertSizetEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define CuAssertSizetEquals_Msg(tc,ms,ex,ac) \
    CuAssertSizetEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertUint8tEquals(tc,ex,ac) \
    CuAssertSizetEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define CuAssertUint8tEquals_Msg(tc,ms,ex,ac) \
    CuAssertSizetEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))

void CuAssertSizetEquals_LineMsg(CuTest* tc, const char* file, int line,
                                 const char* message, size_t expected,
                                 size_t actual);

void CuAssertUint8tEquals_LineMsg(CuTest* tc, const char* file, int line,
                                 const char* message, uint8_t expected,
                                 uint8_t actual);

#endif /* __CUTEST_EX_H__ */
