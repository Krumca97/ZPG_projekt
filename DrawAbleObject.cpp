#include "DrawAbleObject.h"

DrawAbleObject::DrawAbleObject(Model& model, ShaderProgram& shader_program):model(model),shader_program(shader_program){}

DrawAbleObject::~DrawAbleObject() 
{
    clearTransformation();
}
void DrawAbleObject::addTransformation(Transformation* transformation)
{
	if(!transformation)
	{
		printf("transformace uakzuje na nullptr");
	}
	else
	{
		this->transformations.push_back(transformation);
	}
}

void DrawAbleObject::clearTransformation()
{
	for (Transformation* transformation : transformations) 
	{
		delete transformation;
	}
    transformations.clear();
}

void DrawAbleObject::update(float deltaTime)
{
	for(Transformation* transformation : transformations)
	{
		transformation->update(deltaTime);
	}
}

glm::mat4 DrawAbleObject::combiMatrix()
{
	glm::mat4 matrix(1.0f);
	for(Transformation* transformation : transformations)
	{
		matrix = matrix * transformation->getMatrix();
	}
	return matrix;
}


void DrawAbleObject::draw(glm::mat4& view, glm::mat4& proj)
{
	glm::mat4 matrix = combiMatrix();
	glm::mat4 MVP = proj* view * matrix;

	shader_program.use_shader_program();
	shader_program.setUniform("u_MVP",MVP);
	shader_program.setUniform("u_Model", matrix);
	model.draw_Model();
}