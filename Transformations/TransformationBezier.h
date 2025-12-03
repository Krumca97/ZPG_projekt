#pragma once
#include "TransformationComponent.h"
#include <vector>
#include <glm/glm.hpp>

class TransformationBezier : public TransformationComponent
{
public:
    TransformationBezier(const std::vector<glm::vec3> &ctrlPts, float speed);
    virtual glm::mat4 getMatrix() const override;

private:
    struct BezierSegment
    {
        glm::vec3 P0;
        glm::vec3 P1;
        glm::vec3 P2;
        glm::vec3 P3;
    };
    std::vector<BezierSegment> segments;
    std::vector<glm::vec3> controlPoints;

    float speed;
    int segmentCount = 0;

    void buildSegments();
};