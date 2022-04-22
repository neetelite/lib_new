#ifndef _string_h
#define _string_h

#include "./scalar/natural.h"
#include "./cstring.h"

typedef struct String
{
	/* NOTE: u16 was too little, I changed it to max,
	our stream allocation system is efficient anyway */
	union
	{
		n64 count;
		n64 size;
		n64 length;
		n64 len;
	};
	n64 max;
	char *data;
} String;

#define STR_NULL (String){0, 0, NULL}
#define STR(cstr) (String){cstr_len(cstr), (0), (char *)(cstr)}

/* Functions */
String str_alloc(CString cstr);
String str_alloc_n(n64 max);
void str_free(String *str);

String str_dup(String *str);
String str_sub(String *str, char *start, char *end);
void str_cat(String *dst, String *a, String *b);

String str_find(String *str, String *needle);
String str_find_from(String *str, String *needle, char *from);
String str_find_and_skip_whitespace(String *str);

Bool str_eql_n(String *a, String *b, n32 n);
Bool str_eql(String *a, String *b);

String str_path_extension(String *str);
String str_path_filename(String *str);

#endif /* _string_h */
