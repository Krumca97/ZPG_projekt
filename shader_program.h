#pragma once
#include <GL/glew.h>

//class ShaderProgram
//{
//public:
//	ShaderProgram(const char* vertex_shader, const char* fragment_shader);
//	ShaderProgram(GLuint shader_id);
//	~ShaderProgram();
//private:
//	GLuint shader_id;
//};

#pragma once
#include <GL/glew.h>

GLuint createShaderProgram(const char* vertex_shader, const char* fragment_shader);
