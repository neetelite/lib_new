#include "./line.h"
#include "../graphics.h"

inline struct Line2
LINE2(enum Line_Type type, Vec2 start, Vec2 end)
{
	struct Line2 result = {};
	result.type = type;
	result.start = start;
	result.end = end;
	return(result);
}

void
line2_draw(struct Line2 *line)
{
	struct GL_Program *program = gl_get_program(STR("arrow.glsl"));
	gl_program_bind(program->handle);

	struct GL_Uniform *u_pos = gl_program_get_uniform(program, STR("u_pos"));
	gl_uniform_vec4(u_pos->location, line->vec);

	struct GL_Uniform *u_res = gl_program_get_uniform(program, STR("u_res"));
	gl_uniform_vec2(u_res->location, VEC2(os_display.window_main.dim.width, os_display.window_main.dim.height));

	n32 triangle_count = 2;
	gl_vao_draw(0, triangle_count * 3, GL_TRIANGLES);

	gl_program_unbind();
}
