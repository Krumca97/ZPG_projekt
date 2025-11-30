#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 color, float intensity) : LightSubject(glm::vec3(0.0f), color, intensity) {}

void SpotLight::toggle()
{
    active = !active;
}

void SpotLight::attachCamera(CameraSubject *cam)
{
    this->camera = cam;
}

void SpotLight::notify()
{
    glm::vec3 finalPosition = position;
    glm::vec3 finalDirection = direction;

    if (camera)
    {
        finalDirection = glm::normalize(camera->getForward() - glm::vec3(0.0f, 0.15f, 0.0f));
        finalPosition = camera->getPosition() + finalDirection * 0.4f;
    }

    for (IObserverLight *observer : shaderProgramsObservers)
    {
        observer->onSpotLightChange(finalPosition, finalDirection, color, active ? intensity : 0.0f);
    }
}
