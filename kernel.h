#ifndef _kernel_h
#define _kernel_h

#include "./scalar/boolean.h"
#include "./scalar/integer.h"
#include "./scalar/real.h"
#include "./memory.h"

enum Kernel_Type
{
	KERNEL_IMPULSE,
	KERNEL_SHIFT,
	KERNEL_BOX,
	KERNEL_FUZZY,
};

struct Kernel
{
	enum Kernel_Type type;
	Bool is_symetric;

	i32 width;
	i32 height;
	i32 size;
	r32 *data;
};

struct Kernel kernel_box_gen(i32 size_side);
struct Kernel kernel_gen(enum Kernel_Type type, n32 size);

#endif /* _kernel_h */
