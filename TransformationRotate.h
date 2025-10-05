#pragma once
#include "Transformation.h"

class TransformationRotate : public Transformation
{
public:
    TransformationRotate(glm::vec3 axis,float angle,float speed);
    void update(float deltaTime) override;
    glm::mat4 getMatrix()const  override;
private:
    glm::vec3 axis;
    float angle;
    float speed;
};

