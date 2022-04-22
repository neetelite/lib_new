#ifndef _array_h
#define _array_h

#include "./scalar/natural.h"
#include "./scalar/integer.h"

#define ARR_S * /* Manually allocated and kept track of */
#define ARR_D * /* Uses the library to take care of everything */

#define ARRAY_COUNT(array) (sizeof(array) / sizeof(array[0]))

/* Typedefs */
typedef i64 PtrDiff;

/* Structs */
struct Array_Header
{
	n64 len;
	n64 max;
	void *data;
	PtrDiff tmp;
};

/* Macros */
#define array_header(t) ((struct Array_Header *)(t) - 1)
#define array_tmp(t) array_header(t)->tmp;
#define array_tmp_key(t) (*(char **)array_header(t)->data)

#define array_max_set(a,n)    (array_grow(a,0,n))
#define array_len_set(a,n)    ((array_max(a) < (n64) (n) ? array_max_set((a),(n64)(n)),0 : 0), (a) ? array_header(a)->len = (n64) (n) : 0)
#define array_max(a)          ((a) ? array_header(a)->max : 0)
#define array_len(a)          ((a) ? (PtrDiff) array_header(a)->len : 0)
#define array_len_u(a)        ((a) ?             array_header(a)->len : 0)
#define array_push(a,v)       (array_maybe_grow(a,1), (a)[array_header(a)->len++] = (v))
#define array_pop(a)          (array_header(a)->len--, (a)[array_header(a)->len])

#define array_addn(a,n)       ((void)(array_addnoff(a, n)))    // deprecated, use one of the following instead:
#define array_addnptr(a,n)    (array_maybe_grow(a,n), array_header(a)->len += (n), &(a)[array_header(a)->len-(n)])
#define array_addnoff(a,n)    (array_maybe_grow(a,n), array_header(a)->len += (n), array_header(a)->len-(n))

#define array_first(a)        ((a)[0])
#define array_last(a)         ((a)[array_header(a)->len-1])

#define array_alloc(a, n)     (array_grow(a,0,n))
#define array_free(a)         ((void) ((a) ? mem_free(array_header(a)) : (void)0), (a)=NULL)

#define array_del_swap(a,i)   ((a)[i] = array_last(a), array_header(a)->len -= 1)
#define array_del_n(a,i,n)    (memmove(&(a)[i], &(a)[(i)+(n)], sizeof *(a) * (array_header(a)->len-(n)-(i))), array_header(a)->len -= (n))
#define array_del(a,i)        array_deln(a,i,1)

#define array_ins_n(a,i,n)    (array_addn((a),(n)), memmove(&(a)[(i)+(n)], &(a)[i], sizeof *(a) * (array_header(a)->len-(n)-(i))))
#define array_ins(a,i,v)      (array_insn((a),(i),1), (a)[i]=(v))

#define array_maybe_grow(a,n) ((!(a) || array_header(a)->len + (n) > array_header(a)->max) ? (array_grow(a,n,0),0) : 0)
#define array_grow(a,b,c)     ((a) = _array_grow((a), sizeof *(a), (b), (c)))

/* Functions */
void *_array_grow(void *a, n64 item_size, n64 add_len, n64 new_max);

#endif /* _array_h */
