#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float intensity): LightSubject(position, color, intensity){}

void PointLight::notify()
{
    for (IObserverLight* observer : shaderProgramsObservers)
    {
        observer->onLightChange(position, color, intensity, 1);
    }
}