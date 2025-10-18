#pragma once
#include <GLFW/glfw3.h>
#include "CameraSubject.h"

class Controller {
public:
    Controller(CameraSubject* camera);

    void processKeyboard(GLFWwindow* window, float deltaTime);
    void processMouse(GLFWwindow* window, float x_pos, float y_pos);

    void setMouseEnabled(bool enabled);

     CameraSubject* getCamera();

private:
    CameraSubject* camera;
    float lastX;
    float lastY;
    bool firstMouse;
    bool mouseEnabled;
};
