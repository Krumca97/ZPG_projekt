#include "shader_program.h"
#include <cstddef>

//ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader)
//{
//	//vertex shader
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
//	glCompileShader(vertexShader);
//
//	//fragment shader
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
//	glCompileShader(fragmentShader);
//
//	//nastarovani shaderu
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, fragmentShader);
//	glAttachShader(shaderProgram, vertexShader);
//	glLinkProgram(shaderProgram);
//}
//
//ShaderProgram::ShaderProgram(unsigned int shader_id_)
//{
//	shader_id = shader_id_;
//}
//
//ShaderProgram::~ShaderProgram()
//{
//	glDeleteProgram(shader_id);
//}

GLuint createShaderProgram(const char* vertex_shader, const char* fragment_shader)
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
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}