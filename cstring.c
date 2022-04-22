#include "./cstring.h"
#include "./scalar/boolean.h"
#include "./scalar/natural.h"
#include "./scalar/integer.h"

n64
cstr_len(CString cstr)
{
	if(cstr == CSTR_NULL) return(0);

	n32 length = 0;

	CString c = cstr;
	while(*c++ != '\0')
	{
		++length;
	}

	return(length);
}

Bool
cstr_eql_n(CString a, CString b, n64 len)
{
	if(a == CSTR_NULL || b == CSTR_NULL) return(FALSE);

	for(n32 i = 0; i < len; ++i)
	{
		if((a[i] == 0) || (a[i] != b[i]))
		{
			return(FALSE);
		}
	}
	return(TRUE);
}

Bool
cstr_eql(CString a, CString b)
{
	Bool result = TRUE;

	n32 a_len = cstr_len(a);
	n32 b_len = cstr_len(b);

	if(a_len != b_len) return(FALSE);

	for(n32 i = 0; i < a_len; ++i)
	{
		if(*a++ != *b++)
		{
			result = FALSE;
			break;
		}
	}

	return(result);
}

/* */
i32
cstr_cpy_n(CString dst, CString src, n32 n)
{
	CString d = dst;
	CString s = src;

	for(n32 i = 0; i < n; ++i)
	{
		*d++ = *s++;
	}

	return(1);
}

i32
cstr_cpy(CString dst, CString src)
{
	/* TODO(neet): Error checking */
	#if 0
	if(sizeof(dst) < sizeof(src))
	{
		return(-1);
	}
	#endif

	CString d = dst;
	CString s = src;

	while(*s != '\0' || *d != '\0')
	{
		*d++ = *s++;
	}

	return(1);
}

i32
cstr_cat(CString dst, CString a, CString b)
{
	n64 len_a = cstr_len(a);
	n64 len_b = cstr_len(b);

	/* TODO(neet): Error checking */
	#if 0
	printf("D: %d, A: %d, B: %d\n", sizeof(dst), sizeof(a), sizeof(b));
	if(sizeof(dst) < (sizeof(a) + sizeof(b)))
	{
		return(-1);
	}
	#endif

	cstr_cpy(dst, a);
	cstr_cpy(dst + len_a, b);
	dst[len_a + len_b] = '\0';

	return(1);
}

/* Path */
void
cstr_path_parent(CString dst, CString src)
{
	cstr_cpy(dst, src);

	CString c = dst + cstr_len(dst) - 1;
	while(*--c != '/');
	*++c = '\0';
}
