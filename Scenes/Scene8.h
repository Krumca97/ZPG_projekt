#pragma once
#include "../Scene.h"
#include "../Transformations/TransformationBezier.h"

class Application;

class Scene8
{
public:
    Application *app = nullptr;
    static Scene *Build(Application *app, Scene8 *sceneLogic);

    void addBezierPoint(glm::vec3 p);
    void rebuildBezier();

private:
    std::vector<glm::vec3> bezierPoints;
    TransformationBezier *bezierTransform = nullptr;
    DrawAbleObject *formulaCar = nullptr;
};