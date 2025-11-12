#include "DrawAbleObject.h"

DrawAbleObject::DrawAbleObject(Model& model, ShaderProgram& shaderProgram):model(model),shaderProgram(shaderProgram){
	transformations = new TransformationComposite();
	material = Material(glm::vec3(0.1f),glm::vec3(0.8f),glm::vec3(0.0f),32.0f);
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

void DrawAbleObject::clearTransformation()
{
	if (this->transformations)
	{
		delete this->transformations;
	}
	transformations = new TransformationComposite();
}


void DrawAbleObject::draw(glm::mat4& view, glm::mat4& proj)
{
	glm::mat4 matrix = combiMatrix();
	shaderProgram.useShaderProgram();
    shaderProgram.setUniform("modelMatrix", matrix);
    shaderProgram.setUniform("viewMatrix", view);
    shaderProgram.setUniform("projectionMatrix", proj);
    
	if (useTexture && textureID != 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        shaderProgram.setUniform("textureUnitID", 0);
        shaderProgram.setUniform("useTexture", 1);
		shaderProgram.setUniform("uvScale", uvScale);
    }
    else
    {
        shaderProgram.setUniform("useTexture", 0);
    }
	uploadMaterial();
	
	model.drawModel();
	glUseProgram(0);
}

void DrawAbleObject::setMaterial(const Material& mat)
{
	this->material = mat;
}

void DrawAbleObject::uploadMaterial()
{
	shaderProgram.setUniform("material.ra", material.ra);
	shaderProgram.setUniform("material.rd", material.rd);
	shaderProgram.setUniform("material.rs", material.rs);
	shaderProgram.setUniform("material.h",  material.h);
}

void DrawAbleObject::setTexture(GLuint texID)
{
    this->textureID = texID;
    this->useTexture = true;
}

void DrawAbleObject::setUvScale(float scale)
{
	this->uvScale = scale;
}