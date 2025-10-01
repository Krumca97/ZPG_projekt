#include "Shader_program.h"
#include <glm/gtc/type_ptr.hpp>
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
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	//uklid
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//kontrola
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}
	
}

void ShaderProgram::setMat4(const char* name, const glm::mat4& m)
{
	GLint loc = glGetUniformLocation(shaderProgram, name);
    if (loc != -1)
	{ 
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
	}
}

void ShaderProgram::setVec3(const char* name, const glm::vec3& v)
{
    GLint loc = glGetUniformLocation(shaderProgram, name);
    if (loc != -1)
	{ 
		glUniform3fv(loc, 1, glm::value_ptr(v));
	}
}

void ShaderProgram::set_shader()
{
	glUseProgram(shaderProgram);
}

