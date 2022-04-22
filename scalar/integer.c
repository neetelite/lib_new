#include <math.h>
#include "./integer.h"

i32
i32_pow(i32 base, i32 exp)
{
	i32 result = (i32)(pow(base, exp) + 0.5);
	return(result);
}
