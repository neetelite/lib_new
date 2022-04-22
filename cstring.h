#ifndef __cstring_h
#define __cstring_h

#include "./cstring.h"
#include "./scalar/boolean.h"
#include "./scalar/natural.h"
#include "./scalar/integer.h"

/* Defines */
#define CSTR_NULL ((void *)0)

/* Typedefs */
typedef char* CString;

/* Functions */
i32 cstr_cpy_n(CString dst, CString src, n32 n);

n64 cstr_len(CString cstr);

Bool cstr_eql(CString a, CString b);
Bool cstr_eql_n(CString a, CString b, n64 len);
void cstr_path_parent(CString dst, CString src);
i32 cstr_cat(CString dst, CString a, CString b);


#endif /* __cstring_h */
