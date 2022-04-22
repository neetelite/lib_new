#include "vector.h"

/* 2 Dimensional */
inline Vec2
vec2_a(Vec2 a, Vec2 b)
{
	Vec2 result = VEC2_ZERO;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return(result);
}

inline Vec2
vec2_s(Vec2 a, Vec2 b)
{
	Vec2 result = VEC2_ZERO;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return(result);
}

inline Vec2
vec2_m(Vec2 a, Vec2 b)
{
	Vec2 result = VEC2_ZERO;
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	return(result);
}

inline Vec2
vec2_d(Vec2 a, Vec2 b)
{
	Vec2 result = VEC2_ZERO;
	result.x = a.x / b.x;
	result.y = a.y / b.y;
	return(result);
}

inline Vec2
vec2_ar(Vec2 a, r32 b)
{
	Vec2 result = VEC2_ZERO;
	result.x = a.x + b;
	result.y = a.y + b;
	return(result);
}

inline Vec2
vec2_sr(Vec2 a, r32 b)
{
	Vec2 result = VEC2_ZERO;
	result.x = a.x - b;
	result.y = a.y - b;
	return(result);
}

inline Vec2
vec2_mr(Vec2 a, r32 b)
{
	Vec2 result = VEC2_ZERO;
	result.x = a.x * b;
	result.y = a.y * b;
	return(result);
}

inline Vec2
vec2_dr(Vec2 a, r32 b)
{
	Vec2 result = VEC2_ZERO;
	result.x = a.x / b;
	result.y = a.y / b;
	return(result);
}

/* 3 Dimensional */
inline Vec3
VEC3_VEC2_XY(Vec2 a, r32 b)
{
	Vec3 result = VEC3_ZERO;
	result.xy = a;
	result.z = b;
	return(result);
}

inline Vec3
vec3_ar(Vec3 a, r32 b)
{
	Vec3 result = VEC3_ZERO;
	result.x = a.x + b;
	result.y = a.y + b;
	result.z = a.z + b;
	return(result);
}

inline Vec3
vec3_sr(Vec3 a, r32 b)
{
	Vec3 result = VEC3_ZERO;
	result.x = a.x - b;
	result.y = a.y - b;
	result.z = a.z - b;
	return(result);
}

inline Vec3
vec3_mr(Vec3 a, r32 b)
{
	Vec3 result = VEC3_ZERO;
	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return(result);
}

inline Vec3
vec3_dr(Vec3 a, r32 b)
{
	Vec3 result = VEC3_ZERO;
	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	return(result);
}

inline r32
vec3_min(Vec3 a)
{
	r32 result = a.x;
	for(i32 i = 0; i < 3; ++i) if(a.i[i] < result) result = a.i[i];
	return(result);
}

inline r32
vec3_max(Vec3 a)
{
	r32 result = a.x;
	for(i32 i = 0; i < 3; ++i) if(a.i[i] > result) result = a.i[i];
	return(result);
}

inline r32
vec3_sum(Vec3 a)
{
	r32 result = 0;
	result += a.x;
	result += a.y;
	result += a.z;
	return(result);
}

inline r32
vec3_len_sq(Vec3 a)
{
	r32 result = vec3_dot(a, a);
	return(result);
}

inline r32
vec3_len(Vec3 a)
{
	r32 result = r32_sqrt(vec3_len_sq(a));
	return(result);
}

inline Vec3
vec3_norm(Vec3 a)
{
	Vec3 result = vec3_dr(a, vec3_len(a));
	return(result);
}

inline r32
vec3_dot(Vec3 a, Vec3 b)
{
	r32 result = a.x*b.x + a.y+b.y * a.z*b.z;
	return(result);
}

inline Vec3
vec3_cross(Vec3 a, Vec3 b)
{
	Vec3 result = VEC3_ZERO;
	result.x = a.y*b.z + - a.z*b.y;
	result.y = a.z*b.x + - a.x*b.z;
	result.z = a.x*b.y + - a.y*b.x;
	return(result);
}

/* 4 Dimensional */
inline Vec4
vec4_from_n32(n32 a)
{
	Vec4 result = VEC4_ZERO;
	#if 0
	result.x = (r32)((a >> 24) & 0xFF);
	result.y = (r32)((a >> 16) & 0xFF);
	result.z = (r32)((a >>  8) & 0xFF);
	result.w = (r32)((a) & 0xFF);
	#else
	result.w = (r32)((a >> 24) & 0xFF);
	result.z = (r32)((a >> 16) & 0xFF);
	result.y = (r32)((a >>  8) & 0xFF);
	result.x = (r32)((a) & 0xFF);
	#endif
	return(result);
}

inline Vec4
vec4_a(Vec4 a, Vec4 b)
{
	Vec4 result = VEC4_ZERO;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return(result);
}

inline Vec4
vec4_s(Vec4 a, Vec4 b)
{
	Vec4 result = VEC4_ZERO;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return(result);
}

inline Vec4
vec4_ar(Vec4 a, r32 b)
{
	Vec4 result = VEC4_ZERO;
	result.x = a.x + b;
	result.y = a.y + b;
	result.z = a.z + b;
	result.w = a.w + b;
	return(result);
}

inline Vec4
vec4_mr(Vec4 a, r32 b)
{
	Vec4 result = VEC4_ZERO;
	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	result.w = a.w * b;
	return(result);
}

inline Vec4
vec4_dr(Vec4 a, r32 b)
{
	Vec4 result = VEC4_ZERO;
	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	result.w = a.w / b;
	return(result);
}

inline Vec4
vec4_abs(Vec4 a)
{
	Vec4 result = VEC4_ZERO;
	result.x = r32_abs(a.x);
	result.y = r32_abs(a.y);
	result.z = r32_abs(a.z);
	result.w = r32_abs(a.w);
	return(result);
}

inline r32
vec4_sum(Vec4 a)
{
	r32 result = 0;
	result += a.x;
	result += a.y;
	result += a.z;
	result += a.w;
	return(result);
}

inline Vec4
vec4_sym(Vec4 a)
{
	Vec4 result = VEC4_ZERO;
	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	result.w = -a.w;
	return(result);
}
