#include "Shader_program.h"
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>

ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader)
{	
	this->vertex_shader = vertex_shader;
	this->fragment_shader = fragment_shader;
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

void ShaderProgram::use_shader_program()
{
	glUseProgram(shaderProgram);
}

//tohle musi byt nekde tady 
{
	//nastarovani shaderu
	shader_id = glCreateProgram();
	glAttachShader(shader_id, fragmentShader);
	glAttachShader(shader_id, vertexShader);
	glLinkProgram(shader_id);
}