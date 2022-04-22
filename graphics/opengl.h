#ifndef _opengl_h
#define _opengl_h

#include "../os.h"
#include "../cstring.h"

/* Structures */
struct OpenGL_Info
{
	CString vendor;
	CString renderer;

	CString version;
	n32 version_major;
	n32 version_minor;

	CString gsl_version;
};

#if OS == OS_LINUX
	#include <GL/gl.h>
	#include <GL/glx.h>
	#define API
	#define OPENGL_PROC_ADDRESS_GET(name) glXGetProcAddress((GLubyte*)name)
#elif OS == OS_WINDOWS
	#include <gl/gl.h>
	#define API WINAPI
#endif

/* Functions */
void opengl_init(void);

/* Functions gl */
typedef void API FN_glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void API FN_glBindFramebuffer(GLenum target, GLuint framebuffer);
typedef void API FN_glGenFramebuffers(GLsizei n, GLuint *framebuffers);
typedef void API FN_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef GLenum API FN_glCheckFramebufferStatus(GLenum target);
typedef void API FN_glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void API FN_glAttachShader(GLuint program, GLuint shader);
typedef void API FN_glCompileShader(GLuint shader);
typedef GLuint API FN_glCreateProgram(void);
typedef void API FN_glDeleteProgram(GLuint program);
typedef GLuint API FN_glCreateShader(GLenum type);
typedef void API FN_glLinkProgram(GLuint program);
typedef void API FN_glShaderSource(GLuint shader, GLsizei count, GLchar **string, GLint *length);
typedef void API FN_glUseProgram(GLuint program);
typedef void API FN_glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void API FN_glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void API FN_glValidateProgram(GLuint program);
typedef void API FN_glGetProgramiv(GLuint program, GLenum pname, GLint *params);
typedef GLint API FN_glGetUniformLocation (GLuint program, const GLchar *name);
typedef void API FN_glUniform4fv(GLint location, GLsizei count, const GLfloat *value);
typedef void API FN_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void API FN_glUniform1i(GLint location, GLint v0);
typedef const GLubyte * API FN_glGetStringi(GLenum name, GLuint index);
typedef void API FN_glUniform1fv(GLint location, GLsizei count, const GLfloat *value);
typedef void API FN_glUniform2fv(GLint location, GLsizei count, const GLfloat *value);
typedef void API FN_glUniform3fv(GLint location, GLsizei count, const GLfloat *value);
typedef void API FN_glEnableVertexAttribArray(GLuint index);
typedef void API FN_glDisableVertexAttribArray(GLuint index);
typedef GLint API FN_glGetAttribLocation(GLuint program, const GLchar *name);
typedef void API FN_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void API FN_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void API FN_glBindVertexArray(GLuint array);
typedef void API FN_glGenVertexArrays(GLsizei n, GLuint *arrays);
typedef void API FN_glBindBuffer(GLenum target, GLuint buffer);
typedef void API FN_glGenBuffers(GLsizei n, GLuint *buffers);
typedef void API FN_glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void API FN_glGetShaderiv(GLuint shader, GLenum pname, GLint *params);
typedef void API FN_glDeleteShader(GLuint shader);
typedef void API FN_glGenerateMipmap(GLenum target);
typedef void API FN_glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void API FN_glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void API FN_glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);

#define OPENGL_FUNCTION_DECLARE_EXTERN(name) extern FN_##name *name
OPENGL_FUNCTION_DECLARE_EXTERN(glTexImage2DMultisample);
OPENGL_FUNCTION_DECLARE_EXTERN(glBindFramebuffer);
OPENGL_FUNCTION_DECLARE_EXTERN(glGenFramebuffers);
OPENGL_FUNCTION_DECLARE_EXTERN(glFramebufferTexture2D);
OPENGL_FUNCTION_DECLARE_EXTERN(glCheckFramebufferStatus);
OPENGL_FUNCTION_DECLARE_EXTERN(glBlitFramebuffer);
OPENGL_FUNCTION_DECLARE_EXTERN(glAttachShader);
OPENGL_FUNCTION_DECLARE_EXTERN(glCompileShader);
OPENGL_FUNCTION_DECLARE_EXTERN(glCreateProgram);
OPENGL_FUNCTION_DECLARE_EXTERN(glDeleteProgram);
OPENGL_FUNCTION_DECLARE_EXTERN(glCreateShader);
OPENGL_FUNCTION_DECLARE_EXTERN(glLinkProgram);
OPENGL_FUNCTION_DECLARE_EXTERN(glShaderSource);
OPENGL_FUNCTION_DECLARE_EXTERN(glUseProgram);
OPENGL_FUNCTION_DECLARE_EXTERN(glGetProgramInfoLog);
OPENGL_FUNCTION_DECLARE_EXTERN(glGetShaderInfoLog);
OPENGL_FUNCTION_DECLARE_EXTERN(glValidateProgram);
OPENGL_FUNCTION_DECLARE_EXTERN(glGetProgramiv);
OPENGL_FUNCTION_DECLARE_EXTERN(glGetUniformLocation);
OPENGL_FUNCTION_DECLARE_EXTERN(glUniform4fv);
OPENGL_FUNCTION_DECLARE_EXTERN(glUniformMatrix4fv);
OPENGL_FUNCTION_DECLARE_EXTERN(glUniform1i);
OPENGL_FUNCTION_DECLARE_EXTERN(glGetStringi);
OPENGL_FUNCTION_DECLARE_EXTERN(glUniform1fv);
OPENGL_FUNCTION_DECLARE_EXTERN(glUniform2fv);
OPENGL_FUNCTION_DECLARE_EXTERN(glUniform3fv);
OPENGL_FUNCTION_DECLARE_EXTERN(glEnableVertexAttribArray);
OPENGL_FUNCTION_DECLARE_EXTERN(glDisableVertexAttribArray);
OPENGL_FUNCTION_DECLARE_EXTERN(glGetAttribLocation);
OPENGL_FUNCTION_DECLARE_EXTERN(glVertexAttribPointer);
OPENGL_FUNCTION_DECLARE_EXTERN(glVertexAttribIPointer);
OPENGL_FUNCTION_DECLARE_EXTERN(glBindVertexArray);
OPENGL_FUNCTION_DECLARE_EXTERN(glGenVertexArrays);
OPENGL_FUNCTION_DECLARE_EXTERN(glBindBuffer);
OPENGL_FUNCTION_DECLARE_EXTERN(glGenBuffers);
OPENGL_FUNCTION_DECLARE_EXTERN(glBufferData);
OPENGL_FUNCTION_DECLARE_EXTERN(glGetShaderiv);
OPENGL_FUNCTION_DECLARE_EXTERN(glDeleteShader);
OPENGL_FUNCTION_DECLARE_EXTERN(glGenerateMipmap);
OPENGL_FUNCTION_DECLARE_EXTERN(glUniform3f);
OPENGL_FUNCTION_DECLARE_EXTERN(glBufferSubData);

#endif /* _opengl_h */
