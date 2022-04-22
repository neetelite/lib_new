#include <stdio.h>

#include "./graphics.h"
#include "./vector.h"
#include "./matrix.h"
#include "./debug.h"

struct GL gl;

/* General */
void
gl_enable(n32 flag)
{
	glEnable(flag);
}

void
gl_disable(n32 flag)
{
	glDisable(flag);
}

/* Functions */
void
gl_func_blend(n32 s_factor, n32 d_factor)
{
	glBlendFunc(s_factor, d_factor);
}

void
gl_func_depth(n32 func)
{
	glDepthFunc(func);
}

/* Viewport */
void
gl_viewport_rec_set(Vec4 dimension)
{
	glViewport(dimension.min.width, dimension.min.height, dimension.max.width, dimension.max.height);
}

void
gl_viewport_color_set(Vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void
gl_viewport_color_clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void
gl_viewport_depth_clear(void)
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void
gl_viewport_clear(void)
{
	gl_viewport_depth_clear();
	gl_viewport_color_clear();
}

/* Texture */
void
gl_texture_bind(struct GL_Texture *texture)
{
	glBindTexture(texture->type, texture->handle);
}

void
gl_texture_unbind(GLenum target)
{
	glBindTexture(target, 0);
}

void
gl_texture_gen(struct GL_Texture *texture, GLenum target, n32 sampling)
{
	/* NOTE: Example - gl_texture_gen(&texture, GL_TEXTURE_2D, GL_LINEAR); */
	glGenTextures(1, &texture->handle);

	texture->type = target;
	gl_texture_bind(texture);

	n32 format_output = 0;
	n32 format_input = 0;
	n32 representation = 0;

	switch(texture->image->channel_count)
	{
	case 4: format_output = GL_RGBA; break;
	case 3: format_output = GL_RGB; break;
	case 1: format_output = GL_RED; break;
	default: DBG_ERROR("Wrong number of channels in this image"); break;
	}

	switch(texture->image->format)
	{
	case IMG_FORMAT_RGBA: format_input = GL_RGBA; break;
	case IMG_FORMAT_RGB: format_input = GL_RGB; break;

	case IMG_FORMAT_BGRA: format_input = GL_BGRA; break;
	case IMG_FORMAT_BGR: format_input = GL_BGR; break;
	case IMG_FORMAT_C: format_input = GL_RED; break;
	default: DBG_ERROR("Wrong format type in this image"); break;
	}

	switch(texture->image->representation)
	{
	case IMG_REPRESENTATION_N8: representation = GL_UNSIGNED_BYTE; break;
	case IMG_REPRESENTATION_R32: representation = GL_FLOAT; break;
	}

	glTexImage2D(target, 0, format_output, texture->image->width, texture->image->height,
				 0, format_input, representation, texture->image->data);

	//glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(sampling == GL_LINEAR)
	{
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if(sampling == GL_NEAREST)
	{
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	gl_texture_unbind(target);
}

void
gl_texture_update(struct GL_Texture *texture)
{

	n32 format = 0;
	n32 representation = 0;

	switch(texture->image->format)
	{
	case IMG_FORMAT_RGBA: format = GL_RGBA; break;
	case IMG_FORMAT_RGB: format = GL_RGB; break;

	case IMG_FORMAT_BGRA: format = GL_BGRA; break;
	case IMG_FORMAT_BGR: format = GL_BGR; break;
	case IMG_FORMAT_C: format = GL_RED; break;
	default: DBG_ERROR("Wrong format type in this image"); break;
	}

	switch(texture->image->representation)
	{
	case IMG_REPRESENTATION_N8: representation = GL_UNSIGNED_BYTE; break;
	case IMG_REPRESENTATION_R32: representation = GL_FLOAT; break;
	}

	gl_texture_bind(texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0,
					0, 0, texture->image->width, texture->image->height,
					format, representation, texture->image->data
		);

	gl_texture_unbind(GL_TEXTURE_2D);
}

/* Uniform */
n32
gl_uniform_location(n32 program, CString location_name)
{
	n32 result = 0;
	result = glGetUniformLocation(program, location_name);
	return(result);
}

void
gl_uniform_i32(n32 location, i32 i)
{
	glUniform1i(location, i);
}

void
gl_uniform_r32(n32 location, r32 f)
{
	glUniform1fv(location, 1, (r32 *)&f);
}

void
gl_uniform_vec2(n32 location, Vec2 vec)
{
	glUniform2fv(location, 1, (r32 *)&vec);
}

void
gl_uniform_vec3(n32 location, Vec3 vec)
{
	glUniform3fv(location, 1, (r32 *)&vec);
}

void
gl_uniform_vec4(n32 location, Vec4 vec)
{
	glUniform4fv(location, 1, (r32 *)&vec);
}

void
gl_uniform_mat4(n32 location, Mat4 mat)
{
	Mat4 new_mat = mat4_t(mat);
	glUniformMatrix4fv(location, 1, GL_FALSE, (r32 *)&new_mat);
}

/* Shader */
void
gl_shader_attach(n32 program, n32 shader)
{
	glAttachShader(program, shader);
}

void
gl_shader_delete(n32 shader)
{
	glDeleteShader(shader);
}

/* Program */
n32
gl_program_gen(void)
{
	n32 result = 0;
	result = glCreateProgram();
	return(result);
}

void
gl_program_link(n32 program)
{
	glLinkProgram(program);
}

void
gl_program_bind(n32 handle)
{
	glUseProgram(handle);
}

void
gl_program_unbind(void)
{
	glUseProgram(0);
}

/* VAO */
void
gl_vao_gen(n32 count, n32 *vao)
{
	glGenVertexArrays(count, vao);
}

void
gl_vao_bind(n32 vao)
{
	glBindVertexArray(vao);
}

void
gl_vao_unbind()
{
	glBindVertexArray(0);
}

void
gl_vao_draw(n32 start, n32 count, n32 type)
{
	glDrawArrays(type, start, count);
}

/* VBO */
void
gl_vbo_gen(n32 count, n32 *vbo)
{
	glGenBuffers(count, vbo);
}

void
gl_vbo_bind(n32 vbo, n32 target)
{
	glBindBuffer(target, vbo);
}

void
gl_vbo_unbind(n32 target)
{
	glBindBuffer(target, 0);
}


void
gl_vbo_data(void *data, n64 size, n32 target, n32 draw)
{
	glBufferData(target, size, data, draw);
}

void
gl_vbo_sub(void *data, n64 size, n32 target)
{
	glBufferSubData(target, 0, size, data);
}

void
gl_vbo_attrib_set(n32 index, n32 count, n32 type, n32 stride, void *offset)
{
	/* FIXME LEARN(lungu): Do we really need normalized value? */
	Bool normalized = GL_FALSE;

	switch(type)
	{
	case GL_FLOAT:
	{
		glVertexAttribPointer(index, count, type, normalized, stride, offset);
	} break;
	case GL_UNSIGNED_INT:
	{
		glVertexAttribIPointer(index, count, type, stride, offset);
	} break;
	}
}

void
gl_vbo_attrib_enable(n32 index)
{
	glEnableVertexAttribArray(index);
}

/* CUSTOM */
struct GL_Program *
gl_get_program(String name)
{
	for(i32 i = 0; i < array_len(gl.programs); ++i)
	{
		struct GL_Program *program = &gl.programs[i];
		if(str_eql(&program->file.name, &name)) return(program);
	}
	return(NULL);
}

struct GL_Uniform *
gl_program_get_uniform(struct GL_Program *program, String name)
{
	for(i32 i = 0; i < array_len(program->uniforms); ++i)
	{
		struct GL_Uniform *uniform = &program->uniforms[i];
		if(str_eql(&uniform->name, &name)) return(uniform);
	}
	return(NULL);
}

n32
gl_shader_type_from_str(String *str)
{
	if(0);
	else if(cstr_eql_n(str->data, "vertex", 6)) return(GL_SHADER_VERTEX);
	else if(cstr_eql_n(str->data, "fragment", 8)) return(GL_SHADER_FRAGMENT);
	else DBG_ERROR("Passed invalid shader type\n");
}

struct GL_Program
gl_program_load_from_file(struct File *file)
{
	/* TODO(lungu): Maybe let shader be a pointer so when it returns null we know it failed */
	struct GL_Program result = {0};
	result.file = *file;
	result.handle = gl_program_gen();

	i32 ret = file_open(file, FILE_OPEN_MODE_BYTE_READ);
	if(ret < 0)
	{
		DBG_ERROR("Failed to load file");
		return(result);
	}

	String data = file_data(file);
	file_close(file);

	/* Shader */
	n32 shader_count = 0;
	String start = data;
	String end = data;
	while(1)
	{
		/* TODO: Error logging */
		/* Find shader */
		start = str_find(&end, &STR("#start_shader"));
		if(start.len == 0) break;

		start = str_find_and_skip_whitespace(&start);
		n32 shader_type = gl_shader_type_from_str(&start);

		start = str_find_and_skip_whitespace(&start);
		end = str_find_from(&start, &STR("#end_shader"), start.data);
		if(end.len == 0) break;

		n32 shader_size = end.data - start.data;

		/* Compiler shader */
		n32 shader = glCreateShader(shader_type);
		glShaderSource(shader, 1, (char **)&start.data, &shader_size);
		glCompileShader(shader);

		i32 success;
		char info_log[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if(!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, info_log);

			DBG_ERROR("Failed to compile shader: %s\n", file->path.data);
			DBG_INFO("%s", info_log);

			glDeleteProgram(result.handle);
			result.handle = 0;
			return(result);
		}

		gl_shader_attach(result.handle, shader);
		start = end;
		shader_count += 1;
	}
	if(shader_count == 0)
	{
		DBG_ERROR("There were no shaders found on this file: %s\n", file->path.data);
		glDeleteProgram(result.handle);
		result.handle = 0;
		return(result);
	}
	gl_program_link(result.handle);

	/* Uniforms */
	start = data;
	end = data;
	while(1)
	{
		start = str_find(&end, &STR("uniform"));
		if(start.len == 0) break;

		start = str_find_and_skip_whitespace(&start);
		start = str_find_and_skip_whitespace(&start);

		end = str_find_from(&start, &STR(";"), start.data);

		struct GL_Uniform uniform = {0};
		String name = str_sub(&data, start.data, end.data);
		uniform.name = str_dup(&name);
		uniform.location = gl_uniform_location(result.handle, uniform.name.data);

		#if 0
		if(uniform.location == -1)
		{
			DBG_INFO("Uniform '%s' is not being used\n", uniform.name.data);
		}
		#endif

		array_push(result.uniforms, uniform);

		start = end;
	}

	str_free(&data);

	DBG_INFO("Program loaded: %s\n", file->name.data);

	return(result);
}

struct GL_Program
gl_load_program(String name)
{
	String shader_path = str_alloc_n(PATH_MAX);
	str_cat(&shader_path, &STR(os_state.path_run), &STR("data/shader/"));
	str_cat(&shader_path, &shader_path, &name);

	struct File file = file_init(&shader_path);
	struct GL_Program program = gl_program_load_from_file(&file);
	return(program);
}

/* Matrixes */
Mat4
gl_projection_2d(r32 w, r32 h)
{
	/* Projection */
	r32 z = 1.0;
	r32 n = 0.00001; /* NOTE(lungu): Can't be negative or zero */
	r32 f = 1000;

	r32 r = w;
	r32 l = 0;
	r32 t = h;
	r32 b = 0;

	r32 A = (2 / (r - l)) / z;
	r32 B = (2 / (t - b)) / z;
	r32 C = -2 / (f - n);

	r32 D = -(r + l) / (r - l);
	r32 E = -(t + b) / (t - b);
	r32 F = 0;

	Mat4 result = MAT4
		(
			A, 0, 0, D,
			0, B, 0, E,
			0, 0, C, F,
			0, 0, 0, 1
		);

	return(result);
}
