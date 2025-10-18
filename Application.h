#pragma once
//Include GLEW
// #include <GL/glew.h>
// #include <GLFW/glfw3.h> 

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>

#include "Model.h"
#include "DrawAbleObject.h"
#include "Shader_program.h"
#include "Scene.h"
#include "CameraSubject.h"
#include "Controller.h"
#include "LightSubject.h"

//structura pro vytvoreni 20 objektu
struct ObjectGroup 
{
    Shader* vertexShader;
	Shader* fragmentShader;
    ShaderProgram* shader;
    Model* model;
    std::vector<DrawAbleObject*> objects;
    std::string name;
};

class Application 
{
public:
	void check();
	bool initialization();
	void createShaders();
	void createBuffers();
	void buildScene();
	void run();

private:

	GLFWwindow* window = nullptr;

	//Kamera
	CameraSubject* camera = nullptr;
	Controller* controller = nullptr;

	//Svetlo
	LightSubject* light = nullptr;

	//fialovy trojuhelnik
	Shader* vertexShaderTrinagle = nullptr;
	Shader* fragmentShaderTriangle = nullptr;
	ShaderProgram* shaderTriangle = nullptr;
	Model* modelTriangle = nullptr;
	DrawAbleObject* objectTriangle = nullptr;

	//Vytvoreni ctverece
	Shader* vertexShaderRectangle = nullptr;
	Shader* fragmentShaderRectangle = nullptr;
	ShaderProgram* shaderRectangle = nullptr;
	Model* modelRectangle = nullptr;
	DrawAbleObject* objectRectangle = nullptr;

	//Kulicky
	Shader* vertexShaderSphere1 = nullptr;
	Shader* fragmentShaderSphere1 = nullptr;
	ShaderProgram* shaderSphere1 = nullptr;
	Shader* vertexShaderSphere2 = nullptr;
	Shader* fragmentShaderSphere2 = nullptr;
	ShaderProgram* shaderSphere2 = nullptr;
	Shader* vertexShaderSphere3 = nullptr;
	Shader* fragmentShaderSphere3 = nullptr;
	ShaderProgram* shaderSphere3 = nullptr;
	Shader* vertexShaderSphere4 = nullptr;
	Shader* fragmentShaderSphere4 = nullptr;
	ShaderProgram* shaderSphere4 = nullptr;
	Model* modelSphere = nullptr;
	DrawAbleObject* object1Sphere = nullptr;
	DrawAbleObject* object2Sphere = nullptr;
	DrawAbleObject* object3Sphere = nullptr;
	DrawAbleObject* object4Sphere = nullptr;

	//Scena univerzal
	std::vector<ObjectGroup*> groupForScene4;
	Shader* vertexShaderUniverzal = nullptr;
	Shader* fragmentShaderUniverzal = nullptr;
	ShaderProgram* shaderUniverzal = nullptr;
	Model* modelUniverzal = nullptr;

	//scena3
	std::vector<ObjectGroup*> groupForScene3;

	//Slunecni soustava
	Shader* vertexShaderSun = nullptr;
	Shader* fragmentShaderSun = nullptr;
	ShaderProgram* shaderSun = nullptr;
	Shader* vertexShaderEarth = nullptr;
	Shader* fragmentShaderEarth = nullptr;
	ShaderProgram* shaderEarth = nullptr;  
	Shader* vertexShaderMoon = nullptr;
	Shader* fragmentShaderMoon = nullptr;
	ShaderProgram* shaderMoon = nullptr;
	Model* modelSolarSystem = nullptr;
	DrawAbleObject* objectSun = nullptr;
	DrawAbleObject* objectEarth = nullptr;
	DrawAbleObject* objectMoon = nullptr; 

	//Scena
	Scene* scene1 = nullptr;
	Scene* scene2 = nullptr;
	Scene* scene3 = nullptr;
	Scene* scene4 = nullptr;
	Scene* scene5 = nullptr;
	Scene* sceneActual = scene1;	

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};
