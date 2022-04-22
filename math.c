#include "math.h"

Mat4
mat4_rot_vec3(Vec3 rot)
{
	Mat4 result = MAT4_ID;

	result = mat4_m(mat4_rot_x(rot.x), result);
	result = mat4_m(mat4_rot_y(rot.y), result);
	result = mat4_m(mat4_rot_z(rot.z), result);

	return(result);
}

Mat4
mat4_scl_vec3(Vec3 scl)
{
	Mat4 result = MAT4_ID;

	result.m[0][0] = scl.x;
	result.m[1][1] = scl.y;
	result.m[2][2] = scl.z;

	return(result);
}

Mat4
mat4_pos_vec3(Vec3 pos)
{
	Mat4 result = MAT4_ID;

	result.m[0][3] = pos.x;
	result.m[1][3] = pos.y;
	result.m[2][3] = pos.z;

	return(result);
}

Mat4
mat4_transform_vec2(Vec2 pos, Vec2 scl, r32 rot)
{
	Mat4 result = MAT4_ID;

	Mat4 mat_pos = mat4_pos_vec3(VEC3_VEC2_XY(pos, 0.0));
	Mat4 mat_scl = mat4_scl_vec3(VEC3_VEC2_XY(scl, 0.0));
	Mat4 mat_rot = mat4_rot_vec3(VEC3(rot, rot, rot));

	result = mat4_m(mat_scl, result);
	result = mat4_m(mat_rot, result);
	result = mat4_m(mat_pos, result);

	return(result);
}

Mat4
mat4_transform_vec3(Vec3 pos, Vec3 scl, Vec3 rot)
{
	Mat4 result = MAT4_ID;

	Mat4 mat_pos = mat4_pos_vec3(pos);
	Mat4 mat_scl = mat4_scl_vec3(scl);
	Mat4 mat_rot = mat4_rot_vec3(rot);

	result = mat4_m(mat_scl, result);
	result = mat4_m(mat_rot, result);
	result = mat4_m(mat_pos, result);

	return(result);
}
