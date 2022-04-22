#include "./text.h"
#include "./shape.h"
#include "./asset.h"
#include "./math.h"

#include "./debug.h"
#include "./graphics.h"


r32
cstr_text_width(CString text, struct Font *font)
{
	/* TODO(lungu): Crash when text is null string */

	r32 result = 0.0;

	n32 codepoint_previous = 0;
	for(i32 i = 0; text[i] != '\0'; ++i)
	{
		n32 codepoint = text[i];

		r32 advance = font_kerning_get(font, codepoint, codepoint_previous);
		result += advance;

		codepoint_previous = codepoint;
	}

	result += font_glyph_texture_get(font, codepoint_previous).image->width - 2;

	return(result);
}

void
cstr_draw_full(struct Font *font, CString text, Vec3 pos,
			   struct UI_Align align, Mat4 mat_view, Vec4 color)
{
	r32 scale = 1.0;

	r32 width = cstr_text_width(text, font);
	r32 width_half = .5*width;

	r32 height = font->height;
	r32 height_half = .5*height;

	/* TODO: Default alignment */
	if(align.h == UI_ALIGN_H_NULL) align.h = UI_ALIGN_H_MIDDLE;
	if(align.v == UI_ALIGN_V_NULL) align.v = UI_ALIGN_V_CENTER;

	switch(align.h)
	{
	case UI_ALIGN_H_LEFT:   pos.x -= 0; break;
	case UI_ALIGN_H_MIDDLE:	pos.x -= width_half; break;
	case UI_ALIGN_H_RIGHT:	pos.x -= width; break;
	default:				DBG_INVALID_PATH; break;
	}

	/* TODO(lungu): font->height doesn't seem to work very well */
	switch(align.v)
	{
	case UI_ALIGN_V_NULL:	DBG_INVALID_PATH; break;
	case UI_ALIGN_V_BOTTOM:	pos.y -= height; break;
	case UI_ALIGN_V_CENTER:	pos.y -= height_half; break;
	case UI_ALIGN_V_TOP:	pos.y -= 0; break;
	}

	/* OpenGL */
	struct GL_Program *program = gl_get_program(STR("text.glsl"));
	gl_program_bind(program->handle);

	struct GL_Uniform *u_mvp = gl_program_get_uniform(program, STR("u_mvp"));
	gl_uniform_mat4(u_mvp->location, mat_view);

	struct GL_Uniform *u_color = gl_program_get_uniform(program, STR("u_color"));
	gl_uniform_vec4(u_color->location, color);

	n32 codepoint_previous = 0;
	for(n32 i = 0; text[i] != '\0'; ++i)
	{
		n32 codepoint = text[i];

		r32 advance_x = scale*font_kerning_get(font, codepoint, codepoint_previous);
		pos.x += advance_x;

		struct GL_Texture texture = font_glyph_texture_get(font, codepoint);
		gl_texture_bind(&texture);

		Vec2 baseline_align = font_glyph_alignment_get(font, codepoint);
		baseline_align = vec2_m(baseline_align, VEC2(texture.image->width, texture.image->height));

		Vec2 render_pos = vec2_s(pos.xy, baseline_align);

		Vec2 min, max;
		min = render_pos;
		max = vec2_a(render_pos, VEC2(texture.image->width, texture.image->height));

		struct Rec2 rec = REC2(min, max);
		struct Box2 box = box2_from_rec2(rec);

		Vec3 mat_pos = VEC3(box.pos.x, box.pos.y, pos.z);
		Vec3 mat_dim = VEC3(box.dim.x, box.dim.y, 0.0);
		Mat4 mvp = mat4_m(mat_view, mat4_transform_vec3(mat_pos, mat_dim, VEC3_ZERO));
		gl_uniform_mat4(u_mvp->location, mvp);

 n32 triangle_count = 2;
		gl_vao_draw(0, triangle_count * 3, GL_TRIANGLES);

		codepoint_previous = codepoint;
	}

	gl_texture_unbind(GL_TEXTURE_2D);
	gl_program_unbind();
}

void
vec3_text_draw_full(struct Font *font,
	     Vec3 vec, CString s, Vec3 pos, struct UI_Align align, Mat4 mat_view, Vec4 color)
{
	#define BUFFER_MAX 256

	char text[BUFFER_MAX];
	snprintf(text, BUFFER_MAX, "%s x: %-12f y: %-12f z: %-12f", s, vec.x, vec.y, vec.z);

	cstr_draw_full(font, text, pos, align, mat_view, color);
}

void
cstr_draw(CString text, Vec3 pos, struct UI_Align align, Mat4 mat_view, Vec4 color)
{
	/* this is a comment */
	cstr_draw_full(asset_font_default(), text, pos, align, mat_view, color);
}
