#include "./scalar/boolean.h"
#include "./char.h"

Bool
char_is_whitespace(Char c)
{
	Bool result = FALSE;
	if(c == ' ' || c == '\t' || c == '\r' || c == '\n') result = TRUE;
	return(result);
}

Bool
char_is_eol(Char c)
{
	Bool result = FALSE;
	/* TODO: Maybe do this with pointers so you can text if the next character after '\r' is '\n' */
	if(c == '\n' || (c == '\r')) result = TRUE;
	return(result);
}

Bool
char_is_digit(Char c)
{
	Bool result = FALSE;
	result = (c >= '0' && c <= '9');
	return(result);
}

Bool
char_is_alpha(Char c)
{
	Bool result = FALSE;
	result = ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
	return(result);
}

Bool
char_is_ident(Char c)
{
	Bool result = FALSE;
	result = char_is_alpha(c) || c == '_';
	return(result);
}

Bool
char_is_alnum(Char c)
{
	Bool result = FALSE;
	result = char_is_digit(c) || char_is_alpha(c);
	return(result);
}
