#include "char.h"
#include "string.h"
#include "memory.h"
#include "debug.h"

/* Utility */
String
str_alloc_n(n64 max)
{
	String result = {0};
	result.len = 0;
	result.max = max;

	/* NOTE: Our stream are null terminated for C standard compability */
	result.data = mem_alloc(max+1, FALSE);
	result.data[result.max] = '\0';
	return(result);
}

String
str_alloc(CString cstr)
{
	String result = {0};
	n64 len = cstr_len(cstr);
	result = str_alloc_n(len);
	result.len = len;
	mem_cpy(result.data, cstr, result.len);
	return(result);
}

void
str_free(String *str)
{
	str->len = 0;
	str->max = 0;
	if(str->max != 0 && str->data != NULL) mem_free(str->data);
	str->data = NULL;
}

String
str_dup(String *str)
{
	/* To use whenever you want to store a string permanently */
	String result = {0};

	result.len = str->len;
	if(str->max != 0) result.max = str->max;
	else result.max = str->len;

	result.data = mem_alloc(result.max+1, FALSE);
	mem_cpy(result.data, str->data, result.max);
	result.data[result.max] = '\0';

	return(result);
}

String
str_sub(String *str, char *start, char *end)
{
	/* TODO: Why do we pass str to this function? */

	DBG_ASSERT(start <= end);
	//if(start == end) return(STR_NULL);

	String result = {0};
	n32 offset = (start - str->data);
	result.len = end - start;
	//result.max = str->max - offset; /* TODO: Should this be zero */
	result.max = 0; /* TODO: Should this be zero */
	result.data = str->data + offset;
	return(result);
}

void
str_cat(String *dst, String *a, String *b)
{
	/* SPEED TODO: It is slow to copy a into dst every time */

	n32 combined_len = a->len + b->len;
	if(combined_len > dst->max)
	{
		str_free(dst);
		*dst = str_alloc_n(combined_len);
	}

	if(dst != a) mem_cpy(dst->data, a->data, a->len);
	mem_cpy(dst->data+a->len, b->data, b->len);
	dst->len = combined_len;
	dst->data[dst->len] = '\0';
}

/* Find and Skip */
String
str_find_from(String *str, String *needle, char *from)
{
	Char *s = from;
	Char *n = needle->data;

	n32 i = 0;
	String result = STR_NULL;
	n32 chars_matched_count = 0;
	while(TRUE)
	{
		if(s[i] == '\0') return(STR_NULL);

		if(s[i] == n[chars_matched_count])
		{
			if(chars_matched_count == 0) result.data = &s[i];
			chars_matched_count += 1;
		}
		else if(chars_matched_count > 0) chars_matched_count = 0;
		i += 1;

		if(chars_matched_count == needle->len)
		{
			result.len = (str->len - i) + needle->len;
			result.max = 0;
			return(result);
		}
	}
}

String
str_find(String *str, String *needle)
{
	return(str_find_from(str, needle, str->data));
}

Bool
str_eql_n(String *a, String *b, n32 n)
{
	for(n32 i = 0; i < n; ++i)
	{
		if(a->data[i] != b->data[i]) return(FALSE);
	}

	return(TRUE);
}

Bool
str_eql(String *a, String *b)
{
	Bool result = FALSE;
	if(a->len != b->len) return(result);

	result = str_eql_n(a, b, a->len);
	return(result);
}

String
str_skip_whitespace(String *str)
{
	String result = {0};

	n32 whitespace_count = 0;
	while(char_is_whitespace(str->data[whitespace_count])) ++whitespace_count;
	result = str_sub(str, str->data + whitespace_count, str->data + str->len);
	return(result);
}

String
str_find_whitespace(String *str)
{
	String result = {0};

	n32 i = 0;
	while(TRUE)
	{
		if(str->len - i == 0) break;
		if(char_is_whitespace(str->data[i]))
		{
			result = str_sub(str, str->data + i, str->data + str->len);
			break;
		}

		i += 1;
	}
	return(result);
}

String
str_find_and_skip_whitespace(String *str)
{
	String result = {0};

	result = str_find_whitespace(str);
	result = str_skip_whitespace(&result);

	return(result);
}

/* Path */
String
str_path_extension(String *str)
{
	String result = {0};

	char *end = str->data + str->len;
	char *start = end - 1;

	if(*start == '/') return(result);
	/* This is a directory */

	while(TRUE)
	{
		if(start == str->data) return(STR_NULL); /* No extension */
		if(*start == '.')
		{
			start += 1;
			break;
		}
		start -= 1;
	}

	result = str_sub(str, start, end);

	return(result);
}

String
str_path_filename(String *str)
{

	String result = {0};

	char *end = str->data + str->len - 1;
	char *start = end - 1;

	if(*start == '/') return(result);
	/* This is a directory */

	while(*start != '/') --start;
	++start;

	result = str_sub(str, start, end+1);

	return(result);
}
