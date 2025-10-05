#include "TransformationTranslate.h"

TransformationTranslate::TransformationTranslate(glm::vec3 direction,float speed) :translation(0.0f)
{
    this->direction = direction;
    this->speed = speed;
}

void TransformationTranslate::update(float deltaTime)
{
    this->translation += this->direction * this->speed * deltaTime;
    
    if(this->speed == 0)
    {
        this->translation = this->direction;
    }
}

glm::mat4 TransformationTranslate::getMatrix() const
{
    return glm::translate(glm::mat4(1.0f),this->translation);
};
