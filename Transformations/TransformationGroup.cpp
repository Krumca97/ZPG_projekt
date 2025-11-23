#include "TransformationGroup.h"

TransformationGroup::~TransformationGroup()
{
    clear();
}

void TransformationGroup::update(float deltaTime)
{
    for(Transformation* transformation : transformations)
    {
        if(!transformation)
        {
            printf("Transformace je nullptr");
            continue;
        }
        else
        {
            transformation->update(deltaTime);
        }
    }
}

glm::mat4 TransformationGroup::getMatrix() const
{
    glm::mat4 matrix(1.f);
    for(Transformation* transformation : transformations)
    {
        if(!transformation)
        {
            continue;
        }
        else
        {
            matrix = matrix * transformation->getMatrix();
        }
    }
    return matrix;
}

void TransformationGroup::addTransformation(Transformation* transformation)
{
    this->transformations.push_back(transformation);
}

void TransformationGroup::clear()
{
    for( Transformation* transformation : transformations )
    {
        delete transformation;
    }
    transformations.clear();
}

