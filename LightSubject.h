#pragma once
#include <iostream>
#include "IObserverLight.h"
#include <glm/glm.hpp>
#include <vector>

class ShaderProgram;

class LightSubject
{
  public:
    LightSubject(glm::vec3 position,glm::vec3 color,float intensity);

    void attach(IObserverLight* observer);
    void notify();
private:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
    std::vector<IObserverLight*> shaderProgramsObservers;
};