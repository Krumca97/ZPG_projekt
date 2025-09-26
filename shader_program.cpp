#include "shader_program.h"
#include <cstddef>

ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader)
{
	//vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	//fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);

	//nastarovani shaderu
	shader_id = glCreateProgram();
	glAttachShader(shader_id, fragmentShader);
	glAttachShader(shader_id, vertexShader);
	glLinkProgram(shader_id);

	//uklid
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//kontrola nevim jak zatim
	GLint status;
	glGetProgramiv(shader_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shader_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void ShaderProgram::set_shader()
{
	glUseProgram(shader_id);
}

