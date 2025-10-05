#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>

Shader::Shader(const char* source,GLenum type)
{
    this->type = type;
	this->source = source;
	this->shader_id = glCreateShader(type);
}

Shader::~Shader()
{
	if(this->shader_id)
	{
		glDeleteShader(this->shader_id);
	}
}

bool Shader::compile_shader()
{
	glShaderSource(this->shader_id, 1, &source, NULL);
	glCompileShader(this->shader_id);

	//kontrola
	GLint status;
	glGetShaderiv(this->shader_id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(this->shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(this->shader_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}

	return true;
}

void Shader::attachShader(GLuint shaderProgram)
{
	glAttachShader(shaderProgram, this->shader_id);
}


