#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Shader.h"
#include "IObserverCamera.h"
#include "IObserverLight.h"
#include <vector>

class ShaderProgram : public IObserverCamera, public IObserverLight
{
public:
	ShaderProgram();
	~ShaderProgram();

	bool link(Shader &vertex_shader, Shader &fragment_shader);
	void useShaderProgram();

	void setUniform(const char *name, int value);
	void setUniform(const char *name, float value);
	void setUniform(const char *name, const glm::mat4 &matrix);
	void setUniform(const char *name, const glm::vec3 &vector);

	void update(glm::mat4 view, glm::mat4 proj);

	void onCameraChange(glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos) override;
	void onLightChange(glm::vec3 position, glm::vec3 color, float intensity, int type) override;
	void onSpotLightChange(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity) override;
	void setObjectColor(glm::vec3 color) override;
	void resetLight();
	void uploadLights();
	void setLightIndex(int lightIndex);

private:
	GLuint shaderProgramId;
	int lightIndex;
	std::vector<glm::vec3> lightPositions;
	std::vector<glm::vec3> lightColors;
	std::vector<float> lightIntensities;
	std::vector<int> lightTypes;
	std::vector<glm::vec3> lightDirections;
	std::vector<float> lightAngles;
};
