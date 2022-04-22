#include "./scalar/boolean.h"
#include "./scalar/natural.h"
#include "./scalar/integer.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>

void *
_mem_alloc(n64 size, Bool clear)
{
	void *result = NULL;

	if(clear) result = calloc(1, size);
	else result = malloc(size);

	//++global_alloc_count;

	return(result);
}

void *
_mem_realloc(void *pointer, n64 size)
{
	void *result = NULL;

	if(!pointer)
	{
		//++global_alloc_count;
	}

	result = realloc(pointer, size);
	return(result);
}

#define mem_push(size) alloca(size)
/* NOTE: You can't put this in a function, stack is destroyed after */

void *
mem_set(void *pointer, n8 c, n64 count)
{
	void *result = NULL;
	result = memset(pointer, c, count);
	return(result);
}

i32
mem_cmp(void *a, void *b, n64 size)
{
	i32 result = 0;
	result = memcmp(a, b, size);
	return(result);
}

void *
mem_cpy(void *destination, void *source, n64 size)
{
	void *result = NULL;
	memcpy(destination, source, size);
	return(result);
}

void *
mem_move(void *destination, void *source, n64 count)
{
	void *result = NULL;
	result = memmove(destination, source, count);
	return(result);
}

void
mem_free(void *pointer)
{
	if(!pointer) return;

	#if BUILD_DEBUG
	++global_free_count;
	#endif/* BULD_DEBUG */
	free(pointer);
}

#if 0
void
mem_print(void)
{
	#if BUILD_DEBUG
	printf("\n");
	printf("ALLOC: %u\t", global_alloc_count);
	printf("FREE: %u\t", global_free_count);
	printf("LEAKED: %u\t", global_alloc_count - global_free_count);
	printf("\n");
	#endif
}
#endif
