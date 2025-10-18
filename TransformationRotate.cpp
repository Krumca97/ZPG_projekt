#include <GLFW/glfw3.h>
#include "TransformationRotate.h"

TransformationRotate::TransformationRotate(glm::vec3 axis, float angle,float speed)
{
    this->axis = axis;
    this->angle = angle;
    this->speed = speed;
};


glm::mat4 TransformationRotate::getMatrix() const
{
   if (speed == 0.0f)
    {
        return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    }
    else
    {
        float time = glfwGetTime();
        float currentAngle = angle + speed * time;
        return glm::rotate(glm::mat4(1.0f), glm::radians(currentAngle), axis);
    }
}