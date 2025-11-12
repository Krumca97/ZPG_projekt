#pragma once 
#include "../LightSubject.h"

class AmbientLight : public LightSubject
{
public:
    AmbientLight(glm::vec3 color, float intensity);
    void notify() override;
};

