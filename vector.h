#ifndef _multidimensional_
#define _multidimensional_

#include "./scalar/natural.h"
#include "./scalar/integer.h"
#include "./scalar/real.h"

#pragma pack(push, 1)
#pragma pack(1)
/* 2D - Structures */
typedef union Real2
{
	struct
	{
		r32 x, y;
	};
	struct
	{
		r32 u, v;
	};
	struct
	{
		r32 width, height;
	};
	struct
	{
		r32 min, max;
	};
	struct
	{
		r32 start, end;
	};
	r32 i[2];
} Pnt2, Vec2, Point2, Vector2;

/* 3D - Structures */
typedef union Real3
{
	struct
	{
		r32 x, y, z;
	};
	struct
	{
		r32 u, v, n;
	};
	struct
	{
		r32 r, g, b;
	};
	struct
	{
		/* TODO: Is this right? */
		r32 width, length, height;
	};
	struct
	{
		Vec2 xy;
		r32 ignored_0;
	};
	struct
	{
		r32 ignored_1;
		Vec2 yz;
	};
	struct
	{
		Vec2 uv;
		r32 ignored_2;
	};
	struct
	{
		r32 ignored_3;
		Vec2 vn;
	};
	r32 i[3];
} Pnt3, Vec3, Point3, Vector3;

/* 4D - Structures */
typedef union Vector4
{
	struct
	{
		union
		{
			Vec3 xyz;
			struct
			{
				r32 x, y, z;
			};
		};

		r32 w;
	};
	struct
	{
		union
		{
			Vec3 rgb;
			struct
			{
				r32 r, g, b;
			};
		};

		r32 a;
	};
	struct
	{
		Vec2 xy;
		r32 Ignored0_;
		r32 Ignored1_;
	};
	struct
	{
		r32 Ignored2_;
		Vec2 yz;
		r32 Ignored3_;
	};
	struct
	{
		r32 Ignored4_;
		r32 Ignored5_;
		Vec2 zw;
	};
	struct
	{
		Vec2 min;
		Vec2 max;
	};
	struct
	{
		Vec2 start;
		Vec2 end;
	};
	r32 i[4];
} Pnt4, Vec4, Point4, Vector4;
#pragma pack(pop)

/* Constructors */
#define VEC2(a, b)        (Vec2){a, b}
#define VEC3(a, b, c)     (Vec3){a, b, c}
#define VEC4(a, b, c, d)  (Vec4){a, b, c, d}

/* Basic Initializers */
#define VEC2_ZERO VEC2(0, 0)
#define VEC2_ONE VEC2(1, 1)
#define VEC2_NULL VEC2(-1, -1)

#define VEC3_ZERO VEC3(0, 0, 0)
#define VEC3_ONE VEC3(1, 1, 1)
#define VEC3_NULL VEC3(-1, -1, -1)

#define VEC4_ZERO VEC4(0, 0, 0, 1)
#define VEC4_ONE VEC4(1, 1, 1, 1)
#define VEC4_NULL VEC4(-1, -1, -1, -1)

/* Direcational Initializers */
#define VEC2_DIR_RIGHT VEC2(1, 0)
#define VEC2_DIR_LEFT VEC2(-1, 0)
#define VEC2_DIR_UP VEC2(0, 1)
#define VEC2_DIR_DOWN VEC2(0, -1)

#define VEC3_DIR_RIGHT VEC3(1, 0, 0)
#define VEC3_DIR_LEFT VEC3(-1, 0, 0)
#define VEC3_DIR_UP VEC3(0, 0, 1)
#define VEC3_DIR_DOWN VEC3(0, 0, -1)
#define VEC3_DIR_FRONT VEC3(0, 1, 0)
#define VEC3_DIR_BACK VEC3(0, -1, 0)

#define VEC4_DIR_RIGHT VEC4(1, 0, 0, 1)
#define VEC4_DIR_LEFT VEC4(-1, 0, 0, 1)
#define VEC4_DIR_UP VEC4(0, 0, 1, 1)
#define VEC4_DIR_DOWN VEC4(0, 0, -1, 1)
#define VEC4_DIR_FRONT VEC4(0, 1, 0, 1)
#define VEC4_DIR_BACK VEC4(0, -1, 0, 1)

/* Color Initializers */
#define VEC3_COLOR_WHITE   VEC3(1, 1, 1)
#define VEC3_COLOR_RED	 VEC3(1, 0, 0)
#define VEC3_COLOR_YELLOW  VEC3(1, 1, 0)
#define VEC3_COLOR_GREEN   VEC3(0, 1, 0)
#define VEC3_COLOR_CYAN	VEC3(0, 1, 1)
#define VEC3_COLOR_BLUE	VEC3(0, 0, 1)
#define VEC3_COLOR_MAGENTA VEC3(1, 0, 1)
#define VEC3_COLOR_BLACK   VEC3(0, 0, 0)

#define VEC4_COLOR_WHITE   VEC4(1, 1, 1, 1)
#define VEC4_COLOR_RED	 VEC4(1, 0, 0, 1)
#define VEC4_COLOR_YELLOW  VEC4(1, 1, 0, 1)
#define VEC4_COLOR_GREEN   VEC4(0, 1, 0, 1)
#define VEC4_COLOR_CYAN	 VEC4(0, 1, 1, 1)
#define VEC4_COLOR_BLUE	 VEC4(0, 0, 1, 1)
#define VEC4_COLOR_MAGENTA VEC4(1, 0, 1, 1)
#define VEC4_COLOR_BLACK   VEC4(0, 0, 0, 1)

/* Light Initializers */
#define VEC3_LUMA VEC3(0.299, 0.587, 0.114)
#define VEC4_LUMA VEC4(0.299, 0.587, 0.114, 1)

typedef union Vector2i
{
	struct
	{
		i32 x, y;
	};
	struct
	{
		i32 u, v;
	};
	struct
	{
		i32 width, height;
	};
	i32 i[2];
} Pnt2i, Vec2i;

/* Functions */
Vec2 vec2_a(Vec2 a, Vec2 b);
Vec2 vec2_s(Vec2 a, Vec2 b);
Vec2 vec2_m(Vec2 a, Vec2 b);
Vec2 vec2_d(Vec2 a, Vec2 b);

Vec2 vec2_ar(Vec2 a, r32 b);
Vec2 vec2_sr(Vec2 a, r32 b);
Vec2 vec2_mr(Vec2 a, r32 b);
Vec2 vec2_dr(Vec2 a, r32 b);

Vec3 vec3_ar(Vec3 a, r32 b);
Vec3 vec3_sr(Vec3 a, r32 b);
Vec3 vec3_mr(Vec3 a, r32 b);
Vec3 vec3_dr(Vec3 a, r32 b);

Vec3 VEC3_VEC2_XY(Vec2 a, r32 b);
r32 vec3_min(Vec3 a);
r32 vec3_max(Vec3 a);
r32 vec3_sum(Vec3 a);

r32 vec3_len(Vec3 a);
r32 vec3_len_sq(Vec3 a);
Vec3 vec3_norm(Vec3 a);
r32 vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);


Vec4 vec4_from_n32(n32 a);
Vec4 vec4_a(Vec4 a, Vec4 b);
Vec4 vec4_s(Vec4 a, Vec4 b);
Vec4 vec4_ar(Vec4 a, r32 b);
Vec4 vec4_mr(Vec4 a, r32 b);
Vec4 vec4_dr(Vec4 a, r32 b);
Vec4 vec4_abs(Vec4 a);
r32 vec4_sum(Vec4 a);
Vec4 vec4_sym(Vec4 a);


#endif /* _multidimensional_ */
