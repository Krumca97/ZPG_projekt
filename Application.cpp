#include "Application.h"
#include "DrawAbleObject.h"
#include "Model.h"
#include "Shader_program.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
#include "TransformationComponent.h"
#include "TransformationRotate.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "TransformationComposite.h"
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

int directory = 1;
float ratio;
int sceneNow = 1;
int fullScreen = 0;

static ObjectGroup* makeGroupFrom(std::string name,ShaderProgram* shader,const float* data,int vertecies,int instances)
{
    ObjectGroup* object = new ObjectGroup{};
    object->name   = name;
    object->shader = shader;              
	object->model  = new Model(6,3,3);
    std::vector<float>modelsForScene4(data, data + vertecies);
    object->model->loadData(modelsForScene4);

    for (int i = 0; i < instances; i++) {
        object->objects.push_back(new DrawAbleObject(*object->model, *object->shader));
    }
    return object;
}

void Application::error_callback(int error, const char* description) 
{ 
	fputs(description, stderr); 
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		directory *= -1;

	}

	if(key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		sceneNow =1;
	}

	if(key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		sceneNow = 2;
	}

	if(key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		sceneNow = 3;
	}

	if(key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		sceneNow = 4;
	}

	if(key == GLFW_KEY_5 && action == GLFW_PRESS)
	{
		sceneNow = 5;
	}
	if(key == GLFW_KEY_6 && action == GLFW_PRESS)
	{
		sceneNow = 6;
	}
	if(key == GLFW_KEY_7 && action == GLFW_PRESS)
	{
		sceneNow = 7;
	}

	if(key == GLFW_KEY_F11 && action == GLFW_PRESS )
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		if (!fullScreen)
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			fullScreen = 1;
		}
		else
		{
			int windowedWidth = 1280;
			int windowedHeight = 720;
			int xpos = (mode->width - windowedWidth) / 2;
			int ypos = (mode->height - windowedHeight) / 2;

			glfwSetWindowMonitor(window, NULL, xpos, ypos, windowedWidth, windowedHeight, 0);
			fullScreen = 0;
		}
	}

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
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);

    ratio = static_cast<float>(width) / static_cast<float>(height);

	Scene* activeScene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
	if (activeScene && activeScene->getCamera())
	{
		activeScene->getCamera()->setWindowRatio(ratio);
		activeScene->getCamera()->notify();
	}
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{ 
	printf("cursor_callback \n"); 
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
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
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) 
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    int width1 = 1280;
	int height1 = 720;

    if (fullScreen) 
	{
        window = glfwCreateWindow(mode->width, mode->height, "ZPG", monitor, NULL);
		glfwSetWindowSizeCallback(window, window_size_callback);
    } 
	else 
	{
        window = glfwCreateWindow(width1, height1, "ZPG", NULL, NULL);
		glfwSetWindowSizeCallback(window, window_size_callback);
    }


	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window,Application::key_callback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	int a;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &a);
	printf("Texture units: %d\n", a);

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) 
	{
		Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(win));
		if (!scene || !scene->getController())
			return;

		if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			scene->getController()->processMouse(win, x, y);
		}
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) 
	{
		Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(win));
		if (!scene || !scene->getController())
		{
			return;
		}

		Controller* ctrl = scene->getController();

		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			ctrl->setMouseEnabled(action == GLFW_PRESS);
		}
	});

	return true;
}

void Application::createShaders()
{
	//shaders purple triangle
	vertexShaderTrinagle = new Shader("../../Shaders/TriangleVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderTriangle = new Shader("../../Shaders/TriangleFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderTriangle = new ShaderProgram();
	shaderTriangle->link(*vertexShaderTrinagle,*fragmentShaderTriangle);
	shaderTriangle->setObjectColor(glm::vec3(1.f,0.f,1.f));

	//shaders spheres
	vertexShaderSphere1 = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphere1 = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphere1 = new ShaderProgram();
	shaderSphere1->link(*vertexShaderSphere1,*fragmentShaderSphere1);
	shaderSphere1->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	vertexShaderSphere2 = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphere2 = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphere2 = new ShaderProgram();
	shaderSphere2->link(*vertexShaderSphere2,*fragmentShaderSphere2);
	shaderSphere2->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	vertexShaderSphere3 = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphere3 = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphere3 = new ShaderProgram();
	shaderSphere3->link(*vertexShaderSphere3,*fragmentShaderSphere3);
	shaderSphere3->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	vertexShaderSphere4 = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphere4 = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphere4 = new ShaderProgram();
	shaderSphere4->link(*vertexShaderSphere4,*fragmentShaderSphere4);
	shaderSphere4->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	//shaders trees and bushes
	vertexShaderUniverzal = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
    fragmentShaderUniverzal = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
    shaderUniverzal = new ShaderProgram();
    shaderUniverzal->link(*vertexShaderUniverzal,*fragmentShaderUniverzal);
	shaderUniverzal->setObjectColor(glm::vec3(0.f,1.f,0.f));

	vertexShaderSphereForest = new Shader("../../Shaders/ConstantVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphereForest = new Shader("../../Shaders/ConstantFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphereForest = new ShaderProgram();
	shaderSphereForest->link(*vertexShaderSphereForest,*fragmentShaderSphereForest);
	shaderSphereForest->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	vertexShaderPlaineForest = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderPlainForest = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderPlainForest = new ShaderProgram();
	shaderPlainForest->link(*vertexShaderPlaineForest,*fragmentShaderPlainForest);
	shaderPlainForest->setObjectColor(glm::vec3(0.f,1.f,0.f));

	//shaders Solar system
	vertexShaderSun = new Shader("../../Shaders/ConstantVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSun = new Shader("../../Shaders/ConstantFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSun = new ShaderProgram();
	shaderSun->link(*vertexShaderSun,*fragmentShaderSun);
	shaderSun->setObjectColor(glm::vec3(1.f,1.f,0.f));

	vertexShaderEarth = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderEarth = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderEarth = new ShaderProgram();
	shaderEarth->link(*vertexShaderEarth,*fragmentShaderEarth);
	shaderEarth->setObjectColor(glm::vec3(0.f,0.f,1.f));

	vertexShaderMoon = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderMoon = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderMoon = new ShaderProgram();
	shaderMoon->link(*vertexShaderMoon,*fragmentShaderMoon);
	shaderMoon->setObjectColor(glm::vec3(0.9f,0.9f,0.8f));

	//formula1
	vertexShaderFormula1Texture = new Shader("../../Shaders/PhongVertexShader.vert", GL_VERTEX_SHADER);
	fragmentShaderFormula1Texture = new Shader("../../Shaders/PhongFragmentShader.frag", GL_FRAGMENT_SHADER);
	shaderFormula1Texture = new ShaderProgram();
	shaderFormula1Texture->link(*vertexShaderFormula1Texture,*fragmentShaderFormula1Texture);

	//house
	vertexShaderHouseTexture = new Shader("../../Shaders/PhongVertexShader.vert", GL_VERTEX_SHADER);
	fragmentShaderHouseTexture = new Shader("../../Shaders/PhongFragmentShader.frag", GL_FRAGMENT_SHADER);
	shaderHouseTexture = new ShaderProgram();
	shaderHouseTexture->link(*vertexShaderHouseTexture,*fragmentShaderHouseTexture);

	//Shrek
	vertexShaderShrekTexture = new Shader("../../Shaders/PhongVertexShader.vert", GL_VERTEX_SHADER);
	fragmentShaderShrekTexture = new Shader("../../Shaders/PhongFragmentShader.frag", GL_FRAGMENT_SHADER);
	shaderShrekTexture = new ShaderProgram();
	shaderShrekTexture->link(*vertexShaderShrekTexture, *fragmentShaderShrekTexture);
	shaderShrekTexture->setObjectColor(glm::vec3(1.0f));

	//Fiona
	vertexShaderFionaTexture = new Shader("../../Shaders/PhongVertexShader.vert", GL_VERTEX_SHADER);
	fragmentShaderFionaTexture = new Shader("../../Shaders/PhongFragmentShader.frag", GL_FRAGMENT_SHADER);
	shaderFionaTexture = new ShaderProgram();
	shaderFionaTexture->link(*vertexShaderFionaTexture, *fragmentShaderFionaTexture);
	shaderFionaTexture->setObjectColor(glm::vec3(1.0f));

	//Toilet
	vertexShaderToiletTexture = new Shader("../../Shaders/PhongVertexShader.vert", GL_VERTEX_SHADER);
	fragmentShaderToiletTexture = new Shader("../../Shaders/PhongFragmentShader.frag", GL_FRAGMENT_SHADER);
	shaderToiletTexture = new ShaderProgram();
	shaderToiletTexture->link(*vertexShaderToiletTexture, *fragmentShaderToiletTexture);
	shaderToiletTexture->setObjectColor(glm::vec3(1.0f));

}

void Application::createBuffers()
{
	//purple triangle
	modelTriangle = new Model(3,3,0);
	std::vector<float>triangle(pointsTriangle,pointsTriangle + sizeof(pointsTriangle)/sizeof(float));
	modelTriangle->loadData(triangle);
	objectTriangle= new DrawAbleObject(*modelTriangle, *shaderTriangle);
	
	//spheres
	modelSphere = new Model(6,3,3);
	std::vector<float>sphere1(sphere, sphere + sizeof(sphere) / sizeof(float));
	modelSphere->loadData(sphere1);
	object1Sphere = new DrawAbleObject(*modelSphere,*shaderSphere1);
	object2Sphere = new DrawAbleObject(*modelSphere,*shaderSphere2);
	object3Sphere = new DrawAbleObject(*modelSphere,*shaderSphere3);
	object4Sphere = new DrawAbleObject(*modelSphere,*shaderSphere4);

	//scene3
	groupForScene3.push_back(makeGroupFrom("Tree", shaderUniverzal, tree, sizeof(tree)/sizeof(float), 70));
	groupForScene3.push_back(makeGroupFrom("Bush", shaderUniverzal, bushes, sizeof(bushes)/sizeof(float), 80));
	objectForestSphere = new DrawAbleObject(*modelSphere,*shaderSphereForest);

	//scene 4 solar system
	modelSolarSystem = new Model(6,3,3);
	std::vector<float>solarSystem(sphere, sphere + sizeof(sphere) / sizeof(float));
	modelSolarSystem->loadData(solarSystem);
	objectSun = new DrawAbleObject(*modelSolarSystem,*shaderSun);
	objectEarth = new DrawAbleObject(*modelSolarSystem,*shaderEarth);
	objectMoon = new DrawAbleObject(*modelSolarSystem,*shaderMoon);

	//scene 5 formula1
	modelFormula1 = new Model("formula1.obj"); 
	formula1 = new DrawAbleObject(*modelFormula1, *shaderFormula1Texture);
	
	//scene 6 house
	modelHouse = new Model("house.obj");
	house = new DrawAbleObject(*modelHouse,*shaderHouseTexture);

	//Shrek, Fiona and Toilet
	modelShrek = new Model("shrek.obj");
	shrek = new DrawAbleObject(*modelShrek, *shaderShrekTexture);

	modelFiona = new Model("fiona.obj");
	fiona = new DrawAbleObject(*modelFiona, *shaderFionaTexture);

	modelToilet = new Model("toiled.obj");
	toilet = new DrawAbleObject(*modelToilet, *shaderToiletTexture);
}

void Application::buildScene()
{
	glm::mat4 view(1.0f);
	glm::mat4 proj(1.0f);

	scene1 = new Scene(view, proj,{SceneLightType::Ambient});
	scene2 = new Scene(view, proj,{SceneLightType::Directional,SceneLightType::Point,SceneLightType::Ambient,SceneLightType::Spot});
	scene3 = new Scene(view, proj,{SceneLightType::Ambient,SceneLightType::Point});
	scene4 = new Scene(view, proj,{SceneLightType::Point});
	scene5 = new Scene(view, proj, {SceneLightType::Point});
	scene6 = new Scene(view, proj, {SceneLightType::Point});
	scene7 = new Scene(view, proj, {SceneLightType::Ambient});

	scene1->setCamera(ratio);
	scene2->setCamera(ratio);
	scene3->setCamera(ratio);
	scene4->setCamera(ratio);
	scene5->setCamera(ratio);
	scene6->setCamera(ratio);
	scene7->setCamera(ratio);
	
	Material neutral(glm::vec3(0.1f),glm::vec3(1.0f),glm::vec3(1.0f),128.0f);

	//Triangle
	TransformationComposite* groupTriangle = new TransformationComposite();
	groupTriangle->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -0.0f, 0.0f), 0.0f));
	groupTriangle->addTransformation(new TransformationRotate(glm::vec3(0,0,1),0.0f, 100.f));
	objectTriangle->addTransformation(groupTriangle);
	objectTriangle->setMaterial(neutral);
	scene1->addObject(objectTriangle);

	//Spheres
	object1Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.f, 0.75f, 0.0f), 0.0f));
	object1Sphere->addTransformation(new TransformationScale(glm::vec3(0.2f, 0.2f, 0.2f), 0.0f));

	object2Sphere->addTransformation(new TransformationTranslate(glm::vec3(-0.75f, 0.f, 0.0f), 0.0f));;
	object2Sphere->addTransformation(new TransformationScale(glm::vec3(0.2f, 0.2f, 0.2f), 0.0f));

	object3Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.75f, 0.f, 0.0f), 0.0f));;
	object3Sphere->addTransformation(new TransformationScale(glm::vec3(0.2f, 0.2f, 0.2f), 0.0f));

	object4Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.f, -0.75f, 0.0f), 0.0f));;
	object4Sphere->addTransformation(new TransformationScale(glm::vec3(0.2f, 0.2f, 0.2f), 0.0f));

	object1Sphere->setMaterial(neutral);
    object2Sphere->setMaterial(neutral);
    object3Sphere->setMaterial(neutral); 
    object4Sphere->setMaterial(neutral);  

	scene2->addShaderProgram(shaderSphere1);
	scene2->addShaderProgram(shaderSphere2);
	scene2->addShaderProgram(shaderSphere3);
	scene2->addShaderProgram(shaderSphere4);

	glm::vec3 lightCenter = glm::vec3(0.0f, 0.0f, 0.0f);

	AmbientLight* ambient = new AmbientLight(glm::vec3(0.15f, 0.15f, 0.2f), 0.3f);
	ambient->attach(shaderSphere1);
	ambient->notify();
	scene2->addLight(ambient);

	PointLight* point = new PointLight(
		lightCenter + glm::vec3(0.0f, 0.7f, 0.0f), 
		glm::vec3(0.9f, 0.7f, 0.7f),
		0.25f
	);
	point->attach(shaderSphere2);
	point->notify();
	scene2->addLight(point);

	DirectionalLight* directional = new DirectionalLight(
		glm::normalize(glm::vec3(0.5f, -1.0f, 0.3f)), 
		glm::vec3(0.9f, 0.9f, 1.0f),
		0.03f
	);
	directional->attach(shaderSphere3);
	directional->notify();
	scene2->addLight(directional);

	SpotLight* spot = scene2->getSpotLight(); 
	spot->attach(shaderSphere4); 
	spot->attachCamera(scene2->getCamera()); 
	spot->notify(); 
	scene2->addLight(spot);

	scene2->addObject(object1Sphere);
	scene2->addObject(object2Sphere);
	scene2->addObject(object3Sphere);
	scene2->addObject(object4Sphere);

	//ground for scene3 
	{
		Model* plainModel = new Model(8, 3, 3);
		plainModel->loadData(std::vector<float>(plain, plain + sizeof(plain)/sizeof(float)));

		ObjectGroup* ground = new ObjectGroup();
		ground->name = "Ground";
		DrawAbleObject* plainObj = new DrawAbleObject(*plainModel, *shaderPlainForest);

		TransformationComposite* GroundGroup = new TransformationComposite();
		GroundGroup->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -0.01f, 0.0f), 1.0f));
		GroundGroup->addTransformation(new TransformationScale(glm::vec3(60.0f, 1.0f, 60.0f), 1.0f));
		plainObj->addTransformation(GroundGroup);

		plainObj->setMaterial(neutral);
		GLuint texGround = TextureLoader::LoadTexture("../../Textures/grass.png");
		plainObj->setUvScale(16.0f);
		plainObj->setTexture(texGround);

		ground->objects.push_back(plainObj);
		scene3->addObject(plainObj);
		scene3->addShaderProgram(shaderPlainForest);
    }

	//forest for scene 3
    const float areaHalf   = 25.0f;      
    const glm::vec2 center   = glm::vec2(0.0f);
    const float startRadius  = 2.5f; // free space around start pos
    const float groundY      = 0.0f;

    std::srand((unsigned)std::time(nullptr));

    for (ObjectGroup* group : groupForScene3)
    {
        for (DrawAbleObject* obj : group->objects)
        {
            float x; 
			float z;
			bool isValid = false;
			while (!isValid)
			{
				x = -areaHalf + (2.0f * areaHalf) * (std::rand() / (float)RAND_MAX);
				z = -areaHalf + (2.0f * areaHalf) * (std::rand() / (float)RAND_MAX);

				float distance = glm::length(glm::vec2(x, z) - center);
				if(distance >= startRadius)
				{
					isValid = true;
				}
				else
				{
					isValid = false;
				}
			}

            float minSize = 0.6f;
			float maxSize = 1.4f;      
            if (group->name == "Bush") 
			{ 
				minSize = 0.3f; 
				maxSize = 0.8f; 
			}
            float size = minSize + (maxSize - minSize) * (std::rand() / (float)RAND_MAX);


            float randomAngle = -180.f + 360.f * (std::rand() / (float)RAND_MAX);
            float angleInRadians = glm::radians(randomAngle);

            TransformationComposite* transGroup3 = new TransformationComposite();
            transGroup3->addTransformation(new TransformationTranslate(glm::vec3(x, groundY, z), 1.0f));
            transGroup3->addTransformation(new TransformationRotate(glm::vec3(0,1,0), randomAngle, 0.0f));
            transGroup3->addTransformation(new TransformationScale(glm::vec3(size), 1.0f));
            obj->addTransformation(transGroup3);

            obj->setMaterial(neutral);



            scene3->addObject(obj);
			scene3->addShaderProgram(shaderUniverzal);

        }
    }

	//Shrek
	TransformationComposite* shrekTransform = new TransformationComposite();
	shrekTransform->addTransformation(new TransformationTranslate(glm::vec3(-6.0f, 0.0f, -8.0f), 0.0f));
	shrek->addTransformation(shrekTransform);
	shrek->setMaterial(neutral);

	GLuint texShrek = TextureLoader::LoadTexture("../../Textures/shrek.png");
	shrek->setTexture(texShrek);

	scene3->addShaderProgram(shaderShrekTexture);
	scene3->addObject(shrek);

	//Fiona
	TransformationComposite* fionaTransform = new TransformationComposite();
	fionaTransform->addTransformation(new TransformationTranslate(glm::vec3(-3.0f, 0.0f, -8.0f), 0.0f));
	fiona->addTransformation(fionaTransform);
	fiona->setMaterial(neutral);

	GLuint texFiona = TextureLoader::LoadTexture("../../Textures/fiona.png");
	fiona->setTexture(texFiona);

	scene3->addShaderProgram(shaderFionaTexture);
	scene3->addObject(fiona);

	//Toilet
	TransformationComposite* toiletTransform = new TransformationComposite();
	toiletTransform->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, -8.0f), 0.0f));
	toiletTransform->addTransformation(new TransformationScale(glm::vec3(0.5f), 0.0f));
	toilet->addTransformation(toiletTransform);
	toilet->setMaterial(neutral);

	GLuint texToilet = TextureLoader::LoadTexture("../../Textures/toiled.jpg");
	toilet->setTexture(texToilet);

	scene3->addShaderProgram(shaderToiletTexture);
	scene3->addObject(toilet);

	PointLight* lightShrekFionaToilet = new PointLight(
	glm::vec3(0.0f, 5.0f, -8.0f),
	glm::vec3(1.0f, 0.95f, 0.8f),
	20.0f
	);
	lightShrekFionaToilet->attach(shaderShrekTexture);
	lightShrekFionaToilet->attach(shaderFionaTexture);
	lightShrekFionaToilet->attach(shaderToiletTexture);
	lightShrekFionaToilet->notify();
	scene3->addLight(lightShrekFionaToilet);

	scene3->buildFireflies(modelSphere, shaderSphereForest,scene3);

	//solar system for scene 4
	TransformationComposite* transGroupSun = new TransformationComposite();
	transGroupSun->addTransformation(new TransformationScale(glm::vec3(2.f), 0.f));  
	transGroupSun->addTransformation(new TransformationRotate(glm::vec3(0.f, 1.f, 0.f), 0.f, 8.f)); 
	objectSun->addTransformation(transGroupSun);

	TransformationComposite* transGroupEarth = new TransformationComposite();
	transGroupEarth->addTransformation(new TransformationRotate(glm::vec3(0.f, 1.f, 0.f), 0.f, 12.f));  
	transGroupEarth->addTransformation(new TransformationTranslate(glm::vec3(6.f, 0.f, 0.f), 0.f));     
	transGroupEarth->addTransformation(new TransformationRotate(glm::vec3(0.f, 1.f, 0.f), 0.f, 80.f));
	transGroupEarth->addTransformation(new TransformationScale(glm::vec3(0.7f), 0.f));
	objectEarth->addTransformation(transGroupEarth);
	objectEarth->setParentSpace(objectSun);

	TransformationComposite* transGroupMoon = new TransformationComposite();
	transGroupMoon->addTransformation(new TransformationRotate(glm::vec3(0.f, 1.f, 0.f), 0.f, 50.f));  
	transGroupMoon->addTransformation(new TransformationTranslate(glm::vec3(3.f, 0.f, 0.f), 0.f));     
	transGroupMoon->addTransformation(new TransformationRotate(glm::vec3(0.f, 1.f, 0.f), 0.f, 50.f));   
	transGroupMoon->addTransformation(new TransformationScale(glm::vec3(0.3f), 0.f)); 
	objectMoon->addTransformation(transGroupMoon);
	objectMoon->setParentSpace(objectEarth);

	objectSun->setMaterial(neutral);  
    objectEarth->setMaterial(neutral);
    objectMoon->setMaterial(neutral);

	scene4->addShaderProgram(shaderSun);
	scene4->addShaderProgram(shaderEarth);
	scene4->addShaderProgram(shaderMoon);
	PointLight* sunLight = new PointLight(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1.0f, 1.0f, 1.0f), 10.0f);
	sunLight->attach(shaderEarth);
	sunLight->attach(shaderMoon);
	sunLight->notify();
	scene4->addLight(sunLight);
	scene4->addObject(objectSun);
	scene4->addObject(objectEarth);
	scene4->addObject(objectMoon);

	//scene 5 formula
	scene5->addShaderProgram(shaderFormula1Texture);
	TransformationComposite* formulaTransform = new TransformationComposite();
	formulaTransform->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, -5.0f), 0.0f));
	formula1->addTransformation(formulaTransform);
	formula1->setMaterial(neutral);

	PointLight* pointFormula = new PointLight(
		glm::vec3(0.0f, 15.0f, -5.0f),    
		glm::vec3(1.0f, 1.0f, 1.0f),
		3.0f
	);

	pointFormula->attach(shaderFormula1Texture);
	pointFormula->notify();
	scene5->addLight(pointFormula);

	GLuint texFormula = TextureLoader::LoadTexture("../../Textures/wooden_fence.png");
	formula1->setTexture(texFormula);
	scene5->addObject(formula1);

	//scena6 house
	scene6->addShaderProgram(shaderHouseTexture);
	TransformationComposite* houseTransform = new TransformationComposite();
	houseTransform->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -1.0f, -10.0f), 0.0f));
	houseTransform->addTransformation(new TransformationScale(glm::vec3(0.5f), 0.0f));
	house->addTransformation(houseTransform);
	house->setMaterial(neutral);

	PointLight* lightHouse = new PointLight(
		glm::vec3(5.f, 10.f, 5.f),
		glm::vec3(1.f, 1.f, 1.f),
		10.f
	);
	lightHouse->attach(shaderHouseTexture);
	lightHouse->notify();
	scene6->addLight(lightHouse);

	GLuint texHouse = TextureLoader::LoadTexture("../../Textures/grass.png");
	house->setTexture(texHouse);
	scene6->addObject(house);
	scene6->addShaderProgram(shaderHouseTexture);
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
				printf("Scene1");
				sceneActual = scene1;
				break;
			case 2:
				printf("Scene2");
				sceneActual = scene2;
				break;
			case 3:
				printf("Scene3");
				sceneActual = scene3;
				break;
			case 4:
				printf("Scene4");
				sceneActual = scene4;
				break;
			case 5:
				printf("Scene5");
				sceneActual = scene5;
				break;
			case 6:
				printf("Scene6");
				sceneActual = scene6;
				break;
			}
			lastScene = sceneNow;
		}

		glfwSetWindowUserPointer(window, sceneActual);
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
		else
		{
			sceneActual->updateLights(0);
		}
		sceneActual->drawScene();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}



