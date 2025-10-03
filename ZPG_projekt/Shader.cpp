#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>

Shader::Shader(const char* vertex_shader, const char* fragment_shader)
{
    this->vertex_shader = vertex_shader;
    this->fragment_shader = fragment_shader;
}

void Shader::compile_shader()
{
    //vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &this->vertex_shader, NULL);
	glCompileShader(vertexShader);

	//fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &this->fragment_shader, NULL);
	glCompileShader(fragmentShader);

	//uklid
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//kontrola
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
		exit(EXIT_FAILURE);
	}
}

void Shader::use_shader()
{
    
}