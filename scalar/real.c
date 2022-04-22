#include "real.h"

inline r32
r32_abs(r32 a)
{
	r32 result = a;
	if(a < 0) result = -a;
	return(result);
}

/* Angles */
inline r32
r32_sin(r32 a)
{
	r32 result = sinf(a);
	return(result);
}

inline r32
r32_cos(r32 a)
{
	r32 result = cosf(a);
	return(result);
}

inline r32
r32_tan(r32 a)
{
	r32 result = tan(a);
	return(result);
}

inline r32
r32_step(r32 edge, r32 x)
{
	r32 result = 0.0;
	if(x >= edge) result = 1.0;
	return(result);
}

inline r32
r32_pow(r32 b, r32 p)
{
	r32 result = powf(b, p);
	return(result);
}

inline r32
r32_sqrt(r32 a)
{
	r32 result = sqrt(a);
	return(result);
}
