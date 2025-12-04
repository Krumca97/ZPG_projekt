#include "Scene6.h"
#include "../Application.h"

#include "../Transformations/TransformationComposite.h"
#include "../Transformations/TransformationTranslate.h"
#include "../Transformations/TransformationScale.h"

#include "../Lights/PointLight.h"
#include "../TextureLoader.h"

Scene* Scene6::Build(Application* app)
{
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    Scene* scene = new Scene(view,proj,{ SceneLightType::Point,SceneLightType::Spot },false);

    Material neutral(glm::vec3(0.1f),glm::vec3(1.0f),glm::vec3(1.0f),128.0f);

    scene->addShaderProgram(app->shaderHouseTexture);

    TransformationComposite* houseT = new TransformationComposite();
    houseT->addTransformation(new TransformationTranslate(glm::vec3(0.f, -1.f, -10.f), 0.f));
    houseT->addTransformation(new TransformationScale(glm::vec3(0.5f), 0.f));
    app->house->addTransformation(houseT);

    app->house->setMaterial(neutral);

    PointLight* lightHouse = new PointLight(glm::vec3(5.f, 10.f,  5.f),glm::vec3(1.f, 1.f, 1.f),10.f);

    lightHouse->attach(app->shaderHouseTexture);
    lightHouse->notify();
    scene->addLight(lightHouse);

    GLuint texHouse = TextureLoader::LoadTexture("../../Textures/grass.png");
    app->house->setTexture(texHouse);

    scene->addObject(app->house);

    return scene;
}
