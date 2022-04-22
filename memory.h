#ifndef _memory_h
#define _memory_h

#include "./scalar/boolean.h"
#include "./scalar/natural.h"

typedef n8 b8;
typedef n16 b16;
typedef n32 b32;
typedef n64 b64;

void *_mem_alloc(n64 size, Bool clear);
void *_mem_realloc(void *pointer, n64 size);
#define mem_alloc(size, clear) _mem_alloc((size), (clear))
#define mem_alloc_stack(size) alloca(size);
#define mem_realloc(pointer, size) _mem_realloc((pointer), (size))

void *mem_set(void *pointer, n8 c, n64 count);
void *mem_cpy(void *destination, void *source, n64 count);
void *mem_move(void *destination, void *source, n64 count);
void mem_free(void *pointer);

#endif /* _memory_h */
