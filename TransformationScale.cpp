#include "TransformationScale.h"

TransformationScale::TransformationScale(glm::vec3 scale,float speed)
{
    this->scale = scale;
    this->speed = speed;
}

void TransformationScale::update(float deltaTime)
{
    this->scale += this->speed * deltaTime;
}

glm::mat4 TransformationScale::getMatrix() const
{
    return glm::scale(glm::mat4(1.0f),this->scale);
}