#pragma once
#include "../LightSubject.h"

class DirectionalLight : public LightSubject
{
public:
    DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);

    void notify() override;
private:
    glm::vec3 direction;
};
