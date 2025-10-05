#include "Application.h"
#include "DrawAbleObject.h"
#include "Model.h"
#include "Shader_program.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
#include "Transformation.h"
#include "TransformationRotate.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "TransformationGroup.h"
#include <ctime>
#include <iostream>

#include "Models/bushes.h"
#include "Models/sphere.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"

//trojuhelnik
float points_triangle[] = 
{
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

//ctverec
float points_square[] = 
{
	-0.95f, -0.95f, 0.0f,
	-0.95f, -0.75f, 0.0f,
	-0.75f, -0.95f, 0.0f,

	-0.75f, -0.95f, 0.0f,
	-0.95f, -0.75f, 0.0f,
	-0.75f, -0.75f, 0.0f
};

//ctverec 
float points_rectangle[] =
{
	0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  
	-0.5f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,

	-0.5f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
	0.0f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f
};


//vertex shader
const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"uniform mat4 u_MVP;"
"void main () {"
"     gl_Position = u_MVP * vec4 (vp, 1.0);"
"}";

//vertex shader obdelnik
const char* vertex_shader_rectangle =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"out vec3 color;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"	  color = vc;"
"}";

//vertex shader bush
const char* vertex_shader_bush =
"#version 330\n"
"layout(location = 0) in vec3 aPos;"
"layout(location = 1) in vec3 aNormal;"
"uniform mat4 u_MVP;"
"uniform mat4 u_Model;"
"out vec3 Normal;"
"out vec3 FragPos;"
"void main() {"
"    FragPos = vec3(u_Model * vec4(aPos, 1.0));"
"    Normal = mat3(transpose(inverse(u_Model))) * aNormal;"
"    gl_Position = u_MVP * vec4(aPos, 1.0);"
"}";

//tocici ctverec
const char* vertex_shader_rectangle_rotate =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"out vec3 color;"
"uniform mat4 u_MVP;"
"void main () {"
"     gl_Position = u_MVP * vec4(vp, 1.0);"
"     color = vc;"
"}";

//kulicky
const char* vertex_shader_univerzal =
"#version 330\n"
"layout(location = 0) in vec3 aPos;"
"layout(location = 1) in vec3 aNormal;"
"uniform mat4 u_MVP;"
"uniform mat4 u_Model;"
"out vec3 color;"
"void main() {"
"    gl_Position = u_MVP * vec4(aPos, 1.0);"
"    color = normalize(aNormal)*0.5 + 0.5;"
"}";

//fragment shader trojuhelnik
const char* fragment_shader_triangle =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

//fragment shader ctverec
const char* fragment_shader_square =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (1.0, 1.0, 0.0, 1.0);"
"}";

//fragment shader kulicky
const char* fragment_shader_univerzal =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragColor;\n"
"void main() {\n"
"    fragColor = vec4(color, 1.0);\n"
"}";

//fragment shader obdelnik
const char* fragment_shader_rectangle =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragColor;\n"
"void main() {\n"
"    fragColor = vec4(color, 1.0);\n"
"}";

//fragment shader bush
const char* fragment_shader_bush =
"#version 330\n"
"in vec3 Normal;"
"in vec3 FragPos;"
"out vec4 FragColor;"
"const vec3 lightDir = vec3(-0.5, -1.0, -0.3);"
"void main() {"
"    float diff = max(dot(normalize(Normal), -lightDir), 0.0);"
"    vec3 color = vec3(0.2, 0.8, 0.2) * diff;"
"    FragColor = vec4(color, 1.0);"
"}";



int directory = 1;
float ratio;
int sceneNow = 1;

static ObjectGroup* makeGroupFrom(std::string name,ShaderProgram* shader,const float* data,int vertecies,int instances)
{
    ObjectGroup* object = new ObjectGroup{};
    object->name   = name;
    object->shader = shader;              
	object->model  = new Model(6,3,3);
    std::vector<float>modelsForScene4(data, data + vertecies);
    object->model->load_Data(modelsForScene4);

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

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
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

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);

	return true;
}

void Application::createShaders()
{
	//shadery pro fialovy trojuhelnik
	vertexShaderTrinagle = new Shader(vertex_shader,GL_VERTEX_SHADER);
	fragmentShaderTriangle = new Shader(fragment_shader_triangle,GL_FRAGMENT_SHADER);
	shaderTriangle = new ShaderProgram();
	shaderTriangle->link(*vertexShaderTrinagle,*fragmentShaderTriangle);

	//shadery pro barevny ctverec
	vertexShaderRectangle = new Shader(vertex_shader_rectangle_rotate,GL_VERTEX_SHADER);
	fragmentShaderRectangle = new Shader(fragment_shader_rectangle, GL_FRAGMENT_SHADER);
	shaderRectangle = new ShaderProgram();
	shaderRectangle->link(*vertexShaderRectangle, *fragmentShaderRectangle);

	//shadery pro kulicky
	vertexShaderSphere = new Shader(vertex_shader_univerzal,GL_VERTEX_SHADER);
	fragmentShaderSphere = new Shader(fragment_shader_univerzal,GL_FRAGMENT_SHADER);
	shaderSphere = new ShaderProgram();
	shaderSphere->link(*vertexShaderSphere,*fragmentShaderSphere);

	//univerzalni shader pro 20 objektu
	vertexShaderUniverzal = new Shader(vertex_shader_univerzal,GL_VERTEX_SHADER);
    fragmentShaderUniverzal = new Shader(fragment_shader_univerzal,GL_FRAGMENT_SHADER);
    shaderUniverzal = new ShaderProgram();
    shaderUniverzal->link(*vertexShaderUniverzal,*fragmentShaderUniverzal);

	
}
void Application::createBuffers()
{
	//fialovy trojuhelnik
	modelTriangle = new Model(3,3,0);
	std::vector<float>triangle(points_triangle,points_triangle + sizeof(points_triangle)/sizeof(float));
	modelTriangle->load_Data(triangle);
	objectTriangle= new DrawAbleObject(*modelTriangle, *shaderTriangle);


	//barevny tocici se ctverec
	modelRectangle = new Model(6, 3, 3);
	std::vector<float>rectangle(points_rectangle, points_rectangle + sizeof(points_rectangle) / sizeof(float));
	modelRectangle->load_Data(rectangle);
	objectRectangle = new DrawAbleObject(*modelRectangle, *shaderRectangle);
	
	//kulicky 
	modelSphere = new Model(6,3,3);
	std::vector<float>sphere1(sphere, sphere + sizeof(sphere) / sizeof(float));
	modelSphere->load_Data(sphere1);
	object1Sphere = new DrawAbleObject(*modelSphere,*shaderSphere);
	object2Sphere = new DrawAbleObject(*modelSphere,*shaderSphere);
	object3Sphere = new DrawAbleObject(*modelSphere,*shaderSphere);
	object4Sphere = new DrawAbleObject(*modelSphere,*shaderSphere);

	//Scena 4 
    groupForScene4.push_back(makeGroupFrom("Bush",shaderUniverzal,bushes,sizeof(bushes)/sizeof(float),3));
    groupForScene4.push_back(makeGroupFrom("Tree",shaderUniverzal,tree,sizeof(tree)/sizeof(float),3));
    groupForScene4.push_back(makeGroupFrom("SuziSmooth",shaderUniverzal,suziSmooth,sizeof(suziSmooth)/sizeof(float),3));
    groupForScene4.push_back(makeGroupFrom("SuziFlat",shaderUniverzal,suziFlat,sizeof(suziFlat)/sizeof(float),3));
    groupForScene4.push_back(makeGroupFrom("Plain",shaderUniverzal,plain,sizeof(plain)/sizeof(float),3));
    groupForScene4.push_back(makeGroupFrom("Gift",shaderUniverzal,gift,sizeof(gift)/sizeof(float),3));
	groupForScene4.push_back(makeGroupFrom("Sphere",shaderUniverzal,sphere,sizeof(sphere)/sizeof(float),2));
}

void Application::buildScene()
{
	glm::mat4 proj = glm::perspective(glm::radians(60.0f),ratio,0.1f,100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), {0,0,-2.5f});

	scene1 = new Scene(view,proj);
	scene2 = new Scene(view,proj);
	scene3 = new Scene(view,proj);
	scene4 = new Scene(view,proj);

	//barevny trojuhelnik
	TransformationGroup* groupTriangle = new TransformationGroup();
	groupTriangle->addTransformation(new TransformationRotate(glm::vec3(0,0,1),0.0f, 1.f));
	objectTriangle->addTransformation(groupTriangle);
	scene1->addObject(objectTriangle);

	//barevny ctverec
	TransformationGroup* groupRectagle = new TransformationGroup();
    //groupRectagle->addTransformation(new TransformationRotate(glm::vec3(0,0,1), 0.0f,1.f));
	groupRectagle->addTransformation(new TransformationScale(glm::vec3(1.f,1.f,0.6f),-0.5f));
	//groupRectagle->addTransformation(new TransformationTranslate(glm::vec3(0,0.00001,0),0.1f));
	objectRectangle->addTransformation(groupRectagle);
    scene2->addObject(objectRectangle);

	//kulicky
	object1Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.f, 0.75f, 0.0f), 0.0f));
	object1Sphere->addTransformation(new TransformationScale(glm::vec3(0.5f, 0.5f, 0.5f), 0.0f));

	object2Sphere->addTransformation(new TransformationTranslate(glm::vec3(-0.75f, 0.f, 0.0f), 0.0f));;
	object2Sphere->addTransformation(new TransformationScale(glm::vec3(0.5f, 0.5f, 0.5f), 0.0f));

	object3Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.75f, 0.f, 0.0f), 0.0f));;
	object3Sphere->addTransformation(new TransformationScale(glm::vec3(0.5f, 0.5f, 0.5f), 0.0f));

	object4Sphere->addTransformation(new TransformationTranslate(glm::vec3(0.f, -0.75f, 0.0f), 0.0f));;
	object4Sphere->addTransformation(new TransformationScale(glm::vec3(0.5f, 0.5f, 0.5f), 0.0f));

	scene3->addObject(object1Sphere);
	scene3->addObject(object2Sphere);
	scene3->addObject(object3Sphere);
	scene3->addObject(object4Sphere);

	//Scena4 mrizkove rozpolezeni sceny 
	const int rows = 4; 
	const int cols = 5;
	const float left = -1.0f; 
	const float right = 1.0f;
	const float bottom = -1.0f;
	const float top = 1.0f;
	const float placeWidth = (right - left) / cols;
	const float placeHeight = (top - bottom) / rows;
	
	int i = 0; 
	for (ObjectGroup* group : groupForScene4) 
	{
	 	for (DrawAbleObject* object : group->objects) 
		{
			if (i >= rows * cols) 
			{
				break;
			}      
			int row = i / cols;                 
			int col = i % cols;                 

			float x = left + (col+0.5f) * placeWidth;
			float y = top  - (row+ 0.5f) * placeHeight;
			float z = 1;

			float s = 0.2;
			if (group->name == "Tree") 
			{
            s *= 0.2f; 
        	}
			if(group->name == "Bush")
			{
				s *= 2;
			}
			if(group->name == "Gift")
			{
				s*= 2;
			}

			TransformationGroup* scene4TransGroup = new TransformationGroup();
			scene4TransGroup->addTransformation(new TransformationTranslate(glm::vec3(x, y, 0.0f), 0.0f));
			scene4TransGroup->addTransformation(new TransformationScale(glm::vec3(s), 0.0f));
			scene4TransGroup->addTransformation(new TransformationRotate(glm::vec3(x,y,z),0.f,1.f));
			object->addTransformation(scene4TransGroup);
			scene4->addObject(object);

			i++;
		}
	}

}

float angle= 0.0f;
float deltaTime = 0.0f;
float current_time = 0.0f;
float previous_time = 0.0f;
void Application::run()
{
	int lastScene = 0;
	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		previous_time = current_time;
		current_time = glfwGetTime();
		deltaTime = current_time - previous_time;
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
		sceneActual->updateScene(deltaTime);
		sceneActual->drawScene();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}



