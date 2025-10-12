#include "Shader_program.h"
#include "DrawAbleObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>

ShaderProgram::ShaderProgram()
{
	this->shaderProgram_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	if(this->shaderProgram_id)
	{
		glDeleteProgram(this->shaderProgram_id);
	}
}

bool ShaderProgram::link(Shader& vertex_shader, Shader& fragment_shader)
{
	vertex_shader.compile_shader();
	fragment_shader.compile_shader();
	vertex_shader.attachShader(this->shaderProgram_id);
	fragment_shader.attachShader(this->shaderProgram_id);
	glLinkProgram(this->shaderProgram_id);

	//kontrola
	GLint status;
	glGetProgramiv(this->shaderProgram_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	return true;
}

void ShaderProgram::use_shader_program() 
{
	glUseProgram(shaderProgram_id);
}

void ShaderProgram::setUniform(const char* name, int value)
{
	GLint loc = glGetUniformLocation(this->shaderProgram_id, name);
    if (loc != -1) 
	{
		glUniform1i(loc,value);
	}
}

void ShaderProgram::setUniform(const char* name, float value)
{
	GLint loc = glGetUniformLocation(this->shaderProgram_id, name);
    if (loc != -1) 
	{
		glUniform1f(loc,value);
	}
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& vector)
{
	GLint loc = glGetUniformLocation(this->shaderProgram_id, name);
    if (loc != -1) 
	{
		glUniform3fv(loc,1,glm::value_ptr(vector));
	}
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& matrix)
{
	GLint loc = glGetUniformLocation(this->shaderProgram_id, name);
    if (loc != -1) 
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}


void ShaderProgram::update(glm::mat4 view, glm::mat4 proj)
{
	use_shader_program();
	setUniform("viewMatrix",view);
	setUniform("projectionMatrix",proj);
}


