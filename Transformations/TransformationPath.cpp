#include "TransformationPath.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

TransformationPath::TransformationPath(const std::vector<glm::vec3> &pts, float spd) : points(pts), speed(spd)
{
    this->currentSegment = 0;
    this->interpolation = 0.0f;
}

glm::mat4 TransformationPath::getMatrix() const
{
    if (!active || points.size() < 2)
    {
        return glm::mat4(1.0f);
    }

    glm::vec3 P0 = points[currentSegment];
    glm::vec3 P1 = points[(currentSegment + 1) % points.size()];

    // https://github.com/g-truc/glm/blob/master/glm/detail/func_common.inl 131
    glm::vec3 pos = glm::mix(P0, P1, interpolation);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    return model;
}

void TransformationPath::update(float dt)
{
    if (!active || points.size() < 2)
    {
        return;
    }

    interpolation += dt * speed;

    if (interpolation >= 1.0f)
    {
        interpolation = 0.0f;
        currentSegment = (currentSegment + 1) % points.size();
    }
}

void TransformationPath::resetPath(const std::vector<glm::vec3> &newPoints, float newSpeed)
{
    points = newPoints;
    speed = newSpeed;
    currentSegment = 0;
    interpolation = 0.0f;
    active = true;
}

void TransformationPath::setActive(bool a)
{
    active = a;
}
