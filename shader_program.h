#pragma once
#include <GL/glew.h>
#include <iostream>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertex_shader, const char* fragment_shader);
	void set_shader();
private:
	GLuint shader_id;
};

