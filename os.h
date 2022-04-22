#ifndef _os_h
#define _os_h

#define OS_LINUX   0
#define OS_WINDOWS 1

#ifndef OS
	#error Operating system was not defined!
#endif

#if OS == OS_LINUX
	#include "./os/linux.h"
#elif OS == OS_WINDOWS
	#include "./os/windows.h"
#else
	#error Operating system is not valid!
#endif

#endif /* _os_h */
