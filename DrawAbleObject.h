#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include "Model.h"
#include "Shader_program.h"
#include "TransformationComposite.h"
#include <vector>
#include "Material.h"

class DrawAbleObject
{
public:
	DrawAbleObject(Model& model, ShaderProgram& shader_program);
	~DrawAbleObject() =default;
	DrawAbleObject(DrawAbleObject&) = delete;
    DrawAbleObject& operator=(DrawAbleObject&) = delete;

	void addTransformation(TransformationComponent* transformation);

	void setParentSpace(DrawAbleObject* newParentSpace);	

	void clearTransformation();

	void draw(glm::mat4& view, glm::mat4& proj);

	void setMaterial(const Material& material);
	void uploadMaterial();
	void setTexture(GLuint texID);
	void setUvScale(float scale);

private:
	Model& model;
	ShaderProgram& shaderProgram;
	TransformationComposite* transformations;
	glm::mat4 combiMatrix();
	DrawAbleObject* parentSpace = nullptr;
	std::vector<DrawAbleObject*> childrenSpace;
	Material material;
	GLuint textureID = 0;
	bool useTexture = false;
	float uvScale = 1.0f;
};
