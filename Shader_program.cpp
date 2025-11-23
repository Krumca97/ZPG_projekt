#include "Shader_program.h"
#include "DrawAbleObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>

ShaderProgram::ShaderProgram()
{
	this->shaderProgramId = glCreateProgram();
	this->lightIndex = 0;
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

	//Check
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
	glUseProgram(0);
}

void ShaderProgram::onLightChange(glm::vec3 position,glm::vec3 color,float intensity,int type)
{

    for (size_t i = 0; i < lightPositions.size(); ++i)
    {
        if (lightTypes[i] == type && glm::distance(lightPositions[i], position) < 0.01f)
        {
            lightPositions[i] = position;
            lightColors[i] = color;
            lightIntensities[i] = intensity;
            return;
        }
    }

    lightPositions.push_back(position);
    lightColors.push_back(color);
    lightIntensities.push_back(intensity);
    lightTypes.push_back(type);

}

void ShaderProgram::onSpotLightChange(glm::vec3 position, glm::vec3 direction,glm::vec3 color, float intensity)
{
    useShaderProgram();

    setUniform("spotLightPosition", position);
    setUniform("spotLightDirection", glm::normalize(direction));
    setUniform("spotLightColor", color);
    setUniform("spotLightIntensity", intensity);

	glUseProgram(0);

}

void ShaderProgram::setObjectColor(glm::vec3 color)
{
	useShaderProgram();
    setUniform("objectColor", color);
	glUseProgram(0);
}

void ShaderProgram::resetLight()
{
	this->lightPositions.clear();
    this->lightColors.clear();
    this->lightIntensities.clear();
	this->lightTypes.clear();
	this->lightIndex = 0;
}

void ShaderProgram::uploadLights()
{
    useShaderProgram();
	int count = static_cast<int>(lightPositions.size());
	if (count == 0)
    {
        glUniform1i(glGetUniformLocation(shaderProgramId, "lightCount"), 0);
        return;
    }

    glUniform1i(glGetUniformLocation(shaderProgramId, "lightCount"), count);
    glUniform3fv(glGetUniformLocation(shaderProgramId, "lightPosition"),(GLsizei)lightPositions.size(), glm::value_ptr(lightPositions[0]));
    glUniform3fv(glGetUniformLocation(shaderProgramId, "lightColor"),(GLsizei)lightColors.size(), glm::value_ptr(lightColors[0]));
    glUniform1fv(glGetUniformLocation(shaderProgramId, "lightIntensity"),(GLsizei)lightIntensities.size(), lightIntensities.data());
	glUniform1iv(glGetUniformLocation(shaderProgramId, "lightType"), count, lightTypes.data());
	glUseProgram(0);
}

void ShaderProgram::setLightIndex(int lightIndex)
{
	this->lightIndex = lightIndex;
}
