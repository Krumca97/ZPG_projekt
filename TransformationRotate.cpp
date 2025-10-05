#include "TransformationRotate.h"

TransformationRotate::TransformationRotate(glm::vec3 axis, float angle,float speed)
{
    this->axis = axis;
    this->angle = angle;
    this->speed = speed;
};

void TransformationRotate::update(float deltaTime)
{
    this->angle += this->speed *deltaTime;
}

glm::mat4 TransformationRotate::getMatrix() const
{
    return glm::rotate(glm::mat4(1.0f),angle,axis);
}