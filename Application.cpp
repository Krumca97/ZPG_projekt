#include "Application.h"
#include "DrawAbleObject.h"
#include "Model.h"
#include "Shader_program.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
#include "Transformations/TransformationComponent.h"
#include "Transformations/TransformationRotate.h"
#include "Transformations/TransformationScale.h"
#include "Transformations/TransformationTranslate.h"
#include "Transformations/TransformationCustom.h"
#include "Transformations/TransformationComposite.h"
#include "TextureLoader.h"
#include <ctime>
#include <iostream>

#include "Models/bushes.h"
#include "Models/sphere.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/triangle.h"

#include "Lights/AmbientLight.h"
#include "Lights/PointLight.h"
#include "Lights/DirectionalLight.h"
#include "Lights/SpotLight.h"

#include "Scenes/Scene1.h"
#include "Scenes/Scene2.h"
#include "Scenes/Scene3.h"
#include "Scenes/Scene4.h"
#include "Scenes/Scene5.h"
#include "Scenes/Scene6.h"
#include "Scenes/Scene7.h"


float ratio;
int fullScreen = 0;

bool Application::isObjectMoving()
{ 
    return isMovingObject; 
};

DrawAbleObject* Application::getMovingObject()
{ 
    return movingObject;
}

void Application::error_callback(int error, const char* description) 
{ 
	fputs(description, stderr); 
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS) 
	{
		return;
	}

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app) 
	{
		return;
	}

    if (key == GLFW_KEY_ESCAPE) 
	{ 
		glfwSetWindowShouldClose(window, GL_TRUE); 
		return; 
	}

    switch (key)
    {
        case GLFW_KEY_1:
            app->switchScene(1); 
            break;
        case GLFW_KEY_2:           
            app->switchScene(2); 
            break;
        case GLFW_KEY_3:           
            app->switchScene(3); 
            break;
        case GLFW_KEY_4:           
            app->switchScene(4); 
            break;
        case GLFW_KEY_5:           
            app->switchScene(5); 
            break;
        case GLFW_KEY_6:           
            app->switchScene(6); 
            break;
        case GLFW_KEY_7:           
            app->switchScene(7); 
            break;
        case GLFW_KEY_F11:         
            app->toggleFullscreen(window); 
            break;
        case GLFW_KEY_ENTER:       
            app->toggleMoveMode(); 
            break;
        case GLFW_KEY_T:           
            app->togglePlantingMode(); 
            break;
        case GLFW_KEY_M:           
            app->restartShellGame(); 
            break;
    }
}

void Application::switchScene(int scene)
{
    sceneNow = scene;
}

void Application::toggleFullscreen(GLFWwindow* window)
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    if (!fullScreen)
    {
        glfwSetWindowMonitor(window, monitor, 0, 0,mode->width, mode->height, mode->refreshRate);fullScreen = 1;
    }
    else
    {
        int windowedWidth = 1280, windowedHeight = 720;
        int xpos = (mode->width - windowedWidth) / 2;
        int ypos = (mode->height - windowedHeight) / 2;

        glfwSetWindowMonitor(window, NULL, xpos, ypos,windowedWidth, windowedHeight, 0);
        fullScreen = 0;
    }
}

void Application::toggleMoveMode()
{
    if (!sceneActual) 
	{
		return;
	}

    if (!isMovingObject)
    {
        DrawAbleObject* selected = sceneActual->getSelected();
        if (selected)
        {
            printf("MOVING MODE ENABLED\n");
            movingObject = selected;
            isMovingObject = true;
        }
    }
    else
    {
        printf("MOVING MODE DISABLED\n");
        isMovingObject = false;
        movingObject = nullptr;
    }
}

void Application::togglePlantingMode()
{
    plantingMode = !plantingMode;

    if (plantingMode)
	{
        printf("PLANTING MODE ENABLED\n");
	}
    else
    {   
		printf("PLANTING MODE DISABLED\n");
	}
}

void Application::restartShellGame()
{
    if (!cup1 || !cup2 || !cup3 || !ballTranslate) 
	{
		return;
	}

    ball->setVisible(false);

    liftCup1->setDirection(glm::vec3(0));
    liftCup2->setDirection(glm::vec3(0));
    liftCup3->setDirection(glm::vec3(0));

    lifted1 = lifted2 = lifted3 = false;

    mixing = true;
    mixTime = 0;
    path1->setActive(true);
    path2->setActive(true);
    path3->setActive(true);

    int randomSlot = rand() % 3;
    glm::vec3 positions[3] = {
        {-50.5f, -1.8f, 0},
        {  0.0f, -1.8f, 0},
        { 50.5f, -1.8f, 0}
    };

    ballTranslate->setDirection(positions[randomSlot]);
    ballSlot = randomSlot;
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{ 
	printf("window_focus_callback \n"); 
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{ 
	printf("window_iconify_callback \n"); 
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) 
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app || !app->sceneActual)
	{ 
		return;
	}

    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);

    float ratio = static_cast<float>(width) / static_cast<float>(height);

    CameraSubject* cam = app->sceneActual->getCamera();
    if (cam)
    {
        cam->setWindowRatio(ratio);
        cam->setResolution(width, height);
        cam->notify();
    }
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{ 
	printf("cursor_callback \n"); 
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS)
	{
	 	printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
}

void Application::check()
{
	if (!this->initialization())
	{
		exit(EXIT_FAILURE);
	}

}

bool Application::initialization()
{
    if (!initGLFW())
	{ 
		return false;
	}
    initCallbacks();
    return true;
}

bool Application::initGLFW()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return false;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS,   mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS,  mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    int w = 1280, h = 720;

    if (fullScreen)
	{
        window = glfwCreateWindow(mode->width, mode->height, "ZPG", monitor, nullptr);
	}
    else
    { 
		window = glfwCreateWindow(w, h, "ZPG", nullptr, nullptr);
	}

    if (!window)
    {
        fprintf(stderr, "ERROR: cannot create window\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, Application::key_callback);

    int fbw, fbh;
    glfwGetFramebufferSize(window, &fbw, &fbh);
    ratio = float(fbw) / float(fbh);

    // GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    int texUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texUnits);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    return true;
}

void Application::initCallbacks()
{
    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
        if (app)
		{ 
			app->onMouseMove(x, y);
		}
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
        if (app)
		{ 
			app->onMouseButton(button, action, mods);
		}
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int width, int height)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
        if (app) 
		{
			app->onResize(width, height);
		}
    });

    glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
        if (app)
		{ 
			app->onKey(key, action, mods);
		}
    });
}

void Application::onResize(int width, int height)
{
    glViewport(0, 0, width, height);

    ratio = float(width) / float(height);

    if (sceneActual && sceneActual->getCamera())
    {
        auto cam = sceneActual->getCamera();
        cam->setResolution(width, height);
        cam->setWindowRatio(ratio);
        cam->notify();
    }
}

void Application::onMouseMove(double x, double y)
{
    if (!sceneActual) return;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (sceneActual->getController())
		{
            sceneActual->getController()->processMouse(window, x, y);
		}
    }

    if (isMovingObject && movingObject)
    {
        moveObjectUnderCursor(x, y);
    }
}

void Application::onMouseButton(int button, int action, int mods)
{
    if (!sceneActual) return;

    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (sceneActual->getController())
		{
            sceneActual->getController()->setMouseEnabled(action == GLFW_PRESS);
		}
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        handleLeftClick();
    }
}

void Application::onKey(int key, int action, int mods)
{
    Application::key_callback(window, key, 0, action, mods);
}

void Application::moveObjectUnderCursor(double mx, double my)
{
    Scene* scene = sceneActual;
    if (!scene || !scene->getCamera())
	{ 
		return;
	}

    int mouseX = (int)mx;
    int mouseY = (int)my;

    int newY = scene->getCamera()->getResolution().y - mouseY;

    float depth;
    glReadPixels(mouseX, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    glm::vec4 viewport(0, 0,scene->getCamera()->getResolution().x,scene->getCamera()->getResolution().y);
    glm::vec3 screen(mouseX, newY, 0.99f);
    glm::vec3 world = glm::unProject(screen,scene->getCamera()->getViewMatrix(),scene->getCamera()->projectionMatrix(),viewport);

    world.y = 0.0f;

    movingObject->clearTransformation();
    auto* move = new TransformationComposite();
    move->addTransformation(new TransformationTranslate(world, 1.0f));
    movingObject->addTransformation(move);
}

void Application::handleLeftClick()
{
    if (!sceneActual || !sceneActual->getCamera())
	{
        return;
	}

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int x = (int)xpos;
    int y = (int)ypos;

    int newy = sceneActual->getCamera()->getResolution().y - y;

    GLbyte color[4];
    GLfloat depth;
    GLuint index;

    glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    printf("Clicked pixel %d, %d | RGBA %02hhx%02hhx%02hhx%02hhx | depth %f | ID %u\n",x, y, color[0], color[1], color[2], color[3], depth, index);

    glm::vec3 screen(x, newy, depth);
    glm::vec4 viewport(0, 0,sceneActual->getCamera()->getResolution().x,sceneActual->getCamera()->getResolution().y);

    glm::vec3 world = glm::unProject(screen,sceneActual->getCamera()->getViewMatrix(),sceneActual->getCamera()->projectionMatrix(),viewport);

    if (plantingMode)
    {
        world.y = 0.0f;
        sceneActual->plantTree(world);
        return;
    }

    if (index > 0)
    {
        sceneActual->setSelect(index);
    }

    if (sceneNow == 7)
    {
        if (gameOver || !waitingForGuess)
		{
            return;
		}

        int clickedSlot = -1;

        if (index == cup1->getId()) 
		{
			clickedSlot = 0;
		}
        else if (index == cup2->getId()) 
		{
			clickedSlot = 1;
		}
        else if (index == cup3->getId()) 
		{
			clickedSlot = 2;
		}

        if (clickedSlot == -1)
		{
            return;
		}

        if (clickedSlot == 0)
		{      
			liftCup1->setDirection(glm::vec3(0, -1.0f, 0));
		}
        else if (clickedSlot == 1)
		{ 
			liftCup2->setDirection(glm::vec3(0, -1.0f, 0));
		}
        else if (clickedSlot == 2) 
		{
			liftCup3->setDirection(glm::vec3(0, -1.0f, 0));
		}

        if (clickedSlot == ballSlot)
        {
            printf("Correct!\n+1 point\n");
            score++;
        }
        else
        {
            printf("GAME OVER! Ball was under cup %d\n", ballSlot + 1);
            printf("Final score = %d\n", score);
            gameOver = true;
        }

        waitingForGuess = false;
    }
}

void Application::createShaders()
{
	//shaders purple triangle
    shaderTriangle = createShaderProgram("../../Shaders/TriangleVertexShader.vert","../../Shaders/TriangleFragmentShader.frag",glm::vec3(1.f, 0.f, 1.f));

	//shaders spheres
    shaderSphere1 = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.7f, 0.8f, 1.f));
    shaderSphere2 = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.7f, 0.8f, 1.f));
    shaderSphere3 = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.7f, 0.8f, 1.f));
    shaderSphere4 = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.7f, 0.8f, 1.f));

	//shaders trees and bushes
 	shaderUniverzal = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.f, 1.f, 0.f));
    shaderSphereForest = createShaderProgram("../../Shaders/ConstantVertexShader.vert","../../Shaders/ConstantFragmentShader.frag",glm::vec3(0.7f, 0.8f, 1.f));
    shaderPlainForest = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.f, 1.f, 0.f));

	//shaders Solar system
    shaderSun = createShaderProgram("../../Shaders/ConstantVertexShader.vert","../../Shaders/ConstantFragmentShader.frag",glm::vec3(1.f, 1.f, 0.f));
    shaderEarth = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.f, 0.f, 1.f));
    shaderMoon = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.9f,0.9f,0.8f));

	//formula1
    shaderFormula1Texture = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag");

	//house
    shaderHouseTexture = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag");

	//Shrek,Fion,Toilet
    shaderShrekTexture = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(1.f));
    shaderFionaTexture = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(1.f));
    shaderToiletTexture = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(1.f));

	//shell game
    shaderCup = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(1.0f, 0.8f, 0.1f));
    shaderBall = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(0.0f, 1.0f, 0.0f));
    shaderTable = createShaderProgram("../../Shaders/PhongVertexShader.vert","../../Shaders/PhongFragmentShader.frag",glm::vec3(1.f));
}

void Application::createBuffers()
{
	//purple triangle
	objectTriangle = createModelAndObjectFromData(3,3,0,sizeof(pointsTriangle) / sizeof(float),pointsTriangle,shaderTriangle);
	modelTriangle = objectTriangle->getModel();
	
	//spheres
	object1Sphere = createModelAndObjectFromData(6,3,3, sizeof(sphere)/sizeof(float), sphere, shaderSphere1);
	object2Sphere = createModelAndObjectFromData(6,3,3, sizeof(sphere)/sizeof(float), sphere, shaderSphere2);
	object3Sphere = createModelAndObjectFromData(6,3,3, sizeof(sphere)/sizeof(float), sphere, shaderSphere3);
	object4Sphere = createModelAndObjectFromData(6,3,3, sizeof(sphere)/sizeof(float), sphere, shaderSphere4);
	modelSphere = object1Sphere->getModel();

	//scene3
    groupForScene3.push_back(createObjectGroup("Tree", shaderUniverzal, tree, sizeof(tree)/sizeof(float), 70));
    groupForScene3.push_back(createObjectGroup("Bush", shaderUniverzal, bushes, sizeof(bushes)/sizeof(float), 80));

	//scene 4 solar system
    objectSun = createModelAndObjectFromFile("sphere.obj", shaderSun);
    objectEarth = createModelAndObjectFromFile("sphere.obj", shaderEarth);
    objectMoon = createModelAndObjectFromFile("sphere.obj", shaderMoon);

    objectMercury = createModelAndObjectFromFile("sphere.obj", shaderEarth);
    objectVenus = createModelAndObjectFromFile("sphere.obj", shaderEarth);
    objectMars = createModelAndObjectFromFile("sphere.obj", shaderEarth);
    objectJupiter = createModelAndObjectFromFile("sphere.obj", shaderEarth);
    objectSaturn = createModelAndObjectFromFile("sphere.obj", shaderEarth);
    objectUranus = createModelAndObjectFromFile("sphere.obj", shaderEarth);
    objectNeptune = createModelAndObjectFromFile("sphere.obj", shaderEarth);

    objectMoonJupiter1 = createModelAndObjectFromFile("sphere.obj", shaderMoon);
    objectMoonJupiter2 = createModelAndObjectFromFile("sphere.obj", shaderMoon);
    objectMoonSaturn1 = createModelAndObjectFromFile("sphere.obj", shaderMoon);
    objectMoonSaturn2 = createModelAndObjectFromFile("sphere.obj", shaderMoon);

	//scene 5 formula1
	formula1 = createModelAndObjectFromFile("formula1.obj", shaderFormula1Texture);

	//scene 6 house
	house = createModelAndObjectFromFile("house.obj", shaderHouseTexture);

	//Shrek, Fiona and Toilet
    shrek = createModelAndObjectFromFile("shrek.obj",  shaderShrekTexture);
    fiona = createModelAndObjectFromFile("fiona.obj",  shaderFionaTexture);
    toilet = createModelAndObjectFromFile("toiled.obj", shaderToiletTexture);

	//shell game
    cup1 = createModelAndObjectFromFile("plastic_cup.obj", shaderCup);
    cup2 = createModelAndObjectFromFile("plastic_cup.obj", shaderCup);
    cup3 = createModelAndObjectFromFile("plastic_cup.obj", shaderCup);
    ball = createModelAndObjectFromFile("sphere.obj", shaderBall);
    table = createModelAndObjectFromFile("table.obj",  shaderTable);
}

void Application::buildScene()
{
	scene1 = Scene1::Build(this);
	scene2 = Scene2::Build(this);
	scene3 = Scene3::Build(this);
	scene4 = Scene4::Build(this);
	scene5 = Scene5::Build(this);
	scene6 = Scene6::Build(this);
	scene7 = Scene7::Build(this);

	scene1->setCamera(ratio);
	scene2->setCamera(ratio);
	scene3->setCamera(ratio);
	scene4->setCamera(ratio);
	scene5->setCamera(ratio);
	scene6->setCamera(ratio);
	scene7->setCamera(ratio);
}

float angle= 0.0f;
float deltaTime = 0.0f;
float currentTime = 0.0f;
float previousTime = 0.0f;

void Application::run()
{
	int lastScene = 0;
	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		previousTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		if(sceneNow != lastScene)
		{
			switch (sceneNow)
			{
			case 1:
				sceneActual = scene1;
				break;
			case 2:
				sceneActual = scene2;
				break;
			case 3:
				sceneActual = scene3;
				break;
			case 4:
				sceneActual = scene4;
				break;
			case 5:
				sceneActual = scene5;
				break;
			case 6:
				sceneActual = scene6;
				break;
			case 7:
				sceneActual = scene7;
				break;
			}
			lastScene = sceneNow;
		}

		glfwSetWindowUserPointer(window, this);
		sceneActual->updateCamera(window, deltaTime);

		if (sceneNow == 3)
		{	
			sceneActual->updateFireflies();
			sceneActual->updateLights(1);
		}
		else if(sceneNow == 4)
		{
			sceneActual->updateLights(1);
		}
		else if (sceneNow == 7) 
		{
			if (mixing)
			{
				mixTime += deltaTime;
				path1->update(deltaTime);
				path2->update(deltaTime);
				path3->update(deltaTime);

				if (mixTime >= 4.0f)
				{
					mixing = false;

					path1->setActive(false);
					path2->setActive(false);
					path3->setActive(false);

					ballTranslate->setDirection(glm::vec3(0.0f, -1.8f, 0.0f));

					int randomSlot = rand() % 3;
					ballSlot = randomSlot;

					glm::vec3 ballPositions[3] = {
						glm::vec3(-50.5f, -1.8, 0),
						glm::vec3( 0.0f, -1.8, 0),
						glm::vec3( 50.5f, -1.8, 0)
					};

					ballTranslate->setDirection(ballPositions[randomSlot]);

					ball->setVisible(true);

					waitingForGuess = true;
					gameOver = false;

					printf("Guess under which cup is the ball\n");
				}
			}
			sceneActual->updateLights(1);
		}
		else
		{
			sceneActual->updateLights(0);
		}
		sceneActual->drawSceneStencil();
		sceneActual->drawScene();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}



