#ifndef _shape_line_h
#define _shape_line_h

#include "../vector.h"

enum Line_Type
{
	LINE_ARROW,
	LINE_SEGMENT,
	LINE_INFINITE,
};

struct Line2
{
	enum Line_Type type;
	union
	{
		struct
		{
			Vec2 start;
			Vec2 end;
		};
		Vec4 vec;
	};
};

/* Functions */
struct Line2 LINE2(enum Line_Type type, Vec2 start, Vec2 end);
struct Line3 LINE3(enum Line_Type type, Vec3 start, Vec3 end);

struct Line2 LINE2(enum Line_Type type, Vec2 start, Vec2 end);
void line2_draw(struct Line2 *line);


#endif /* _shape_line_h */
