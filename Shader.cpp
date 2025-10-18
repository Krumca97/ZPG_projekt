#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Shader::Shader(const char* source,GLenum type)
{
    this->type = type;
	this->shaderId = glCreateShader(type);

	FILE* file;
	long size =0;
	char* shaderContent = nullptr;

	file = fopen(source,"rb");
	if(file == NULL)
	{
		fprintf(stderr,"Cant load shader file");
		return;
	}

	fseek(file,0L,SEEK_END);
	size = ftell(file);
	rewind(file);

	shaderContent = (char*)malloc(size + 1);
	fread(shaderContent,1,size,file);
	shaderContent[size] = '\0';
	fclose(file);

	this->source = shaderContent;
}

Shader::~Shader()
{
	if(this->shaderId)
	{
		glDeleteShader(this->shaderId);
	}
}

bool Shader::compileShader()
{
	glShaderSource(this->shaderId, 1, &source, NULL);
	glCompileShader(this->shaderId);

	//kontrola
	GLint status;
	glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(this->shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(this->shaderId, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}

	return true;
}

void Shader::attachShader(GLuint shaderProgram)
{
	glAttachShader(shaderProgram, this->shaderId);
}


