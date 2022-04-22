#include "./kernel.h"

struct Kernel
kernel_box_gen(i32 size_side)
{
	struct Kernel result = {};

	result.type = KERNEL_FUZZY;
	result.is_symetric = TRUE;

	result.width = size_side;
	result.height = size_side;
	result.size = result.width * result.height;
	result.data = mem_alloc(result.size * sizeof(r32), FALSE);

	r32 x = 1.0/(result.size);
	for(i32 i = 0; i < result.size; ++i) result.data[i] = x;

	return(result);
}

struct Kernel
kernel_gen(enum Kernel_Type type, n32 size)
{
	struct Kernel result = {};
	switch(type)
	{
	case KERNEL_BOX: result = kernel_box_gen(size); break;
	}
	return(result);
}
