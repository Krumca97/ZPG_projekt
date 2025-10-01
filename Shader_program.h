#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertex_shader, const char* fragment_shader);
	void set_shader();

	void setMat4(const char* name,const glm::mat4& m);
	void setVec3(const char* name,const glm::vec3& v);
	
private:
	GLuint shaderProgram;
};

