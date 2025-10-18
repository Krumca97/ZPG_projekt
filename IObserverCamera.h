#pragma once
#include <glm/glm.hpp>

class IObserverCamera
{
public:
    virtual ~IObserverCamera() = default;
    virtual void onCameraChange(glm::mat4 viewMatrix,glm::mat4 projMatrix,glm::vec3 cameraPos) = 0;
};