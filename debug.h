#ifndef _debug_h
#define _debug_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
//#define DBG_ASSERT(expression) if(!(expression)) {*(volatile int *)0 = 0;}
#define DBG_ASSERT(expression) if(!(expression)) {printf("ASSERT: %s:%d\n", __FILE__, __LINE__); *(volatile int *)0 = 0;}
#else
#define DBG_ASSERT(expression)
#endif

#define DBG_INVALID_PATH DBG_ASSERT(!"Invalid Path")

#if 1
#define DBG_PRINT(message, ...)   printf(message, ##__VA_ARGS__)
#define DBG_FATAL(message, ...)   printf(message, ##__VA_ARGS__)
#define DBG_ERROR(message, ...)   printf(message, ##__VA_ARGS__)
#define DBG_WARNING(message, ...) printf(message, ##__VA_ARGS__)
#define DBG_INFO(message, ...)    printf(message, ##__VA_ARGS__)
#else
#define DBG_PRINT(message, ...)
#define DBG_FATAL(message, ...)
#define DBG_ERROR(message, ...)
#define DBG_WARNING(message, ...)
#define DBG_INFO(message, ...)
#endif

#endif /* _debug_h */
