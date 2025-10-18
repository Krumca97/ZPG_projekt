#pragma once
#include "TransformationComponent.h"

class TransformationRotate : public TransformationComponent
{
public:
    TransformationRotate(glm::vec3 axis,float angle,float speed);
    glm::mat4 getMatrix()const  override;
private:
    glm::vec3 axis;
    float angle;
    float speed;
};

