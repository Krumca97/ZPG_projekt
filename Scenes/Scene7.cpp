#include "Scene7.h"
#include "../Application.h"

#include "../Transformations/TransformationComposite.h"
#include "../Transformations/TransformationTranslate.h"
#include "../Transformations/TransformationScale.h"
#include "../Transformations/TransformationRotate.h"
#include "../Transformations/TransformationPath.h"

#include "../Lights/PointLight.h"
#include "../TextureLoader.h"

Scene* Scene7::Build(Application* app)
{
    glm::mat4 view(1.f);
    glm::mat4 proj(1.f);

    Scene* scene = new Scene(view,proj,{ SceneLightType::Point },false);

    scene->addShaderProgram(app->shaderCup);
    scene->addShaderProgram(app->shaderBall);
    scene->addShaderProgram(app->shaderTable);

    GLuint texCup = TextureLoader::LoadTexture("../../Textures/red.jpg");
    GLuint texTable = TextureLoader::LoadTexture("../../Textures/wooden_fence.png");

    app->cup1->setTexture(texCup);
    app->cup2->setTexture(texCup);
    app->cup3->setTexture(texCup);
    app->table->setTexture(texTable);

    glm::vec3 P1(-1.5f, 0.f, 0.f);
    glm::vec3 P2( 0.0f, 0.f, 0.f);
    glm::vec3 P3( 1.5f, 0.f, 0.f);

    app->transCup1 = new TransformationComposite();
    app->transCup2 = new TransformationComposite();
    app->transCup3 = new TransformationComposite();

    app->transCup1->addTransformation(new TransformationRotate(glm::vec3(1,0,0), 180.f, 0.f));
    app->transCup2->addTransformation(new TransformationRotate(glm::vec3(1,0,0), 180.f, 0.f));
    app->transCup3->addTransformation(new TransformationRotate(glm::vec3(1,0,0), 180.f, 0.f));

    app->transCup1->addTransformation(new TransformationScale(glm::vec3(5.f), 0.f));
    app->transCup2->addTransformation(new TransformationScale(glm::vec3(5.f), 0.f));
    app->transCup3->addTransformation(new TransformationScale(glm::vec3(5.f), 0.f));

    app->transCup1->addTransformation(new TransformationTranslate(P1, 0.f));
    app->transCup2->addTransformation(new TransformationTranslate(P2, 0.f));
    app->transCup3->addTransformation(new TransformationTranslate(P3, 0.f));

    app->cup1->addTransformation(app->transCup1);
    app->cup2->addTransformation(app->transCup2);
    app->cup3->addTransformation(app->transCup3);

    Material cupMat(glm::vec3(0.2f), glm::vec3(1.f), glm::vec3(1.f), 64.f);

    app->cup1->setMaterial(cupMat);
    app->cup2->setMaterial(cupMat);
    app->cup3->setMaterial(cupMat);

    scene->addObject(app->cup1);
    scene->addObject(app->cup2);
    scene->addObject(app->cup3);

    app->liftCup1 = new TransformationTranslate(glm::vec3(0, 0, 0), 0.f);
    app->liftCup2 = new TransformationTranslate(glm::vec3(0, 0, 0), 0.f);
    app->liftCup3 = new TransformationTranslate(glm::vec3(0, 0, 0), 0.f);

    app->transCup1->addTransformation(app->liftCup1);
    app->transCup2->addTransformation(app->liftCup2);
    app->transCup3->addTransformation(app->liftCup3);

    std::vector<glm::vec3> pathPoints = { P1, P2, P3 };

    app->path1 = new TransformationPath(pathPoints, 3.0f);
    app->path2 = new TransformationPath(pathPoints, 2.8f);
    app->path3 = new TransformationPath(pathPoints, 3.2f);

    app->path1->setActive(false);
    app->path2->setActive(false);
    app->path3->setActive(false);

    app->transCup1->addTransformation(app->path1);
    app->transCup2->addTransformation(app->path2);
    app->transCup3->addTransformation(app->path3);

    app->ball->setMaterial(cupMat);

    app->ballTranslate = new TransformationTranslate(glm::vec3(0.f), 0.f);

    TransformationComposite* ballT = new TransformationComposite();
    ballT->addTransformation(new TransformationScale(glm::vec3(0.15f), 0.f));
    ballT->addTransformation(app->ballTranslate);

    glm::vec3 ballBasePositions[3] =
    {
        P1 + glm::vec3(0, -1.8f, 0),
        P2 + glm::vec3(0, -1.8f, 0),
        P3 + glm::vec3(0, -1.8f, 0)
    };

    app->ballSlot = rand() % 3;
    app->ballTranslate->setDirection(ballBasePositions[app->ballSlot]);

    app->ball->addTransformation(ballT);
    scene->addObject(app->ball);

    TransformationComposite* tableT = new TransformationComposite();
    tableT->addTransformation(new TransformationTranslate(glm::vec3(0, -3.f, 0.f), 0.f));
    tableT->addTransformation(new TransformationScale(glm::vec3(20.f, 17.f, 10.f), 0.f));

    app->table->addTransformation(tableT);
    app->table->setMaterial(cupMat);

    scene->addObject(app->table);

    PointLight* cupLight = new PointLight(glm::vec3(0.f, 5.f, 3.f),glm::vec3(1.f),50.f);

    cupLight->attach(app->shaderCup);
    cupLight->attach(app->shaderBall);
    cupLight->attach(app->shaderTable);
    cupLight->notify();

    scene->addLight(cupLight);

    return scene;
}
