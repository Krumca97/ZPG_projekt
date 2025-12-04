#include "Scene5.h"
#include "../Application.h"

#include "../Transformations/TransformationComposite.h"
#include "../Transformations/TransformationTranslate.h"
#include "../Transformations/TransformationCustom.h"

#include "../Lights/PointLight.h"
#include "../TextureLoader.h"

Scene* Scene5::Build(Application* app)
{
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    Scene* scene = new Scene(view,proj,{ SceneLightType::Point,SceneLightType::Spot },false);

    Material neutral(glm::vec3(0.1f),glm::vec3(1.0f),glm::vec3(1.0f),128.0f);

    scene->addShaderProgram(app->shaderFormula1Texture);

    TransformationComposite* t = new TransformationComposite();
    t->addTransformation(new TransformationTranslate(glm::vec3(0.f, 0.f, -5.f), 0.f));
    t->addTransformation(new TransformationCustom());
    app->formula1->addTransformation(t);

    app->formula1->setMaterial(neutral);

    PointLight* pointFormula = new PointLight(glm::vec3(0.f, 15.f, -5.f),glm::vec3(1.f, 1.f, 1.f),3.f);

    pointFormula->attach(app->shaderFormula1Texture);
    pointFormula->notify();
    scene->addLight(pointFormula);

    GLuint tex = TextureLoader::LoadTexture("../../Textures/wooden_fence.png");
    app->formula1->setTexture(tex);

    scene->addObject(app->formula1);

    return scene;
}
