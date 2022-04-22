#ifndef _real_h
#define _real_h

#include <math.h>

/* Typedefs */
typedef float r32;
typedef double r64;

/* Constants */
#define R32_INF 		INFINITY
#define R32_NAN 		NAN
#define R32_PRECISION 	6

#define R64_PI      	(3.141592653589793238462643383279)
#define R64_TAU     	(6.283185307179586476925286766559)
#define R64_PRECISION 	15

/* Functions */
r32 r32_abs(r32 a);
r32 r32_sin(r32 a);
r32 r32_cos(r32 a);
r32 r32_ton(r32 a);
r32 r32_step(r32 edge, r32 x);
r32 r32_pow(r32 b, r32 p);
r32 r32_sqrt(r32 a);

#endif /* _real_h */
