#include <stdlib.h> /* TODO: Remove this */

#include "./opengl.h"
#include "../char.h"

struct OpenGL_Info
opengl_info(void)
{
	struct OpenGL_Info result = {};
	result.vendor = (CString)glGetString(GL_VENDOR);
	result.renderer = (CString)glGetString(GL_RENDERER);
	result.version = (CString)glGetString(GL_VERSION);
	result.gsl_version = (CString)glGetString(GL_SHADING_LANGUAGE_VERSION);

	/* Get the minor version */
	CString major_at = result.version;
	CString minor_at = 0;
	for(Char *at = &result.version[0]; *at != '\0'; ++at)
	{
		if(*at == '.')
		{
			minor_at = at + 1;
			break;
		}
	}

	if(minor_at)
	{
		result.version_major = atoi(major_at);
		result.version_minor = atoi(minor_at);
	}

	return(result);
}

/* Function pointers */
#define OPENGL_FUNCTION_DECLARE(name) FN_##name *name
OPENGL_FUNCTION_DECLARE(glTexImage2DMultisample);
OPENGL_FUNCTION_DECLARE(glBindFramebuffer);
OPENGL_FUNCTION_DECLARE(glGenFramebuffers);
OPENGL_FUNCTION_DECLARE(glFramebufferTexture2D);
OPENGL_FUNCTION_DECLARE(glCheckFramebufferStatus);
OPENGL_FUNCTION_DECLARE(glBlitFramebuffer);
OPENGL_FUNCTION_DECLARE(glAttachShader);
OPENGL_FUNCTION_DECLARE(glCompileShader);
OPENGL_FUNCTION_DECLARE(glCreateProgram);
OPENGL_FUNCTION_DECLARE(glDeleteProgram);
OPENGL_FUNCTION_DECLARE(glCreateShader);
OPENGL_FUNCTION_DECLARE(glLinkProgram);
OPENGL_FUNCTION_DECLARE(glShaderSource);
OPENGL_FUNCTION_DECLARE(glUseProgram);
OPENGL_FUNCTION_DECLARE(glGetProgramInfoLog);
OPENGL_FUNCTION_DECLARE(glGetShaderInfoLog);
OPENGL_FUNCTION_DECLARE(glValidateProgram);
OPENGL_FUNCTION_DECLARE(glGetProgramiv);
OPENGL_FUNCTION_DECLARE(glGetUniformLocation);
OPENGL_FUNCTION_DECLARE(glUniform4fv);
OPENGL_FUNCTION_DECLARE(glUniformMatrix4fv);
OPENGL_FUNCTION_DECLARE(glUniform1i);
OPENGL_FUNCTION_DECLARE(glGetStringi);
OPENGL_FUNCTION_DECLARE(glUniform1fv);
OPENGL_FUNCTION_DECLARE(glUniform2fv);
OPENGL_FUNCTION_DECLARE(glUniform3fv);
OPENGL_FUNCTION_DECLARE(glEnableVertexAttribArray);
OPENGL_FUNCTION_DECLARE(glDisableVertexAttribArray);
OPENGL_FUNCTION_DECLARE(glGetAttribLocation);
OPENGL_FUNCTION_DECLARE(glVertexAttribPointer);
OPENGL_FUNCTION_DECLARE(glVertexAttribIPointer);
OPENGL_FUNCTION_DECLARE(glBindVertexArray);
OPENGL_FUNCTION_DECLARE(glGenVertexArrays);
OPENGL_FUNCTION_DECLARE(glBindBuffer);
OPENGL_FUNCTION_DECLARE(glGenBuffers);
OPENGL_FUNCTION_DECLARE(glBufferData);
OPENGL_FUNCTION_DECLARE(glGetShaderiv);
OPENGL_FUNCTION_DECLARE(glDeleteShader);
OPENGL_FUNCTION_DECLARE(glGenerateMipmap);
OPENGL_FUNCTION_DECLARE(glUniform3f);
OPENGL_FUNCTION_DECLARE(glBufferSubData);

void
opengl_functions_load(void)
{
#define OPENGL_FUNCTION_INITIALIZE(name) name = (FN_##name *)OPENGL_PROC_ADDRESS_GET(#name)
	OPENGL_FUNCTION_INITIALIZE(glTexImage2DMultisample);
	OPENGL_FUNCTION_INITIALIZE(glBindFramebuffer);
	OPENGL_FUNCTION_INITIALIZE(glGenFramebuffers);
	OPENGL_FUNCTION_INITIALIZE(glFramebufferTexture2D);
	OPENGL_FUNCTION_INITIALIZE(glCheckFramebufferStatus);
	OPENGL_FUNCTION_INITIALIZE(glBlitFramebuffer);
	OPENGL_FUNCTION_INITIALIZE(glAttachShader);
	OPENGL_FUNCTION_INITIALIZE(glCompileShader);
	OPENGL_FUNCTION_INITIALIZE(glCreateProgram);
	OPENGL_FUNCTION_INITIALIZE(glDeleteProgram);
	OPENGL_FUNCTION_INITIALIZE(glCreateShader);
	OPENGL_FUNCTION_INITIALIZE(glLinkProgram);
	OPENGL_FUNCTION_INITIALIZE(glShaderSource);
	OPENGL_FUNCTION_INITIALIZE(glUseProgram);
	OPENGL_FUNCTION_INITIALIZE(glGetProgramInfoLog);
	OPENGL_FUNCTION_INITIALIZE(glGetShaderInfoLog);
	OPENGL_FUNCTION_INITIALIZE(glValidateProgram);
	OPENGL_FUNCTION_INITIALIZE(glGetProgramiv);
	OPENGL_FUNCTION_INITIALIZE(glGetUniformLocation);
	OPENGL_FUNCTION_INITIALIZE(glUniform4fv);
	OPENGL_FUNCTION_INITIALIZE(glUniformMatrix4fv);
	OPENGL_FUNCTION_INITIALIZE(glUniform1i);
	OPENGL_FUNCTION_INITIALIZE(glGetStringi);
	OPENGL_FUNCTION_INITIALIZE(glUniform1fv);
	OPENGL_FUNCTION_INITIALIZE(glUniform2fv);
	OPENGL_FUNCTION_INITIALIZE(glUniform3fv);
	OPENGL_FUNCTION_INITIALIZE(glEnableVertexAttribArray);
	OPENGL_FUNCTION_INITIALIZE(glDisableVertexAttribArray);
	OPENGL_FUNCTION_INITIALIZE(glGetAttribLocation);
	OPENGL_FUNCTION_INITIALIZE(glVertexAttribPointer);
	OPENGL_FUNCTION_INITIALIZE(glVertexAttribIPointer);
	OPENGL_FUNCTION_INITIALIZE(glBindVertexArray);
	OPENGL_FUNCTION_INITIALIZE(glGenVertexArrays);
	OPENGL_FUNCTION_INITIALIZE(glBindBuffer);
	OPENGL_FUNCTION_INITIALIZE(glGenBuffers);
	OPENGL_FUNCTION_INITIALIZE(glBufferData);
	OPENGL_FUNCTION_INITIALIZE(glGetShaderiv);
	OPENGL_FUNCTION_INITIALIZE(glDeleteShader);
	OPENGL_FUNCTION_INITIALIZE(glDeleteShader);
	OPENGL_FUNCTION_INITIALIZE(glGenerateMipmap);
	OPENGL_FUNCTION_INITIALIZE(glUniform3f);
	OPENGL_FUNCTION_INITIALIZE(glBufferSubData);
}

void
opengl_init(void)
{
	opengl_info();
	opengl_functions_load();
}
