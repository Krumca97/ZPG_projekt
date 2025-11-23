#include <GLFW/glfw3.h>
#include "TransformationScale.h"

TransformationScale::TransformationScale(glm::vec3 scale,float speed)
{
    this->scale = scale;
    this->speed = speed;
}

glm::mat4 TransformationScale::getMatrix() const
{

    return glm::scale(glm::mat4(1.0f),this->scale);
}