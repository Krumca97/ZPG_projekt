#pragma once
#include "TransformationComponent.h"

class TransformationTranslate : public TransformationComponent
{
public:
    TransformationTranslate(glm::vec3 direction,float speed);
    glm::mat4 getMatrix()const  override;
    glm::vec3 getDirection();
    void setDirection(glm::vec3 dir);
private:
    glm::vec3 translation;
    glm::vec3 direction;
    float speed;
};