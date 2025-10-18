#pragma once
#include <glm/glm.hpp>

class IObserverLight
{
public:
    virtual ~IObserverLight() = default;
    virtual void onLightChange(glm::vec3 position, glm::vec3 color, float intensity) = 0;
    virtual void setObjectColor(glm::vec3 color) = 0;
};