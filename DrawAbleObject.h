#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include "Model.h"
#include "Shader_program.h"
#include "Transformation.h"

class DrawAbleObject
{
public:
	DrawAbleObject(Model& model, ShaderProgram& shader_program);
	~DrawAbleObject();
	DrawAbleObject(DrawAbleObject&) = delete;
    DrawAbleObject& operator=(DrawAbleObject&) = delete;

	void addTransformation(Transformation* transformation);
	void clearTransformation();

	void update(float deltaTime);
	void draw(glm::mat4& view, glm::mat4& proj);

private:
	Model& model;
	ShaderProgram& shader_program;
	std::vector<Transformation*> transformations;
	glm::mat4 combiMatrix();

};
