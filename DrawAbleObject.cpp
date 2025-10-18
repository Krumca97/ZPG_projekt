#include "DrawAbleObject.h"

DrawAbleObject::DrawAbleObject(Model& model, ShaderProgram& shaderProgram):model(model),shaderProgram(shaderProgram){
	transformations = new TransformationComposite();
}

void DrawAbleObject::addTransformation(TransformationComponent* transformation)
{
	if(!transformation)
	{
		printf("transformace uakzuje na nullptr");
	}
	else
	{
		transformations->addTransformation(transformation);
	}
}

glm::mat4 DrawAbleObject::combiMatrix()
{
	glm::mat4 matrix(1.0f);
	matrix = matrix * transformations->getMatrix();
	if (this->parentSpace) 
	{
        matrix = parentSpace->combiMatrix() * matrix;
    }
	return matrix;
}

void DrawAbleObject::setParentSpace(DrawAbleObject* newParentSpace)
{
	this->parentSpace = newParentSpace;
	if(parentSpace)
	{
		this->parentSpace->childrenSpace.push_back(this);
	}
}


void DrawAbleObject::draw(glm::mat4& view, glm::mat4& proj)
{
	glm::mat4 matrix = combiMatrix();
	shaderProgram.useShaderProgram();
    shaderProgram.setUniform("modelMatrix", matrix);
    shaderProgram.setUniform("viewMatrix", view);
    shaderProgram.setUniform("projectionMatrix", proj);
    model.drawModel();
}