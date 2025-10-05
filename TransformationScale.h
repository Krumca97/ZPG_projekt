#pragma once
#include "Transformation.h"

class TransformationScale : public Transformation
{
public:
    TransformationScale(glm::vec3 scale,float speed);
    void update(float deltaTime) override;
    glm::mat4 getMatrix()const  override;
private:
    glm::vec3 scale;
    float speed;

};