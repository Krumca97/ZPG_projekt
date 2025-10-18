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
	if(key == GLFW_KEY_F && action == GLFW_PRESS )
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

    Controller* ctrl = static_cast<Controller*>(glfwGetWindowUserPointer(window));
    if (ctrl && ctrl->getCamera())
    {
        ctrl->getCamera()->setWindowRatio(ratio);
        ctrl->getCamera()->notify();
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
	if (!glfwInit()) {
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

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	// int width, height;
	// glfwGetFramebufferSize(window, &width, &height);
	// ratio = width / (float)height;
	// glViewport(0, 0, width, height);

	camera = new CameraSubject(glm::vec3(0.f, 1.7f, 3.f),glm::quat(1.f, 0.f, 0.f, 0.f),glm::vec3(0.f, 1.f, 0.f),60.f, ratio,0.1f, 100.f,2.5f, 0.1f);
	controller = new Controller(camera);

	glfwSetWindowUserPointer(window, controller);
	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) 
	{
		Controller* ctrl = static_cast<Controller*>(glfwGetWindowUserPointer(win));
		if (ctrl) 
		{
			ctrl->processMouse(win, x, y);
		}
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) 
	{
		Controller* ctrl = static_cast<Controller*>(glfwGetWindowUserPointer(win));
		if (!ctrl) 
		{
			return;
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT) 
		{
			ctrl->setMouseEnabled(action == GLFW_PRESS);
			if (action == GLFW_PRESS)
			{
				glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			else
			{
				glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
	});

	light = new LightSubject(
		glm::vec3(0.f,0.f,0.f),
		glm::vec3(0.7f,0.8f,1.f),
		1.f
	);

	return true;
}

void Application::createShaders()
{
	//shadery pro fialovy trojuhelnik
	vertexShaderTrinagle = new Shader("../../Shaders/TriangleVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderTriangle = new Shader("../../Shaders/TriangleFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderTriangle = new ShaderProgram();
	shaderTriangle->link(*vertexShaderTrinagle,*fragmentShaderTriangle);
	shaderTriangle->setObjectColor(glm::vec3(1.f,0.f,1.f));

	//shadery pro kulicky
	vertexShaderSphere1 = new Shader("../../Shaders/ConstantVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphere1 = new Shader("../../Shaders/ConstantFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphere1 = new ShaderProgram();
	shaderSphere1->link(*vertexShaderSphere1,*fragmentShaderSphere1);
	shaderSphere1->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	vertexShaderSphere2 = new Shader("../../Shaders/LambertVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphere2 = new Shader("../../Shaders/LambertFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphere2 = new ShaderProgram();
	shaderSphere2->link(*vertexShaderSphere2,*fragmentShaderSphere2);
	shaderSphere2->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	vertexShaderSphere3 = new Shader("../../Shaders/PhongVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphere3 = new Shader("../../Shaders/PhongFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphere3 = new ShaderProgram();
	shaderSphere3->link(*vertexShaderSphere3,*fragmentShaderSphere3);
	shaderSphere3->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	vertexShaderSphere4 = new Shader("../../Shaders/BlinnPhonVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSphere4 = new Shader("../../Shaders/BlinnPhonFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSphere4 = new ShaderProgram();
	shaderSphere4->link(*vertexShaderSphere4,*fragmentShaderSphere4);
	shaderSphere4->setObjectColor(glm::vec3(0.7f,0.8f,1.f));

	//univerzalni shader
	vertexShaderUniverzal = new Shader("../../Shaders/UniverzalVertexShader.vert",GL_VERTEX_SHADER);
    fragmentShaderUniverzal = new Shader("../../Shaders/UniverzalFragmentShader.frag",GL_FRAGMENT_SHADER);
    shaderUniverzal = new ShaderProgram();
    shaderUniverzal->link(*vertexShaderUniverzal,*fragmentShaderUniverzal);

	//slunecni soustava shadery
	vertexShaderSun = new Shader("../../Shaders/ConstantVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderSun = new Shader("../../Shaders/ConstantFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderSun = new ShaderProgram();
	shaderSun->link(*vertexShaderSun,*fragmentShaderSun);
	shaderSun->setObjectColor(glm::vec3(1.f,1.f,0.f));

	vertexShaderEarth = new Shader("../../Shaders/BlinnPhonVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderEarth = new Shader("../../Shaders/BlinnPhonFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderEarth = new ShaderProgram();
	shaderEarth->link(*vertexShaderEarth,*fragmentShaderEarth);
	shaderEarth->setObjectColor(glm::vec3(0.f,0.f,1.f));

	vertexShaderMoon = new Shader("../../Shaders/BlinnPhonVertexShader.vert",GL_VERTEX_SHADER);
	fragmentShaderMoon = new Shader("../../Shaders/BlinnPhonFragmentShader.frag",GL_FRAGMENT_SHADER);
	shaderMoon = new ShaderProgram();
	shaderMoon->link(*vertexShaderMoon,*fragmentShaderMoon);
	shaderMoon->setObjectColor(glm::vec3(0.9f,0.9f,0.8f));

	//pridani do kamery
	camera->attach(shaderTriangle);
	camera->attach(shaderSphere1);
	camera->attach(shaderSphere2);
	camera->attach(shaderSphere3);
	camera->attach(shaderSphere4);
	camera->attach(shaderUniverzal);

	camera->attach(shaderSun);
	camera->attach(shaderEarth);
	camera->attach(shaderMoon);

	//pridani svetla
	light->attach(shaderTriangle);
	light->attach(shaderSphere1);
	light->attach(shaderSphere2);
	light->attach(shaderSphere3);
	light->attach(shaderSphere4);

	light->attach(shaderSun);
	light->attach(shaderEarth);
	light->attach(shaderMoon);

	camera->notify();
	light->notify();
}

void Application::createBuffers()
{
	//fialovy trojuhelnik
	modelTriangle = new Model(3,3,0);
	std::vector<float>triangle(pointsTriangle,pointsTriangle + sizeof(pointsTriangle)/sizeof(float));
	modelTriangle->loadData(triangle);
	objectTriangle= new DrawAbleObject(*modelTriangle, *shaderTriangle);
	
	//kulicky 
	modelSphere = new Model(6,3,3);
	std::vector<float>sphere1(sphere, sphere + sizeof(sphere) / sizeof(float));
	modelSphere->loadData(sphere1);
	object1Sphere = new DrawAbleObject(*modelSphere,*shaderSphere1);
	object2Sphere = new DrawAbleObject(*modelSphere,*shaderSphere2);
	object3Sphere = new DrawAbleObject(*modelSphere,*shaderSphere3);
	object4Sphere = new DrawAbleObject(*modelSphere,*shaderSphere4);

	//scena3
	groupForScene3.push_back(makeGroupFrom("Tree", shaderUniverzal, tree, sizeof(tree)/sizeof(float), 70));
	groupForScene3.push_back(makeGroupFrom("Bush", shaderUniverzal, bushes, sizeof(bushes)/sizeof(float), 80));

	//scena 4 solar system
	modelSolarSystem = new Model(6,3,3);
	std::vector<float>solarSystem(sphere, sphere + sizeof(sphere) / sizeof(float));
	modelSolarSystem->loadData(solarSystem);
	objectSun = new DrawAbleObject(*modelSolarSystem,*shaderSun);
	objectEarth = new DrawAbleObject(*modelSolarSystem,*shaderEarth);
	objectMoon = new DrawAbleObject(*modelSolarSystem,*shaderMoon);
}

void Application::buildScene()
{
	glm::mat4 proj = camera->projectionMatrix();
	glm::mat4 view = camera->getCamera();

	scene1 = new Scene(view,proj);
	scene2 = new Scene(view,proj);
	scene3 = new Scene(view,proj);
	scene4 = new Scene(view,proj);

	//barevny trojuhelnik
	TransformationComposite* groupTriangle = new TransformationComposite();
	groupTriangle->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -0.0f, 0.0f), 0.0f));
	groupTriangle->addTransformation(new TransformationRotate(glm::vec3(0,0,1),0.0f, 100.f));
	objectTriangle->addTransformation(groupTriangle);
	scene1->addObject(objectTriangle);

	//kulicky
	object1Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.f, 0.75f, 0.0f), 0.0f));
	object1Sphere->addTransformation(new TransformationScale(glm::vec3(0.2f, 0.2f, 0.2f), 0.0f));

	object2Sphere->addTransformation(new TransformationTranslate(glm::vec3(-0.75f, 0.f, 0.0f), 0.0f));;
	object2Sphere->addTransformation(new TransformationScale(glm::vec3(0.2f, 0.2f, 0.2f), 0.0f));

	object3Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.75f, 0.f, 0.0f), 0.0f));;
	object3Sphere->addTransformation(new TransformationScale(glm::vec3(0.2f, 0.2f, 0.2f), 0.0f));

	object4Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.f, -0.75f, 0.0f), 0.0f));;
	object4Sphere->addTransformation(new TransformationScale(glm::vec3(0.2f, 0.2f, 0.2f), 0.0f));

	scene2->addObject(object1Sphere);
	scene2->addObject(object2Sphere);
	scene2->addObject(object3Sphere);
	scene2->addObject(object4Sphere);

	//podlaha pro scenu 3
	{
        ObjectGroup* ground = makeGroupFrom("Ground", shaderUniverzal, plain, sizeof(plain)/sizeof(float), 1);
        TransformationComposite* froundGroup = new TransformationComposite();
        froundGroup->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -0.01f, 0.0f), 1.0f));
        froundGroup->addTransformation(new TransformationScale(glm::vec3(60.0f, 1.0f, 60.0f), 1.0f));
        ground->objects[0]->addTransformation(froundGroup);
        scene3->addObject(ground->objects[0]);
    }


	//vytvoreni lesa scena 3
    const float areaHalf   = 25.0f;      
    const glm::vec2 center   = glm::vec2(0.0f);
    const float startRadius  = 2.5f;       // volný prostor kolem startu
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

            scene3->addObject(obj);
        }
    }

	//vytvoreni solar system pr osceny 4
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

	scene4->addObject(objectSun);
	scene4->addObject(objectEarth);
	scene4->addObject(objectMoon);
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
			}
			//sceneActual->reset();
			lastScene = sceneNow;
		}

		controller->processKeyboard(window, deltaTime);

		glm::mat4 view = camera->getCamera();
		glm::mat4 proj = camera->projectionMatrix();
		
		sceneActual->setView(view);
		sceneActual->setProjection(proj);
		sceneActual->drawScene();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}



