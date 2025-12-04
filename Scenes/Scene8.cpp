#include "Scene8.h"
#include "../Application.h"
#include "../TextureLoader.h"
#include "../Transformations/TransformationComposite.h"
#include "../Transformations/TransformationBezier.h"
#include "../Transformations/TransformationRotate.h"
#include "../Transformations/TransformationScale.h"
#include "../Models/plain.h"

Scene *Scene8::Build(Application *app, Scene8 *sceneLogic)
{
    glm::mat4 view(1.f);
    glm::mat4 proj(1.f);

    sceneLogic->app = app;

    Scene *scene = new Scene(view, proj, {SceneLightType::Ambient}, false);
    scene->addShaderProgram(app->shaderFormula1Texture2);

    Material neutral(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 128.0f);
    // Model *plainModel = new Model(8, 3, 3);
    // plainModel->loadData(std::vector<float>(plain, plain + sizeof(plain) / sizeof(float)));

    // ObjectGroup *ground = new ObjectGroup();
    // ground->name = "Ground";

    // DrawAbleObject *plainObj = new DrawAbleObject(*plainModel, *app->shaderPlainForest);

    // TransformationComposite *GroundGroup = new TransformationComposite();
    // GroundGroup->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -0.01f, 0.0f), 1.0f));
    // GroundGroup->addTransformation(new TransformationScale(glm::vec3(60.0f, 1.0f, 60.0f), 1.0f));
    // plainObj->addTransformation(GroundGroup);

    // plainObj->setMaterial(neutral);
    // GLuint texGround = TextureLoader::LoadTexture("../../Textures/grass.png");
    // plainObj->setUvScale(16.0f);
    // plainObj->setTexture(texGround);

    // ground->objects.push_back(plainObj);

    // scene->addObject(plainObj);
    // scene->addShaderProgram(app->shaderPlainForest);

    GLuint texTeren = TextureLoader::LoadTexture("../../Textures/grass.png");
    app->teren->setTexture(texTeren);
    scene->addObject(app->teren);

    GLuint texFormula1 = TextureLoader::LoadTexture("../../Textures/wooden_fence.png");
    app->formula1_scene8->setTexture(texFormula1);
    app->formula1_scene8->clearTransformation();

    Material formula1Mat(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 64.0f);
    app->formula1_scene8->setMaterial(formula1Mat);

    TransformationComposite *formula1_transformation = new TransformationComposite();
    formula1_transformation->addTransformation(new TransformationScale(glm::vec3(0.1f), 0.f));

    std::vector<glm::vec3> path = {
        {0.f, 0.f, 0.f},
        {0.f, 0.f, 0.f},
        {0.f, 0.f, 0.f},
        {0.f, 0.f, 0.f},

        // {0.f,   0.f,    0.f},
        // {80.f,  10.f,  -60.f},
        // {160.f, 20.f, -120.f},
        // {240.f,  0.f, -200.f},

        // {300.f, -5.f, -260.f},
        // {340.f, -10.f, -200.f},
        // {380.f, -5.f, -120.f},
        // {420.f,  0.f,  -40.f},

        // {460.f, 10.f,   40.f},
        // {480.f, 25.f,  120.f},
        // {460.f, 40.f,  200.f},
        // {420.f, 50.f,  260.f},

        // {360.f, 55.f,  320.f},
        // {280.f, 60.f,  360.f},
        // {160.f, 55.f,  380.f},
        // { 40.f, 50.f,  360.f},

        // {-40.f,  30.f, 300.f},
        // {-120.f, 10.f, 220.f},
        // {-200.f,  0.f, 140.f},
        // {-280.f, -10.f,  60.f},

        // {-360.f, -15.f, -20.f},
        // {-420.f, -20.f, -100.f},
        // {-460.f, -10.f, -180.f},
        // {-480.f,   0.f, -260.f},

        // {-420.f, 10.f, -340.f},
        // {-320.f, 20.f, -380.f},
        // {-160.f, 10.f, -400.f},
        // {  0.f,   0.f, -380.f},

        // { 80.f,  5.f, -320.f},
        // {120.f, 10.f, -200.f},
        // { 60.f,  5.f, -100.f},
        // {  0.f,  0.f,    0.f}
    };

    formula1_transformation->addTransformation(new TransformationBezier(path, 0.8f));
    formula1_transformation->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 90.f, 0.f));
    app->formula1_scene8->addTransformation(formula1_transformation);
    scene->addObject(app->formula1_scene8);
    sceneLogic->formulaCar = app->formula1_scene8;

    AmbientLight *ambient = new AmbientLight(glm::vec3(1.f, 1.f, 1.f), 5.f);
    ambient->attach(app->shaderFormula1Texture2);
    ambient->notify();
    scene->addLight(ambient);

    return scene;
}

void Scene8::addBezierPoint(glm::vec3 p)
{
    bezierPoints.push_back(p);
    printf("added point: %.2f %.2f %.2f\n", p.x, p.y, p.z);

    rebuildBezier();
}

void Scene8::rebuildBezier()
{

    if (!formulaCar)
    {
        return;
    }

    if (bezierPoints.size() < 4)
    {
        return;
    }

    formulaCar->clearTransformation();

    TransformationComposite *comp = new TransformationComposite();
    bezierTransform = new TransformationBezier(bezierPoints, 1.0f);
    comp->addTransformation(bezierTransform);

    comp->addTransformation(new TransformationScale(glm::vec3(0.1f), 0.f));
    comp->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 90.f, 0.f));

    formulaCar->addTransformation(comp);
}
