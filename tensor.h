#ifndef _tensor_h
#define _tensor_h

struct Tensfor
{
	n32 rows;
	n32 cols;
	n32 count;
	n32 rank;

	void *data;
};

#endif /* _tensor_h */
