#include "AmbientLight.h"

AmbientLight::AmbientLight(glm::vec3 color, float intensity) : LightSubject(glm::vec3(0.0f), color, intensity) {}

void AmbientLight::notify()
{
    for (IObserverLight *observer : shaderProgramsObservers)
    {
        observer->onLightChange(glm::vec3(0.0f), color, intensity, 2);
    }
}
