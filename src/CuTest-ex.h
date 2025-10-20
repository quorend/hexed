#ifndef __CUTEST_EX_H__
#define __CUTEST_EX_H__

#include "cutest/CuTest.h"

#define CuAssertSizetEquals(tc,ex,ac) \
    CuAssertSizetEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define CuAssertSizetEquals_Msg(tc,ms,ex,ac) \
    CuAssertSizetEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))


void CuAssertSizetEquals_LineMsg(CuTest* tc, const char* file, int line,
                                 const char* message, size_t expected,
                                 size_t actual);

#endif /* __CUTEST_EX_H__ */
