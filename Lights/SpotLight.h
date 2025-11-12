#pragma once
#include <GL/glew.h>
#include "../LightSubject.h"
#include "../CameraSubject.h"            
#include "../Shader_program.h"


class SpotLight : public LightSubject
{
public:
    SpotLight(glm::vec3 color, float intensity);
    void attachCamera(CameraSubject* cam);
    void toggle();
    void notify() override;

private:
    CameraSubject* camera = nullptr;
    glm::vec3 direction;
};
