#include "Scene.h"

Scene::Scene(glm::mat4& view,glm::mat4& proj)
{
    this->view= view;
    this->proj = proj;
};

Scene::~Scene(){};

void Scene::addObject(DrawAbleObject* object)
{
    if(!object)
    {
        printf("DrawAbleObjekt ukazuje na nullptr");
        return;
    }
    else
    {
        this->drawAbleObjects.push_back(object);
    }
}

void Scene::addShaderProgram(ShaderProgram* shaderProgram)
{
    if(!shaderProgram)
    {
        printf("Shader program ukazuje na nullptr");
        return;
    }
    else
    {
        this->shaderPrograms.push_back(shaderProgram);
    }
}

void Scene::setView(glm::mat4& view)
{
    this->view = view;
}

void Scene::setProjection(glm::mat4& proj)
{
    this->proj = proj;
}


void Scene::drawScene()
{
    for (auto& object : drawAbleObjects){
        object->draw(view,proj);
    }
}

