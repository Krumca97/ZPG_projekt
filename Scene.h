#pragma once
#include "DrawAbleObject.h"
#include "Shader_program.h"
#include "LightSubject.h"
#include "CameraSubject.h"
#include "Controller.h"
#include <vector>
#include <glm/glm.hpp>
#include <ctime>

struct Firefly 
{
    DrawAbleObject* sphere;
    LightSubject* light;
    glm::vec3 position;
    glm::vec3 direction;
    double lastChangeDir;
    double lastUpdate;
};

class Scene
{
public:
    Scene(glm::mat4& view,glm::mat4& proj);
    ~Scene();

    void addObject(DrawAbleObject* object);
    void addShaderProgram(ShaderProgram* shaderProgram);
    void addLight(LightSubject* light);

    void setView(glm::mat4& view);
    void setProjection(glm::mat4& proj);
    
    void updateLights(bool reset);
    void drawScene();

    void buildFireflies(Model* model, ShaderProgram* shader,Scene* scene);
    void updateFireflies();

    void setCamera(float ratio);
    CameraSubject* getCamera();
    void updateCamera(GLFWwindow* window, float deltaTime);

    Controller* getController();

private:
    glm::mat4 view;
    glm::mat4 proj;

    CameraSubject* camera = nullptr;
    Controller* controller = nullptr;

    std::vector<DrawAbleObject*> drawAbleObjects;
    std::vector<ShaderProgram*> shaderPrograms;
    std::vector<LightSubject*> lights;
    std::vector<LightSubject*> fireflies;
    std::vector<Firefly> firefliesData;
};