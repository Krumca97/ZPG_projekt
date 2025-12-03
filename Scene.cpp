#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include <time.h>
#include "Transformations/TransformationTranslate.h"
#include "Transformations/TransformationScale.h"
#include "Transformations/TransformationRotate.h"
#include "Transformations/TransformationComposite.h"
#include <algorithm>
#include "Models/tree.h"
#include "Application.h"

Scene::Scene(glm::mat4 &view, glm::mat4 &proj, std::vector<SceneLightType> lights, bool skyboxSky)
{
    this->view = view;
    this->proj = proj;
    this->skyboxShaderProgram = new ShaderProgram();
    this->skyboxStars = skyboxSky;

    if (this->skyboxStars)
    {
        Shader skyboxVertexShader("../../Shaders/SkyboxVertexShader.vert", GL_VERTEX_SHADER);
        Shader skyboxFragmentShader("../../Shaders/SkyboxFragmentShader.frag", GL_FRAGMENT_SHADER);
        this->skyboxShaderProgram->link(skyboxVertexShader, skyboxFragmentShader);
        skybox = new Skybox(skyboxShaderProgram,
                            {"../../Textures/Skybox/px.png",
                             "../../Textures/Skybox/nx.png",
                             "../../Textures/Skybox/py.png",
                             "../../Textures/Skybox/ny.png",
                             "../../Textures/Skybox/pz.png",
                             "../../Textures/Skybox/nz.png"});
    }
    else
    {
        Shader skyboxVertexShader("../../Shaders/SkyboxVertexShader.vert", GL_VERTEX_SHADER);
        Shader skyboxFragmentShader("../../Shaders/SkyboxFragmentShader.frag", GL_FRAGMENT_SHADER);
        this->skyboxShaderProgram->link(skyboxVertexShader, skyboxFragmentShader);
        skybox = new Skybox(skyboxShaderProgram,
                            {"../../Textures/Skybox/posx.jpg",
                             "../../Textures/Skybox/negx.jpg",
                             "../../Textures/Skybox/posy.jpg",
                             "../../Textures/Skybox/negy.jpg",
                             "../../Textures/Skybox/posz.jpg",
                             "../../Textures/Skybox/negz.jpg"});
    }

    stencilShaderProgram = new ShaderProgram();
    Shader stencilVektorShader("../../Shaders/UniverzalVertexShader.vert", GL_VERTEX_SHADER);
    Shader stencilFragmentShader("../../Shaders/UniverzalFragmentShader.frag", GL_FRAGMENT_SHADER);
    stencilShaderProgram->link(stencilVektorShader, stencilFragmentShader);

    modelTree = new Model(6, 3, 3);
    std::vector<float> treeVerts(tree, tree + sizeof(tree) / sizeof(float));
    modelTree->loadData(treeVerts);

    shaderTree = new ShaderProgram();
    Shader treeVektorShader("../../Shaders/PhongVertexShader.vert", GL_VERTEX_SHADER);
    Shader treeFragmentShader("../../Shaders/PhongFragmentShader.frag", GL_FRAGMENT_SHADER);
    shaderTree->link(treeVektorShader, treeFragmentShader);

    for (auto type : lights)
    {
        switch (type)
        {
        case SceneLightType::Point:
            point = new PointLight(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(1.0f, 0.9f, 0.8f), 1.0f);
            addLight(point);
            break;

        case SceneLightType::Directional:
            directional = new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(1.0f, 1.0f, 0.95f), 1.2f);
            addLight(directional);
            break;

        case SceneLightType::Spot:
            spot = new SpotLight(glm::vec3(1.0f, 1.0f, 0.9f), 2.0f);
            addLight(spot);
            break;
        }
    }
};

Scene::~Scene() {};

void Scene::addObject(DrawAbleObject *object)
{
    if (!object)
    {
        printf("DrawAbleObject points to nullptr");
        return;
    }
    else
    {
        this->drawAbleObjects.push_back(object);
    }
}

void Scene::addShaderProgram(ShaderProgram *shaderProgram)
{
    if (!shaderProgram)
    {
        printf("Shader program points to nullptr");
        return;
    }
    else
    {
        this->shaderPrograms.push_back(shaderProgram);
    }
}

void Scene::addLight(LightSubject *light)
{
    lights.push_back(light);

    for (auto *shader : shaderPrograms)
    {
        light->attach(shader);
    }
}

void Scene::setView(glm::mat4 &view)
{
    this->view = view;
}

void Scene::setProjection(glm::mat4 &proj)
{
    this->proj = proj;
}

void Scene::updateLights(bool reset)
{
    if (reset)
    {
        for (auto *shader : shaderPrograms)
        {
            shader->resetLight();
            shader->setLightIndex(0);
        }
    }

    if (spot)
    {
        spot->notify();
    }

    int i = 0;
    for (auto *light : lights)
    {
        light->notify();
    }

    for (auto *shader : shaderPrograms)
    {
        shader->uploadLights();
    }
}

void Scene::drawScene()
{
    glStencilMask(0x00);
    for (auto &object : drawAbleObjects)
    {
        object->draw(view, proj);
    }
    skybox->draw(view, proj);
    glStencilMask(0xFF);
}

void Scene::drawSceneStencil()
{
    glEnable(GL_STENCIL_TEST);

    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_STENCIL_BUFFER_BIT);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);

    Application *app = static_cast<Application *>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

    for (DrawAbleObject *obj : drawAbleObjects)
    {
        if (app && app->isObjectMoving() && app->getMovingObject() == obj)
        {
            continue;
        }

        glStencilFunc(GL_ALWAYS, obj->getId(), 0xFF);
        obj->drawStencil(*stencilShaderProgram, view, proj);
    }

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glDisable(GL_STENCIL_TEST);
}

void Scene::buildFireflies(Model *model, ShaderProgram *shader, Scene *scene)
{
    fireflies.clear();
    std::srand((unsigned)std::time(nullptr));

    const int numFireflies = 8;
    const float forestArea = 25.0f;

    for (int i = 0; i < numFireflies; i++)
    {
        float x = -forestArea + 2.0f * forestArea * (std::rand() / (float)RAND_MAX);
        float y = 0.5f + 3.5f * (std::rand() / (float)RAND_MAX);
        float z = -forestArea + 2.0f * forestArea * (std::rand() / (float)RAND_MAX);
        glm::vec3 pos(x, y, z);
        glm::vec3 color(1.0f, 0.9f, 0.7f);
        float intensity = 0.2f;
        fireflies.push_back(new LightSubject(pos, color, intensity));
    }

    firefliesData.clear();

    for (int i = 0; i < fireflies.size(); i++)
    {

        glm::vec3 pos = fireflies[i]->getPosition();

        DrawAbleObject *sphere = new DrawAbleObject(*model, *shader);
        sphere->addTransformation(new TransformationTranslate(pos, 0.0f));
        sphere->addTransformation(new TransformationScale(glm::vec3(0.005f), 0.0f));
        shader->setObjectColor(glm::vec3(1.f, 0.9f, 0.6f));
        scene->addObject(sphere);

        glm::vec3 dir = glm::normalize(glm::vec3(((std::rand() % 200) - 100) / 100.0f, ((std::rand() % 100) - 50) / 200.0f, ((std::rand() % 200) - 100) / 100.0f));
        Firefly f = {sphere, fireflies[i], pos, dir, glfwGetTime(), glfwGetTime()};

        firefliesData.push_back(f);
        fireflies[i]->attach(shader);
        scene->addLight(fireflies[i]);
    }
}

void Scene::updateFireflies()
{
    const float area = 25.0f;

    for (auto &firefly : firefliesData)
    {
        double now = glfwGetTime();
        float dt = float(now - firefly.lastUpdate);
        firefly.lastUpdate = now;

        if (now - firefly.lastChangeDir > 2.0 + (std::rand() % 2000) / 1000.0)
        {
            firefly.lastChangeDir = now;
            float yaw = ((std::rand() % 360) - 180) * 0.1f;
            float pitch = ((std::rand() % 100) - 50) * 0.02f;
            glm::mat4 rot(1.0f);
            rot = glm::rotate(rot, glm::radians(yaw), glm::vec3(0, 1, 0));
            rot = glm::rotate(rot, glm::radians(pitch), glm::vec3(1, 0, 0));
            firefly.direction = glm::normalize(glm::vec3(rot * glm::vec4(firefly.direction, 0.0f)));
        }

        firefly.position += firefly.direction * dt * 0.5f;

        if (firefly.position.x < -area || firefly.position.x > area)
        {
            firefly.direction.x *= -1;
        }
        if (firefly.position.z < -area || firefly.position.z > area)
        {
            firefly.direction.z *= -1;
        }
        if (firefly.position.y < 0.2f || firefly.position.y > 4.0f)
        {
            firefly.direction.y *= -1;
        }

        firefly.position.x = glm::clamp(firefly.position.x, -area, area);
        firefly.position.y = glm::clamp(firefly.position.y, 0.2f, 4.0f);
        firefly.position.z = glm::clamp(firefly.position.z, -area, area);

        firefly.light->clearTransformation();
        firefly.light->addTransformation(new TransformationTranslate(firefly.position, 0.0f));
        firefly.light->notify();

        firefly.sphere->clearTransformation();
        firefly.sphere->addTransformation(new TransformationTranslate(firefly.position, 0.0f));
        firefly.sphere->addTransformation(new TransformationScale(glm::vec3(0.005f), 0.0f));
    }
}

void Scene::setCamera(float ratio)
{
    this->camera = new CameraSubject(glm::vec3(0.f, 1.7f, 3.f), -90.0f, 0.0f, 60.f, ratio, 0.1f, 100.f, 3.f, 0.003f);
    this->controller = new Controller(this->camera);

    for (auto *shader : shaderPrograms)
    {
        this->camera->attach(shader);
    }
    this->camera->notify();

    if (spot)
    {
        spot->attachCamera(this->camera);
    }
}

CameraSubject *Scene::getCamera()
{
    return this->camera;
}

void Scene::updateCamera(GLFWwindow *window, float deltaTime)
{
    if (!this->controller || !this->camera)
    {
        return;
    }
    this->controller->processKeyboard(window, deltaTime);

    view = this->camera->getViewMatrix();
    proj = this->camera->projectionMatrix();

    for (auto *shader : shaderPrograms)
    {
        shader->onCameraChange(view, proj, camera->getPosition());
    }

    static bool f11Pressed = false;

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !f11Pressed)
    {
        spot->toggle();
        spot->notify();
        f11Pressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
    {
        f11Pressed = false;
    }
    glm::vec3 pos = camera->getPosition();
}

Controller *Scene::getController()
{
    return this->controller;
}

void Scene::setSelect(int id)
{
    selectedObject = nullptr;

    for (DrawAbleObject *obj : this->drawAbleObjects)
    {
        if (obj->getId() == id)
        {
            selectedObject = obj;
            return;
        }
    }
}

DrawAbleObject *Scene::getSelected() const
{
    return selectedObject;
}

void Scene::plantTree(const glm::vec3 &worldPos)
{
    nextId = drawAbleObjects.size() + 1;
    DrawAbleObject *newTree = new DrawAbleObject(*modelTree, *shaderTree);
    newTree->setMaterial(treeMaterial);

    newTree->setId(this->nextId++);
    shaderTree->setObjectColor(glm::vec3(0.0f, 1.0f, 0.0f));
    TransformationComposite *trans = new TransformationComposite();
    trans->addTransformation(new TransformationTranslate(worldPos, 1.0f));
    trans->addTransformation(new TransformationScale(glm::vec3(1.0f), 0.0f));
    newTree->addTransformation(trans);

    this->drawAbleObjects.push_back(newTree);

    for (LightSubject *light : this->lights)
    {
        light->notify();
    }
}

void Scene::deleteSelected()
{
    for (int i = 1; i < drawAbleObjects.size(); i++)
    {
        if (drawAbleObjects[i] == selectedObject)
        {
            delete drawAbleObjects[i];
            drawAbleObjects.erase(drawAbleObjects.begin() + i);
            selectedObject = nullptr;
            return;
        }
    }
}
