#include "Scene1.h"
#include "../Application.h"

#include "../Transformations/TransformationComposite.h"
#include "../Transformations/TransformationTranslate.h"
#include "../Transformations/TransformationRotate.h"

Scene *Scene1::Build(Application *app)
{
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    Scene *scene = new Scene(view, proj, {SceneLightType::Ambient,SceneLightType::Spot}, false);

    DrawAbleObject *tri = app->objectTriangle;
    ShaderProgram *triShader = app->shaderTriangle;

    TransformationComposite *groupTriangle = new TransformationComposite();
    groupTriangle->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f));
    groupTriangle->addTransformation(new TransformationRotate(glm::vec3(0, 0, 1), 0.0f, 100.f));

    tri->addTransformation(groupTriangle);

    Material neutral(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 128.0f);
    tri->setMaterial(neutral);

    scene->addShaderProgram(triShader);
    scene->addObject(tri);

    return scene;
}
