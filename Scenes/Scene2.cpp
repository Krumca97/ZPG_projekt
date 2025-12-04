#include "Scene2.h"
#include "../Application.h"

#include "../Transformations/TransformationComposite.h"
#include "../Transformations/TransformationTranslate.h"
#include "../Transformations/TransformationRotate.h"
#include "../Transformations/TransformationScale.h"

#include "../Lights/AmbientLight.h"
#include "../Lights/PointLight.h"
#include "../Lights/DirectionalLight.h"
#include "../Lights/SpotLight.h"

Scene *Scene2::Build(Application *app)
{
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    Scene *scene = new Scene(view, proj, {SceneLightType::Directional, SceneLightType::Point, SceneLightType::Ambient, SceneLightType::Spot}, false);

    DrawAbleObject *s1 = app->object1Sphere;
    DrawAbleObject *s2 = app->object2Sphere;
    DrawAbleObject *s3 = app->object3Sphere;
    DrawAbleObject *s4 = app->object4Sphere;

    ShaderProgram *sh1 = app->shaderSphere1;
    ShaderProgram *sh2 = app->shaderSphere2;
    ShaderProgram *sh3 = app->shaderSphere3;
    ShaderProgram *sh4 = app->shaderSphere4;

    s1->addTransformation(new TransformationTranslate(glm::vec3(0.f, 0.75f, 0.f), 0.0f));
    s1->addTransformation(new TransformationScale(glm::vec3(0.2f), 0.0f));

    s2->addTransformation(new TransformationTranslate(glm::vec3(-0.75f, 0.f, 0.f), 0.0f));
    s2->addTransformation(new TransformationScale(glm::vec3(0.2f), 0.0f));

    s3->addTransformation(new TransformationTranslate(glm::vec3(0.75f, 0.f, 0.f), 0.0f));
    s3->addTransformation(new TransformationScale(glm::vec3(0.2f), 0.0f));

    s4->addTransformation(new TransformationTranslate(glm::vec3(0.f, -0.75f, 0.f), 0.0f));
    s4->addTransformation(new TransformationScale(glm::vec3(0.2f), 0.0f));

    Material neutral(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 128.0f);

    s1->setMaterial(neutral);
    s2->setMaterial(neutral);
    s3->setMaterial(neutral);
    s4->setMaterial(neutral);

    scene->addShaderProgram(sh1);
    scene->addShaderProgram(sh2);
    scene->addShaderProgram(sh3);
    scene->addShaderProgram(sh4);

    glm::vec3 lightCenter(0.f);

    // Ambient
    AmbientLight *ambient = new AmbientLight(glm::vec3(0.15f, 0.15f, 0.2f), 1.3f);
    ambient->attach(sh1);
    ambient->notify();
    scene->addLight(ambient);

    // Point light
    PointLight *point = new PointLight(lightCenter + glm::vec3(0.f, 0.0f, 0.f), glm::vec3(0.9f, 0.7f, 0.7f), 0.75f);
    point->attach(sh2);
    point->notify();
    scene->addLight(point);

    // Directional
    DirectionalLight *directional = new DirectionalLight(glm::normalize(glm::vec3(0.5f, -1.f, 0.3f)), glm::vec3(0.9f, 0.9f, 1.f), 0.13f);
    directional->attach(sh3);
    directional->notify();
    scene->addLight(directional);

    // Spotlight
    SpotLight *spot = scene->getSpotLight();
    spot->attach(sh4);
    spot->attachCamera(scene->getCamera());
    spot->notify();
    scene->addLight(spot);

    scene->addObject(s1);
    scene->addObject(s2);
    scene->addObject(s3);
    scene->addObject(s4);

    return scene;
}
