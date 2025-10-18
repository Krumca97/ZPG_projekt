#include "Shader_program.h"
#include "DrawAbleObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>

ShaderProgram::ShaderProgram()
{
	this->shaderProgramId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	if(this->shaderProgramId)
	{
		glDeleteProgram(this->shaderProgramId);
	}
}

bool ShaderProgram::link(Shader& vertexShader, Shader& fragmentShader)
{
	vertexShader.compileShader();
	fragmentShader.compileShader();
	vertexShader.attachShader(this->shaderProgramId);
	fragmentShader.attachShader(this->shaderProgramId);
	glLinkProgram(this->shaderProgramId);

	//kontrola
	GLint status;
	glGetProgramiv(this->shaderProgramId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgramId, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	return true;
}

void ShaderProgram::useShaderProgram() 
{
	glUseProgram(shaderProgramId);
}

void ShaderProgram::setUniform(const char* name, int value)
{
	GLint loc = glGetUniformLocation(this->shaderProgramId, name);
    if (loc != -1) 
	{
		glUniform1i(loc,value);
	}
}

void ShaderProgram::setUniform(const char* name, float value)
{
	GLint loc = glGetUniformLocation(this->shaderProgramId, name);
    if (loc != -1) 
	{
		glUniform1f(loc,value);
	}
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& vector)
{
	GLint loc = glGetUniformLocation(this->shaderProgramId, name);
    if (loc != -1) 
	{
		glUniform3fv(loc,1,glm::value_ptr(vector));
	}
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& matrix)
{
	GLint loc = glGetUniformLocation(this->shaderProgramId, name);
    if (loc != -1) 
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}

void ShaderProgram::onCameraChange(glm::mat4 view, glm::mat4 proj,glm::vec3 cameraPos)
{
	useShaderProgram();
	setUniform("viewMatrix",view);
	setUniform("projectionMatrix",proj);
	setUniform("viewPos", cameraPos);
}

void ShaderProgram::onLightChange(glm::vec3 position,glm::vec3 color,float intensity)
{
	useShaderProgram();
	setUniform("lightPosition", position);
	setUniform("lightColor",color);
	setUniform("lightIntensity",intensity);
}

void ShaderProgram::setObjectColor(glm::vec3 color)
{
	 useShaderProgram();
    setUniform("objectColor", color);
}
