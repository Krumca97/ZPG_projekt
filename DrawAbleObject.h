#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include "Model.h"
#include "Shader_program.h"
#include "TransformationComposite.h"
#include <vector>

class DrawAbleObject
{
public:
	DrawAbleObject(Model& model, ShaderProgram& shader_program);
	~DrawAbleObject() =default;
	DrawAbleObject(DrawAbleObject&) = delete;
    DrawAbleObject& operator=(DrawAbleObject&) = delete;

	void addTransformation(TransformationComponent* transformation);

	void setParentSpace(DrawAbleObject* newParentSpace);	

	void draw(glm::mat4& view, glm::mat4& proj);

private:
	Model& model;
	ShaderProgram& shaderProgram;
	TransformationComposite* transformations;
	glm::mat4 combiMatrix();
	DrawAbleObject* parentSpace = nullptr;
	std::vector<DrawAbleObject*> childrenSpace;
};
