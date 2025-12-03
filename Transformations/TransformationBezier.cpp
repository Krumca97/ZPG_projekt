#include <GLFW/glfw3.h>
#include "TransformationBezier.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

TransformationBezier::TransformationBezier(const std::vector<glm::vec3> &ctrlPts, float spd) : controlPoints(ctrlPts), speed(spd)
{
    buildSegments();
}

glm::mat4 TransformationBezier::getMatrix() const
{
    if (this->segments.empty())
    {
        return glm::mat4(1.0f);
    }

    float timeNow = glfwGetTime();
    float timeGlobal = fmod(timeNow * this->speed, (float)this->segmentCount);

    int currentSegmentIndex = (int)timeGlobal;
    float t = timeGlobal - currentSegmentIndex;

    const BezierSegment &seg = this->segments[currentSegmentIndex];

    float u = 1.0f - t;

    glm::vec3 t1 = glm::vec3((u * u * u) * seg.P0);
    glm::vec3 t2 = glm::vec3(3.0f * (u * u) * t * seg.P1);
    glm::vec3 t3 = glm::vec3(3.0f * u * (t * t) * seg.P2);
    glm::vec3 t4 = glm::vec3((t * t * t) * seg.P3);
    glm::vec4 T = glm::vec4(t1 + t2 + t3 + t4, 0.0f);

    glm::vec3 dT1 = 3.0f * u * u * glm::vec3(seg.P1 - seg.P0);
    glm::vec3 dT2 = 6.0f * u * t * glm::vec3(seg.P2 - seg.P1);
    glm::vec3 dT3 = 3.0f * t * t * glm::vec3(seg.P3 - seg.P2);
    glm::vec4 dT = glm::vec4(dT1 + dT2 + dT3, 0.0f);

    glm::vec3 pos = glm::vec3(T);
    glm::vec3 tangent = glm::normalize(dT);

    glm::vec3 forward = glm::normalize(glm::vec3(tangent));
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(worldUp, forward));
    glm::vec3 up = glm::cross(forward, right);

    glm::mat4 rotation(1.0f);
    rotation[0] = glm::vec4(right, 0.0f);
    rotation[1] = glm::vec4(up, 0.0f);
    rotation[2] = glm::vec4(forward, 0.0f);

    return glm::translate(glm::mat4(1.0f), pos) * rotation;
}

void TransformationBezier::buildSegments()
{
    segments.clear();

    int N = controlPoints.size();

    if (N < 4)
    {
        segmentCount = 0;
        return;
    }

    if ((N - 1) % 3 != 0)
    {
        segmentCount = (N - 1) / 3;
    }
    else
    {
        segmentCount = (N - 1) / 3;
    }

    for (int s = 0; s < segmentCount; s++)
    {
        int i = s * 3;
        BezierSegment seg;

        seg.P0 = controlPoints[i + 0];
        seg.P1 = controlPoints[i + 1];
        seg.P2 = controlPoints[i + 2];
        seg.P3 = controlPoints[i + 3];

        segments.push_back(seg);
    }
}
