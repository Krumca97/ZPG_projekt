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
#include "Transformations/TransformationPath.h"
#include "Transformations/TransformationTranslate.h"
#include "ResourceOwner.h"

class Application : public ResourceOwner
{
	friend class Scene1;
	friend class Scene2;
	friend class Scene3;
	friend class Scene4;
	friend class Scene5;
	friend class Scene6;
	friend class Scene7;
public:
	void check();
	bool initialization();
	bool initGLFW();
	void initCallbacks();
	void onResize(int width, int height);
	void onMouseMove(double x, double y);
	void onMouseButton(int button, int action, int mods);
	void onKey(int key, int action, int mods);
	void moveObjectUnderCursor(double mx, double my);
	void handleLeftClick();
	void createShaders();
	void createBuffers();
	void buildScene();
	void run();

	int sceneNow = 1;
	bool isObjectMoving();
    DrawAbleObject* getMovingObject();
private:
	GLFWwindow* window = nullptr;

	//Shell game
	bool mixing = false;
	float mixTime = 0.0f;
	int ballSlot = 0; 
	int score = 0;
	bool gameOver = false;
	bool waitingForGuess = false;

	DrawAbleObject* cup1 = nullptr;
	DrawAbleObject* cup2 = nullptr;
	DrawAbleObject* cup3 = nullptr;
	TransformationPath* path1 = nullptr;
	TransformationPath* path2 = nullptr;
	TransformationPath* path3 = nullptr;
	TransformationComposite* transCup1 = nullptr;
	TransformationComposite* transCup2 = nullptr;
	TransformationComposite* transCup3 = nullptr;

	TransformationTranslate* liftCup1;
	TransformationTranslate* liftCup2;
	TransformationTranslate* liftCup3;
	TransformationTranslate* ballTranslate = nullptr;

	bool lifted1 = false;
	bool lifted2 = false;
	bool lifted3 = false;

	//Scene
	Scene* scene1 = nullptr;
	Scene* scene2 = nullptr;
	Scene* scene3 = nullptr;
	Scene* scene4 = nullptr;
	Scene* scene5 = nullptr;
	Scene* scene6 = nullptr;
	Scene* scene7 = nullptr;
	Scene* sceneActual = scene1;	

	bool isMovingObject = false;
	bool plantingMode = false;
	DrawAbleObject* movingObject = nullptr;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void switchScene(int scene);
	void toggleFullscreen(GLFWwindow* window);
	void toggleMoveMode();
	void togglePlantingMode();
	void restartShellGame();
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};
