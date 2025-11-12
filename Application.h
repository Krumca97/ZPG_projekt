#pragma once
//Include GLM  
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "Model.h"
#include "DrawAbleObject.h"
#include "Shader_program.h"
#include "Scene.h"
#include "CameraSubject.h"
#include "Controller.h"
#include "LightSubject.h"

//structure for 20 objects
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

	//purple triangle
	Shader* vertexShaderTrinagle = nullptr;
	Shader* fragmentShaderTriangle = nullptr;
	ShaderProgram* shaderTriangle = nullptr;
	Model* modelTriangle = nullptr;
	DrawAbleObject* objectTriangle = nullptr;

	//rectangle
	Shader* vertexShaderRectangle = nullptr;
	Shader* fragmentShaderRectangle = nullptr;
	ShaderProgram* shaderRectangle = nullptr;
	Model* modelRectangle = nullptr;
	DrawAbleObject* objectRectangle = nullptr;

	//Spheres
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

	//Scene univerzal
	std::vector<ObjectGroup*> groupForScene4;
	Shader* vertexShaderUniverzal = nullptr;
	Shader* fragmentShaderUniverzal = nullptr;
	ShaderProgram* shaderUniverzal = nullptr;
	Model* modelUniverzal = nullptr;

	//scene3
	std::vector<ObjectGroup*> groupForScene3;
	Shader* vertexShaderSphereForest = nullptr;
	Shader* fragmentShaderSphereForest = nullptr;
	ShaderProgram* shaderSphereForest = nullptr;
	Shader* vertexShaderPlaineForest = nullptr;
	Shader* fragmentShaderPlainForest = nullptr;
	ShaderProgram* shaderPlainForest = nullptr;
	DrawAbleObject* objectForestSphere = nullptr;

	//Solar system
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

	//models from assests
	//formula
	Shader* vertexShaderFormula1Texture = nullptr;
	Shader* fragmentShaderFormula1Texture = nullptr;
	ShaderProgram* shaderFormula1Texture = nullptr;
	Model* modelFormula1 = nullptr;
	DrawAbleObject* formula1 = nullptr;
	
	//house
	Shader* vertexShaderHouseTexture = nullptr;
	Shader* fragmentShaderHouseTexture = nullptr;
	ShaderProgram* shaderHouseTexture = nullptr;
	Model* modelHouse = nullptr;
	DrawAbleObject* house = nullptr;
	
	//shrek,fiona and toilet
	Shader* vertexShaderShrekTexture = nullptr;
	Shader* fragmentShaderShrekTexture = nullptr;
	ShaderProgram* shaderShrekTexture = nullptr;
	Model* modelShrek = nullptr;
	DrawAbleObject* shrek = nullptr;

	Shader* vertexShaderFionaTexture = nullptr;
	Shader* fragmentShaderFionaTexture = nullptr;
	ShaderProgram* shaderFionaTexture = nullptr;
	Model* modelFiona = nullptr;
	DrawAbleObject* fiona = nullptr;

	Shader* vertexShaderToiletTexture = nullptr;
	Shader* fragmentShaderToiletTexture = nullptr;
	ShaderProgram* shaderToiletTexture = nullptr;
	Model* modelToilet = nullptr;
	DrawAbleObject* toilet = nullptr;

	//Scene
	Scene* scene1 = nullptr;
	Scene* scene2 = nullptr;
	Scene* scene3 = nullptr;
	Scene* scene4 = nullptr;
	Scene* scene5 = nullptr;
	Scene* scene6 = nullptr;
	Scene* scene7 = nullptr;
	Scene* sceneActual = scene1;	

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};
