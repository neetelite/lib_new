#ifndef _char_h
#define _char_h

#include "./scalar/boolean.h"

/* Typedefs */
typedef unsigned char Char;

/* Functions */
Bool char_is_whitespace(Char c);
Bool char_is_eol(Char c);
Bool char_is_digit(Char c);
Bool char_is_alpha(Char c);
Bool char_is_ident(Char c);
Bool char_is_alnum(Char c);

#endif /* _char_h */
