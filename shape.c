#include "./shape.h"

inline struct Box2
box2_from_rec2(struct Rec2 rec)
{
	struct Box2 result = {0};
	result.dim = VEC2(rec.end.x-rec.start.x, rec.end.y-rec.start.y);
	result.pos = vec2_a(rec.start, vec2_mr(result.dim, 0.5));
	result.rot = 0;
	result.scl = VEC2_ONE;
	return(result);
}
