#pragma once
#include "TransformationComponent.h"

class TransformationScale : public TransformationComponent
{
public:
    TransformationScale(glm::vec3 scale,float speed);
    glm::mat4 getMatrix()const  override;
private:
    glm::vec3 scale;
    float speed;

};