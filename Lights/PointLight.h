#pragma once
#include "../LightSubject.h"

class PointLight : public LightSubject
{
public:
    PointLight(glm::vec3 position, glm::vec3 color, float intensity);

    void notify() override; 
};
