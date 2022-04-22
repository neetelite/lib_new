#ifndef _integer_h
#define _integer_h

#include <stdint.h>

/* Typedefs */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

/* Defines */
#define  I8_MIN (-128)
#define I16_MIN (-32768)
#define I32_MIN (-2147483648)
#define I64_MIN (-9223372036854775808)

#define  I8_MAX (127)
#define I16_MAX (32767)
#define I32_MAX (2147483647)
#define I64_MAX (9223372036854775807)

/* Functions */
i32 i32_pow(i32 base, i32 exp);

#endif /* _integer_h */
