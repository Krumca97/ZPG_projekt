#include "LightSubject.h"

LightSubject::LightSubject(glm::vec3 position, glm::vec3 color, float intensity)
{
    this->position = position;
    this->color = color;
    this->intensity = intensity;
    this->transformations = new TransformationComposite();
};

void LightSubject::attach(IObserverLight *observer)
{
    this->shaderProgramsObservers.push_back(observer);
};

void LightSubject::notify()
{
    if (!active)
    {
        return;
    }

    glm::vec3 finalPos = position;
    if (transformations)
    {
        glm::mat4 matrix = combiMatrix();
        finalPos = glm::vec3(matrix * glm::vec4(0, 0, 0, 1));
    }

    for (IObserverLight *observer : shaderProgramsObservers)
    {
        observer->onLightChange(finalPos, color, intensity, 1);
    }
};

void LightSubject::addTransformation(TransformationComponent *transform)
{
    this->transformations->addTransformation(transform);
}

void LightSubject::clearTransformation()
{
    if (this->transformations)
    {
        delete this->transformations;
    }
    transformations = new TransformationComposite();
}

glm::mat4 LightSubject::combiMatrix()
{
    glm::mat4 matrix(1.0f);
    matrix = matrix * transformations->getMatrix();
    if (this->parentSpace)
    {
        matrix = parentSpace->combiMatrix() * matrix;
    }
    return matrix;
}

glm::vec3 LightSubject::getPosition()
{
    return this->position;
}

void LightSubject::setParentSpace(LightSubject *newParentSpace)
{
    this->parentSpace = newParentSpace;
    if (parentSpace)
    {
        this->parentSpace->childrenSpace.push_back(this);
    }
}
