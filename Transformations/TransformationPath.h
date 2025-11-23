#pragma once
#include "TransformationComponent.h"
#include <vector>
#include <glm/glm.hpp>

class TransformationPath : public TransformationComponent
{
public:
    TransformationPath(const std::vector<glm::vec3>& pts, float spd);

    virtual glm::mat4 getMatrix() const override;
    void update(float dt);
    void resetPath(const std::vector<glm::vec3>& newPoints, float newSpeed);
    void setActive(bool a) { active = a; }
private:
    std::vector<glm::vec3> points;
    int currentSegment = 0;
    float interpolation = 0.0f;
    float speed;

    bool active = true;
};