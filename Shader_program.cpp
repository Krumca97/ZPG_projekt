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
	if (this->shaderProgramId)
	{
		glDeleteProgram(this->shaderProgramId);
	}
}

bool ShaderProgram::link(Shader &vertexShader, Shader &fragmentShader)
{
	vertexShader.compileShader();
	fragmentShader.compileShader();
	vertexShader.attachShader(this->shaderProgramId);
	fragmentShader.attachShader(this->shaderProgramId);
	glLinkProgram(this->shaderProgramId);

	// Check
	GLint status;
	glGetProgramiv(this->shaderProgramId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
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

void ShaderProgram::setUniform(const char *name, int value)
{
	GLint loc = glGetUniformLocation(this->shaderProgramId, name);
	if (loc != -1)
	{
		glUniform1i(loc, value);
	}
}

void ShaderProgram::setUniform(const char *name, float value)
{
	GLint loc = glGetUniformLocation(this->shaderProgramId, name);
	if (loc != -1)
	{
		glUniform1f(loc, value);
	}
}

void ShaderProgram::setUniform(const char *name, const glm::vec3 &vector)
{
	GLint loc = glGetUniformLocation(this->shaderProgramId, name);
	if (loc != -1)
	{
		glUniform3fv(loc, 1, glm::value_ptr(vector));
	}
}

void ShaderProgram::setUniform(const char *name, const glm::mat4 &matrix)
{
	GLint loc = glGetUniformLocation(this->shaderProgramId, name);
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}

void ShaderProgram::onCameraChange(glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos)
{
	useShaderProgram();
	setUniform("viewMatrix", view);
	setUniform("projectionMatrix", proj);
	setUniform("viewPos", cameraPos);
	glUseProgram(0);
}

void ShaderProgram::onLightChange(glm::vec3 position, glm::vec3 color, float intensity, int type)
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
	glm::vec3 defaultDir = glm::vec3(0, -1, 0);
	float defaultAngle = 40.0f;

	lightPositions.push_back(position);
	lightColors.push_back(color);
	lightIntensities.push_back(intensity);
	lightTypes.push_back(type);
	lightDirections.push_back(defaultDir);
	lightAngles.push_back(defaultAngle);
}

void ShaderProgram::onSpotLightChange(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity)
{
	int type = 3;

	for (size_t i = 0; i < lightTypes.size(); ++i)
	{
		if (lightTypes[i] == 3)
		{
			lightPositions[i] = position;
			lightDirections[i] = glm::normalize(direction);
			lightColors[i] = color;
			lightIntensities[i] = intensity;
			lightAngles[i] = 40.0f;
			return;
		}
	}

	lightTypes.push_back(type);
	lightPositions.push_back(position);
	lightDirections.push_back(glm::normalize(direction));
	lightColors.push_back(color);
	lightIntensities.push_back(intensity);
	lightAngles.push_back(40.0f);
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

	int count = (int)lightPositions.size();
	glUniform1i(glGetUniformLocation(shaderProgramId, "lightCount"), count);

	if (count == 0)
	{
		glUseProgram(0);
		return;
	}

	for (int i = 0; i < count; i++)
	{
		std::string base = "lights[" + std::to_string(i) + "]";

		glUniform1i(glGetUniformLocation(shaderProgramId, (base + ".type").c_str()), lightTypes[i]);
		glUniform3fv(glGetUniformLocation(shaderProgramId, (base + ".position").c_str()), 1, glm::value_ptr(lightPositions[i]));
		glUniform3fv(glGetUniformLocation(shaderProgramId, (base + ".direction").c_str()), 1, glm::value_ptr(lightDirections[i]));
		glUniform3fv(glGetUniformLocation(shaderProgramId, (base + ".color").c_str()), 1, glm::value_ptr(lightColors[i]));
		glUniform1f(glGetUniformLocation(shaderProgramId, (base + ".intensity").c_str()), lightIntensities[i]);
		glUniform1f(glGetUniformLocation(shaderProgramId, (base + ".angle").c_str()), lightAngles[i]);
	}

	glUseProgram(0);
}

void ShaderProgram::setLightIndex(int lightIndex)
{
	this->lightIndex = lightIndex;
}
