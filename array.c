#include "array.h"
#include "memory.h"
#include "./scalar/natural.h"

#include <stdio.h>

void *
_array_grow(void *a, n64 item_size, n64 add_len, n64 new_max)
{
	n64 new_len = array_len(a) + add_len;

	/* Compute the minimum capacity needed */
	if(new_len > new_max) new_max = new_len;
	if(new_max <= array_max(a)) return(a);

	/* Increase needed capacity to guarantee O(1) amortized */
	if(new_max < 2*array_max(a)) new_max = 2*array_max(a);
	else if(new_max < 4) new_max = 4;

	void *b = mem_realloc((a) ? array_header(a) : 0, item_size*new_max+sizeof(struct Array_Header));
	b = (char *)b + sizeof(struct Array_Header);

	if(a == NULL)
	{
		array_header(b)->len = 0;
		array_header(b)->data = 0;
	}
	else
	{
		/* TODO: Stats */
	}
	array_header(b)->max = new_max;

	return(b);
}
