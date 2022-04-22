#include "./box.h"

inline struct Box2
BOX2(Vec2 pos, Vec2 dim, r32 rot)
{
	struct Box2 result = {0};
	result.pos = pos;
	result.dim = dim;
	result.rot = rot;
	result.scl = VEC2_ONE;
	return(result);
}

inline struct Box3
BOX3(Vec3 pos, Vec3 dim, Vec3 rot)
{
	struct Box3 result = {0};
	result.pos = pos;
	result.dim = dim;
	result.rot = rot;
	result.scl = VEC3_ONE;
	return(result);
}
