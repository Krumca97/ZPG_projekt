#include "Scene4.h"
#include "../Application.h"

#include "../Transformations/TransformationComposite.h"
#include "../Transformations/TransformationTranslate.h"
#include "../Transformations/TransformationRotate.h"
#include "../Transformations/TransformationScale.h"

#include "../Lights/PointLight.h"
#include "../TextureLoader.h"

Scene *Scene4::Build(Application *app)
{
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    Scene *scene = new Scene(view, proj, {SceneLightType::Point}, true);

    Material neutral(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 128.0f);

    TransformationComposite *sunT = new TransformationComposite();
    sunT->addTransformation(new TransformationScale(glm::vec3(4.f), 0.f));
    sunT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 3.f));
    app->objectSun->addTransformation(sunT);

    TransformationComposite *earthT = new TransformationComposite();
    earthT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 8.f));
    earthT->addTransformation(new TransformationTranslate(glm::vec3(12.f, 0.f, 0.f), 0.f));
    earthT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 40.f));
    earthT->addTransformation(new TransformationScale(glm::vec3(0.8f), 0.f));
    app->objectEarth->addTransformation(earthT);
    app->objectEarth->setParentSpace(app->objectSun);

    TransformationComposite *moonT = new TransformationComposite();
    moonT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 20.f));
    moonT->addTransformation(new TransformationTranslate(glm::vec3(4.f, 0.f, 0.f), 0.f));
    moonT->addTransformation(new TransformationScale(glm::vec3(0.35f), 0.f));
    app->objectMoon->addTransformation(moonT);
    app->objectMoon->setParentSpace(app->objectEarth);

    TransformationComposite *loginT = new TransformationComposite();
    loginT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, -40.f));
    loginT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, -60.f));
    loginT->addTransformation(new TransformationTranslate(glm::vec3(4.f, 0.f, 0.f), 0.f));
    loginT->addTransformation(new TransformationScale(glm::vec3(0.35f), 0.f));
    app->objectLogin->addTransformation(loginT);
    app->objectLogin->setParentSpace(app->objectEarth);

    TransformationComposite *mercuryT = new TransformationComposite();
    mercuryT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 18.f));
    mercuryT->addTransformation(new TransformationTranslate(glm::vec3(7.f, 0.f, 0.f), 0.f));
    mercuryT->addTransformation(new TransformationScale(glm::vec3(0.3f), 0.f));
    app->objectMercury->addTransformation(mercuryT);
    app->objectMercury->setParentSpace(app->objectSun);

    TransformationComposite *venusT = new TransformationComposite();
    venusT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 14.f));
    venusT->addTransformation(new TransformationTranslate(glm::vec3(9.f, 0.f, 0.f), 0.f));
    venusT->addTransformation(new TransformationScale(glm::vec3(0.7f), 0.f));
    app->objectVenus->addTransformation(venusT);
    app->objectVenus->setParentSpace(app->objectSun);

    TransformationComposite *marsT = new TransformationComposite();
    marsT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 11.f));
    marsT->addTransformation(new TransformationTranslate(glm::vec3(15.f, 0.f, 0.f), 0.f));
    marsT->addTransformation(new TransformationScale(glm::vec3(0.4f), 0.f));
    app->objectMars->addTransformation(marsT);
    app->objectMars->setParentSpace(app->objectSun);

    TransformationComposite *jupiterT = new TransformationComposite();
    jupiterT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 6.f));
    jupiterT->addTransformation(new TransformationTranslate(glm::vec3(25.f, 0.f, 0.f), 0.f));
    jupiterT->addTransformation(new TransformationScale(glm::vec3(1.8f), 0.f));
    app->objectJupiter->addTransformation(jupiterT);
    app->objectJupiter->setParentSpace(app->objectSun);

    TransformationComposite *saturnT = new TransformationComposite();
    saturnT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 5.f));
    saturnT->addTransformation(new TransformationTranslate(glm::vec3(35.f, 0.f, 0.f), 0.f));
    saturnT->addTransformation(new TransformationScale(glm::vec3(1.5f), 0.f));
    app->objectSaturn->addTransformation(saturnT);
    app->objectSaturn->setParentSpace(app->objectSun);

    TransformationComposite *uranusT = new TransformationComposite();
    uranusT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 4.f));
    uranusT->addTransformation(new TransformationTranslate(glm::vec3(45.f, 0.f, 0.f), 0.f));
    uranusT->addTransformation(new TransformationScale(glm::vec3(1.2f), 0.f));
    app->objectUranus->addTransformation(uranusT);
    app->objectUranus->setParentSpace(app->objectSun);

    TransformationComposite *neptuneT = new TransformationComposite();
    neptuneT->addTransformation(new TransformationRotate(glm::vec3(0, 1, 0), 0.f, 3.f));
    neptuneT->addTransformation(new TransformationTranslate(glm::vec3(55.f, 0.f, 0.f), 0.f));
    neptuneT->addTransformation(new TransformationScale(glm::vec3(1.1f), 0.f));
    app->objectNeptune->addTransformation(neptuneT);
    app->objectNeptune->setParentSpace(app->objectSun);

    app->objectSun->setMaterial(neutral);
    app->objectEarth->setMaterial(neutral);
    app->objectMoon->setMaterial(neutral);
    app->objectMercury->setMaterial(neutral);
    app->objectVenus->setMaterial(neutral);
    app->objectMars->setMaterial(neutral);
    app->objectJupiter->setMaterial(neutral);
    app->objectSaturn->setMaterial(neutral);
    app->objectUranus->setMaterial(neutral);
    app->objectNeptune->setMaterial(neutral);

    app->objectSun->setTexture(TextureLoader::LoadTexture("../../Textures/2k_sun.jpg"));
    app->objectEarth->setTexture(TextureLoader::LoadTexture("../../Textures/2k_earth_daymap.jpg"));
    app->objectMoon->setTexture(TextureLoader::LoadTexture("../../Textures/2k_moon.jpg"));
    app->objectMercury->setTexture(TextureLoader::LoadTexture("../../Textures/2k_mercury.jpg"));
    app->objectVenus->setTexture(TextureLoader::LoadTexture("../../Textures/2k_venus_surface.jpg"));
    app->objectMars->setTexture(TextureLoader::LoadTexture("../../Textures/2k_mars.jpg"));
    app->objectJupiter->setTexture(TextureLoader::LoadTexture("../../Textures/2k_jupiter.jpg"));
    app->objectSaturn->setTexture(TextureLoader::LoadTexture("../../Textures/2k_saturn.jpg"));
    app->objectUranus->setTexture(TextureLoader::LoadTexture("../../Textures/2k_uranus.jpg"));
    app->objectNeptune->setTexture(TextureLoader::LoadTexture("../../Textures/2k_neptune.jpg"));

    scene->addShaderProgram(app->shaderSun);
    scene->addShaderProgram(app->shaderEarth);
    scene->addShaderProgram(app->shaderMoon);

    PointLight *sunLight = new PointLight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), 40.f);

    sunLight->attach(app->shaderEarth);
    sunLight->attach(app->shaderMoon);
    sunLight->notify();
    scene->addLight(sunLight);

    scene->addObject(app->objectSun);
    scene->addObject(app->objectEarth);
    scene->addObject(app->objectMoon);
    scene->addObject(app->objectMercury);
    scene->addObject(app->objectVenus);
    scene->addObject(app->objectMars);
    scene->addObject(app->objectJupiter);
    scene->addObject(app->objectSaturn);
    scene->addObject(app->objectUranus);
    scene->addObject(app->objectNeptune);
    scene->addObject(app->objectLogin);

    return scene;
}
