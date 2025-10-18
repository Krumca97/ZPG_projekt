#pragma once
#include "DrawAbleObject.h"
#include "Shader_program.h"

class Scene
{
public:
    Scene(glm::mat4& view,glm::mat4& proj);
    ~Scene();

    void addObject(DrawAbleObject* object);
    void addShaderProgram(ShaderProgram* shaderProgram);

    void setView(glm::mat4& view);
    void setProjection(glm::mat4& proj);
    
    void drawScene();

private:
    glm::mat4 view;
    glm::mat4 proj;

    std::vector<DrawAbleObject*> drawAbleObjects;
    std::vector<ShaderProgram*> shaderPrograms;

};