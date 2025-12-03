#pragma once
#include "DrawAbleObject.h"
#include "Shader_program.h"
#include "LightSubject.h"
#include "CameraSubject.h"
#include "Controller.h"
#include "Lights/AmbientLight.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include <vector>
#include <glm/glm.hpp>
#include <ctime>
#include "Skybox.h"

struct Firefly
{
    DrawAbleObject *sphere;
    LightSubject *light;
    glm::vec3 position;
    glm::vec3 direction;
    double lastChangeDir;
    double lastUpdate;
};

enum class SceneLightType
{
    Ambient,
    Point,
    Directional,
    Spot
};

class Scene
{
public:
    Scene(glm::mat4 &view, glm::mat4 &proj, std::vector<SceneLightType> lights, bool skyboxSky);
    ~Scene();
    void init();
    void addObject(DrawAbleObject *object);
    void addShaderProgram(ShaderProgram *shaderProgram);
    void addLight(LightSubject *light);

    void setView(glm::mat4 &view);
    void setProjection(glm::mat4 &proj);

    void updateLights(bool reset);
    void drawScene();
    void drawSceneStencil();

    void buildFireflies(Model *model, ShaderProgram *shader, Scene *scene);
    void updateFireflies();

    void setCamera(float ratio);
    CameraSubject *getCamera();
    void updateCamera(GLFWwindow *window, float deltaTime);

    Controller *getController();

    SpotLight *getSpotLight() { return spot; }
    void selectObjectById(unsigned int id);
    void setSelect(int id);
    DrawAbleObject *getSelected() const;

    void plantTree(const glm::vec3 &worldPos);
    ShaderProgram *getTreeShader() const { return shaderTree; }
    Material &getTreeMaterial() { return treeMaterial; }
    void deleteSelected();

private:
    bool firefliesBuilt = false;
    glm::mat4 view;
    glm::mat4 proj;

    CameraSubject *camera = nullptr;
    Controller *controller = nullptr;

    AmbientLight *ambient = nullptr;
    PointLight *point = nullptr;
    DirectionalLight *directional = nullptr;
    SpotLight *spot = nullptr;

    std::vector<DrawAbleObject *> drawAbleObjects;
    std::vector<ShaderProgram *> shaderPrograms;
    std::vector<LightSubject *> lights;
    std::vector<LightSubject *> fireflies;
    std::vector<Firefly> firefliesData;

    Skybox *skybox = nullptr;
    ShaderProgram *skyboxShaderProgram = nullptr;
    ShaderProgram *stencilShaderProgram = nullptr;
    DrawAbleObject *selectedObject = nullptr;

    Model *modelTree = nullptr;
    ShaderProgram *shaderTree = nullptr;
    Material treeMaterial = Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 32.0f);

    // zmena
    int nextId;
    bool skyboxStars = 0;
};