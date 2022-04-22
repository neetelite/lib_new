#include "./rectangle.h"

inline struct Rec2
REC2(Vec2 start, Vec2 end)
{
	struct Rec2 result = {};
	result.start = start;
	result.end = end;
	return(result);
}

inline struct Rec3
REC3(Vec3 start, Vec3 end)
{
	struct Rec3 result = {};
	result.start = start;
	result.end = end;
	return(result);
}
