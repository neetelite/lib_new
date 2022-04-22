#ifndef _graphics_h
#define _graphics_h

#include "./graphics/opengl.h"
#include "./scalar/natural.h"
#include "./string.h"
#include "./image.h"
#include "./file.h"
#include "./array.h"
#include "./vector.h"
#include "./matrix.h"

#define GL_SHADER_VERTEX GL_VERTEX_SHADER
#define GL_SHADER_FRAGMENT GL_FRAGMENT_SHADER

struct GL_Texture
{
	n32 type;
	n32 handle;
	struct Image *image;
};

struct GL_Uniform
{
	String name;
	n32 location;
};

struct GL_Program
{
	struct File file;

	n32 handle;
	struct GL_Uniform *uniforms;
};

struct GL
{
	struct GL_Program ARR_D programs;
	Mat4 projection_2d;
};
extern struct GL gl;

/* Functions */
void gl_enable(n32 flag);
void gl_disable(n32 flag);
void gl_func_blend(n32 s_factor, n32 d_factor);
void gl_func_depth(n32 func);

void gl_viewport_rec_set(Vec4 dimension);
void gl_viewport_color_set(Vec4 color);
void gl_viewport_color_clear(void);
void gl_viewport_depth_clear(void);
void gl_viewport_clear(void);

void gl_texture_gen(struct GL_Texture *texture, GLenum target, n32 sampling);
void gl_texture_bind(struct GL_Texture *texture);
void gl_texture_unbind(GLenum target);
void gl_texture_update(struct GL_Texture *texture);

n32 gl_uniform_location(n32 program, CString location_name);
void gl_uniform_i32(n32 location, i32 i);
void gl_uniform_vec2(n32 location, Vec2 vec);
void gl_uniform_vec3(n32 location, Vec3 vec);
void gl_uniform_vec4(n32 location, Vec4 vec);
void gl_uniform_mat4(n32 location, Mat4 mat);

void gl_shader_attach(n32 program, n32 shader);

n32 gl_program_gen(void);
void gl_program_link(n32 program);
void gl_program_bind(n32 handle);
void gl_program_unbind(void);

void gl_vao_draw(n32 start, n32 count, n32 type);

/* CUSTOM */
struct GL_Program * gl_get_program(String name);
struct GL_Uniform * gl_program_get_uniform(struct GL_Program *program, String name);

struct GL_Program gl_load_program(String name);
Mat4 gl_projection_2d(r32 w, r32 h);

#endif /* _graphics_h */
