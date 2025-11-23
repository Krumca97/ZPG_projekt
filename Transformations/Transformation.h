#pragma once
#include <glm/ext/matrix_transform.hpp>


class Transformation
{
public:
    virtual ~Transformation() = default;
    virtual void update(float deltaTime) = 0;
    virtual glm::mat4 getMatrix() const = 0;    
};