#pragma once
#include <vector>
#include <iostream>
#include "Transformation.h"

class TransformationGroup: public Transformation
{
public:
    TransformationGroup() = default;
    ~TransformationGroup();
    void update(float deltaTime) override;
    glm::mat4 getMatrix() const override;
    
    void addTransformation(Transformation* transformation);
    void clear();
private:
    std::vector<Transformation*> transformations;
};