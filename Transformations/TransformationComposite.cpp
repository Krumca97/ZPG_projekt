#include "TransformationComposite.h"

TransformationComposite::~TransformationComposite()
{
    clear();
}

glm::mat4 TransformationComposite::getMatrix() const
{
    glm::mat4 matrix(1.f);
    for (TransformationComponent* transformation : transformations)
    {
        if (!transformation) 
        {
            continue;
        }

        const TransformationComposite* group = dynamic_cast<const TransformationComposite*>(transformation);
        if (group)
        {
            matrix *= group->getMatrix();
        }
        else
        {
            matrix *= transformation->getMatrix();
        }
    }
    return matrix;
}

void TransformationComposite::addTransformation(TransformationComponent* transformation)
{
    this->transformations.push_back(transformation);
}

void TransformationComposite::clear()
{
    for( TransformationComponent* transformation : transformations )
    {
        delete transformation;
    }
    transformations.clear();
}

