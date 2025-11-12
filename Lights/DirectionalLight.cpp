#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity) : LightSubject(glm::vec3(0), color, intensity), direction(glm::normalize(direction)) {}

void DirectionalLight::notify()
{
    for (IObserverLight* observer : shaderProgramsObservers)
    {
        observer->onLightChange(direction, color, intensity,0);
    }
}