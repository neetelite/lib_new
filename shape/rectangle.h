#ifndef _shape_rec_
#define _shape_rec_

#include "../vector.h"

struct Rec2
{
	union
	{
		struct
		{
			Vec2 start;
			Vec2 end;
		};
		Vec4 vec;
	};
};

struct Rec3
{
	Vec3 start;
	Vec3 end;
};

/* Functions */
struct Rec2 REC2(Vec2 start, Vec2 end);
struct Rec3 REC3(Vec3 start, Vec3 end);

#endif /* _shape_rec_ */
