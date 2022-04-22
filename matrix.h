#ifndef _matrix_h
#define _matrix_h

#include "./scalar/real.h"

/* Structures */
typedef struct Matrix3x3
{
	union
	{
		r32 m[3][3];
		r32 i[9];
		struct
		{
			r32 m00, m01, m02;
			r32 m10, m11, m12;
			r32 m20, m21, m22;
		};
	};
} Mat3;

typedef struct Matrix4x4
{
	union
	{
		r32 m[4][4];
		r32 i[16];
		struct
		{
			r32 m00, m01, m02, m03;
			r32 m10, m11, m12, m13;
			r32 m20, m21, m22, m23;
			r32 m30, m31, m32, m33;
		};
	};
} Mat4;

/* Constructors */
Mat3 MAT3(r32 m00, r32 m01, r32 m02,
		  r32 m10, r32 m11, r32 m12,
		  r32 m20, r32 m21, r32 m22);

Mat4 MAT4(r32 m00, r32 m01, r32 m02, r32 m03,
		  r32 m10, r32 m11, r32 m12, r32 m13,
		  r32 m20, r32 m21, r32 m22, r32 m23,
		  r32 m30, r32 m31, r32 m32, r32 m33);

/* Macros */
#define MAT3_ID   MAT3(1,0,0, 0,1,0, 0,0,1)
#define MAT3_ZERO MAT3(0,0,0, 0,0,0, 0,0,0)

#define MAT4_ID   MAT4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)
#define MAT4_ZERO MAT4(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0)

/* Functions */
Mat4 mat4_t(Mat4 a);
Mat4 mat4_m(Mat4 a, Mat4 b);

Mat4 mat4_rot_x(r32 a);
Mat4 mat4_rot_y(r32 a);
Mat4 mat4_rot_z(r32 a);

#endif /* _matrix_h */
