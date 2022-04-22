#ifndef _time_h
#define _time_h

#include "./scalar/natural.h"

enum Date_CommonEra
{
	DATE_COMMON_ERA_BC,
	DATE_COMMON_ERA_AD,
};

struct Date
{
	enum Date_CommonEra common_era;

	union
	{
		struct
		{
			n16 Y;
			n8 M;
			n8 D;
			n8 h;
			n8 m;
			n8 s;
			n16 ms;
			n16 us;
			n16 ns;

			n8 W; /* Irrelevant */
			n8 DW; /* Irrelevant */
		};
		struct
		{
			n8 year;
			n8 month;
			n8 day;
			n8 hour;
			n8 minute;
			n8 second;
			n16 millisecond;
			n16 microsecond;
			n16 nanosecond;

			n8 week; /* Irrelevant */
			n8 day_of_the_week; /* Irrelevant */
		};
	};
};

#endif /* _time_h */
