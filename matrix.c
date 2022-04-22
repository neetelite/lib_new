#include "matrix.h"
#include "./scalar/integer.h"

/* Constructors */
Mat3
MAT3(r32 m00,  r32 m01,  r32 m02,
     r32 m10,  r32 m11,  r32 m12,
     r32 m20,  r32 m21,  r32 m22)
{
	//NOTE(kaede): When initializing you need to use brakets for every
	//struct and union that's wrapping the array. Tested in G++ too.
	Mat3 result = (Mat3){m00, m01, m02,
			     m10, m11, m12,
			     m20, m21, m22};
	return(result);
}

Mat4
MAT4(r32 m00,  r32 m01,  r32 m02,  r32 m03,
     r32 m10,  r32 m11,  r32 m12,  r32 m13,
     r32 m20,  r32 m21,  r32 m22,  r32 m23,
     r32 m30,  r32 m31,  r32 m32,  r32 m33)
{
	//NOTE(kaede): When initializing you need to use brakets for every
	//struct and union that's wrapping the array. Tested in G++ too.
	Mat4 result = (Mat4){m00, m01, m02, m03,
			     m10, m11, m12, m13,
			     m20, m21, m22, m23,
			     m30, m31, m32, m33};
	return(result);
}

Mat4
mat4_t(Mat4 a)
{
	/* From column-major to row-maor and vice-versa */
	Mat4 result = MAT4_ZERO;
	for(i32 i = 0; i < 4; ++i)
	{
		for(i32 j = 0; j < 4; ++j)
		{
			result.m[i][j] = a.m[j][i];
		}
	}
	return(result);
}

Mat4
mat4_m(Mat4 a, Mat4 b)
{
	Mat4 result = MAT4_ZERO;
	for(i32 row = 0; row < 4; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			r32 sum = 0;
			for(i32 i = 0; i < 4; i++)
			{
				sum += (a.m[row][i] * b.m[i][col]);
			}
			result.m[row][col] = sum;
		}
	}

	return(result);
}

Mat4
mat4_rot_x(r32 a)
{
	//a = r32_rad_from_deg(a);

	r32 c = r32_cos(a);
	r32 s = r32_sin(a);

	Mat4 result = MAT4
		(
			1, 0, 0,  0,
			0, c, -s, 0,
			0, s, c,  0,
			0, 0, 0,  1
		);

	return(result);
}

Mat4
mat4_rot_y(r32 a)
{
	//a = r32_rad_from_deg(a);

	r32 c = r32_cos(a);
	r32 s = r32_sin(a);

	Mat4 result = MAT4
		(
			c,  0, s,  0,
			0,  1, 0,  0,
			-s, 0, c,  0,
			0,  0, 0,  1
		);

	return(result);
}

Mat4
mat4_rot_z(r32 a)
{
	//a = r32_rad_from_deg(a);

	r32 c = r32_cos(a);
	r32 s = r32_sin(a);

	Mat4 result = MAT4
		(
			c, -s, 0,  0,
			s, c,  0,  0,
			0, 0,  1,  0,
			0, 0,  0,  1
		);

	return(result);
}
