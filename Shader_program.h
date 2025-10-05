#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	bool link(Shader& vertex_shader, Shader& fragment_shader);
	void use_shader_program();

	void setUniform(const char* name,int value);
	void setUniform(const char* name,float value);
	void setUniform(const char* name,const glm::mat4& matrix);
	void setUniform(const char* name,const glm::vec3& vector);
private:
	GLuint shaderProgram_id;
};

