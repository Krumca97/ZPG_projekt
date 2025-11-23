#include <GLFW/glfw3.h>
#include "TransformationTranslate.h"

TransformationTranslate::TransformationTranslate(glm::vec3 direction,float speed) :translation(0.0f)
{
    this->direction = direction;
    this->speed = speed;
}

glm::mat4 TransformationTranslate::getMatrix() const
{

    return glm::translate(glm::mat4(1.0f),this->direction);
};

glm::vec3 TransformationTranslate::getDirection()
{
    return this->direction;
}

void TransformationTranslate::setDirection(glm::vec3 dir)
{
    this->direction = dir;
}