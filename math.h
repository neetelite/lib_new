#ifndef _math_h
#define _math_h

#include "./vector.h"
#include "./matrix.h"

/* Functions */
Mat4 mat4_rot_vec3(Vec3 rot);
Mat4 mat4_scl_vec3(Vec3 scl);
Mat4 mat4_pos_vec3(Vec3 pos);
Mat4 mat4_transform_vec2(Vec2 pos, Vec2 scl, r32 rot);
Mat4 mat4_transform_vec3(Vec3 pos, Vec3 scl, Vec3 rot);

#endif /* _math_h */
