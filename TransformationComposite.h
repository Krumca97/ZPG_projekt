#pragma once
#include <vector>
#include <iostream>
#include "TransformationComponent.h"

class TransformationComposite: public TransformationComponent
{
public:
    TransformationComposite() = default;
    ~TransformationComposite();
    glm::mat4 getMatrix() const override;
    
    void addTransformation(TransformationComponent* transformation);
    void clear();
private:
    std::vector<TransformationComponent*> transformations;
};