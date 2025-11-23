#include "Scene3.h"
#include "../Application.h"

#include "../Transformations/TransformationComposite.h"
#include "../Transformations/TransformationTranslate.h"
#include "../Transformations/TransformationRotate.h"
#include "../Transformations/TransformationScale.h"

#include "../Lights/AmbientLight.h"
#include "../Lights/PointLight.h"

#include "../TextureLoader.h"

#include "../Models/plain.h"

Scene* Scene3::Build(Application* app)
{
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    Scene* scene = new Scene(view,proj,{ SceneLightType::Ambient, SceneLightType::Point },false);

    Material neutral(glm::vec3(0.1f),glm::vec3(1.0f),glm::vec3(1.0f),128.0f);    

    {
        Model* plainModel = new Model(8, 3, 3);
        plainModel->loadData(std::vector<float>(plain, plain + sizeof(plain) / sizeof(float)));

        ObjectGroup* ground = new ObjectGroup();
        ground->name = "Ground";

        DrawAbleObject* plainObj = new DrawAbleObject(*plainModel, *app->shaderPlainForest);

        TransformationComposite* GroundGroup = new TransformationComposite();
        GroundGroup->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -0.01f, 0.0f), 1.0f));
        GroundGroup->addTransformation(new TransformationScale(glm::vec3(60.0f, 1.0f, 60.0f), 1.0f));
        plainObj->addTransformation(GroundGroup);

        plainObj->setMaterial(neutral);
        GLuint texGround = TextureLoader::LoadTexture("../../Textures/grass.png");
        plainObj->setUvScale(16.0f);
        plainObj->setTexture(texGround);

        ground->objects.push_back(plainObj);

        scene->addObject(plainObj);
        scene->addShaderProgram(app->shaderPlainForest);
    }

    AmbientLight* forestAmbient = new AmbientLight(glm::vec3(0.3f, 0.3f, 0.3f),0.6f);
    forestAmbient->attach(app->shaderUniverzal);
    forestAmbient->attach(scene->getTreeShader());
    forestAmbient->notify();
    scene->addLight(forestAmbient);
    scene->addShaderProgram(scene->getTreeShader());

    const float areaHalf = 25.0f;
    const glm::vec2 center(0.0f);
    const float startRadius = 2.5f;
    const float groundY = 0.0f;

    std::srand((unsigned)std::time(nullptr));

    for (ObjectGroup* group : app->groupForScene3)
    {
        for (DrawAbleObject* obj : group->objects)
        {
            float x, z;
            bool isValid = false;

            while (!isValid)
            {
                x = -areaHalf + ((float)std::rand() / RAND_MAX) * (2 * areaHalf);
                z = -areaHalf + ((float)std::rand() / RAND_MAX) * (2 * areaHalf);

                if (glm::length(glm::vec2(x, z) - center) >= startRadius)
                {
                    isValid = true;
                }
            }

            float minSize = 0.6f;
            float maxSize = 1.4f;

            if (group->name == "Bush")
            {
                minSize = 0.3f;
                maxSize = 0.8f;
            }

            float size = minSize + ((float)std::rand() / RAND_MAX) * (maxSize - minSize);
            float randomAngle = -180.f + ((float)std::rand() / RAND_MAX) * 360.f;

            TransformationComposite* transGroup3 = new TransformationComposite();
            transGroup3->addTransformation(new TransformationTranslate(glm::vec3(x, groundY, z), 1.0f));
            transGroup3->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), randomAngle, 0.0f));
            transGroup3->addTransformation(new TransformationScale(glm::vec3(size), 1.0f));
            obj->addTransformation(transGroup3);

            obj->setMaterial(neutral);

            scene->addObject(obj);
            scene->addShaderProgram(app->shaderUniverzal);
        }
    }

    TransformationComposite* shrekT = new TransformationComposite();
    shrekT->addTransformation(new TransformationTranslate(glm::vec3(-6.f, 0.f, -8.f), 0.f));
    app->shrek->addTransformation(shrekT);
    app->shrek->setMaterial(neutral);

    GLuint texShrek = TextureLoader::LoadTexture("../../Textures/shrek.png");
    app->shrek->setTexture(texShrek);

    scene->addShaderProgram(app->shaderShrekTexture);
    scene->addObject(app->shrek);

    TransformationComposite* fionaT = new TransformationComposite();
    fionaT->addTransformation(new TransformationTranslate(glm::vec3(-3.f, 0.f, -8.f), 0.f));
    app->fiona->addTransformation(fionaT);
    app->fiona->setMaterial(neutral);

    GLuint texFiona = TextureLoader::LoadTexture("../../Textures/fiona.png");
    app->fiona->setTexture(texFiona);

    scene->addShaderProgram(app->shaderFionaTexture);
    scene->addObject(app->fiona);

    TransformationComposite* toiletT = new TransformationComposite();
    toiletT->addTransformation(new TransformationTranslate(glm::vec3(0.f, 0.f, -8.f), 0.f));
    toiletT->addTransformation(new TransformationScale(glm::vec3(0.5f), 0.f));
    app->toilet->addTransformation(toiletT);
    app->toilet->setMaterial(neutral);

    GLuint texToilet = TextureLoader::LoadTexture("../../Textures/toiled.jpg");
    app->toilet->setTexture(texToilet);

    scene->addShaderProgram(app->shaderToiletTexture);
    scene->addObject(app->toilet);

    PointLight* lf = new PointLight(glm::vec3(0.f, 5.f, -8.f),glm::vec3(1.0f, 0.95f, 0.8f),20.f);
    lf->attach(app->shaderShrekTexture);
    lf->attach(app->shaderFionaTexture);
    lf->attach(app->shaderToiletTexture);
    lf->notify();
    scene->addLight(lf);

    scene->buildFireflies(app->modelSphere, app->shaderSphereForest, scene);

    return scene;
}
