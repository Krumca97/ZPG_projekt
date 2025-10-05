#pragma once
#include "Transformation.h"

class TransformationTranslate : public Transformation
{
public:
    TransformationTranslate(glm::vec3 direction,float speed);
    void update(float deltaTime) override;
    glm::mat4 getMatrix()const  override;
private:
    glm::vec3 translation;
    glm::vec3 direction;
    float speed;
};