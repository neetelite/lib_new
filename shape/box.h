#ifndef _shape_box_h
#define _shape_box_h

#include "../scalar/real.h"
#include "../vector.h"

struct Box2
{
	Vec2 pos;
	Vec2 dim;
	r32 rot;
	Vec2 scl; /* Premultiplied */
};

struct Box3
{
	Vec3 pos;
	Vec3 dim;
	Vec3 rot;
	Vec3 scl; /* Premultiplied */
};

/* Functions */
struct Box2 BOX2(Vec2 pos, Vec2 dim, r32 rot);
struct Box3 BOX3(Vec3 pos, Vec3 dim, Vec3 rot);

#endif /* _shape_box_h */
