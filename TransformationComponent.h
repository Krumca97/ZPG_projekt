#pragma once
#include <glm/ext/matrix_transform.hpp>


class TransformationComponent
{
public:
    virtual ~TransformationComponent() = default;
    virtual glm::mat4 getMatrix() const = 0;    
};