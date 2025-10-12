#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

class Controller {
public:
    Controller(Camera* camera);

    void process_keyboard(GLFWwindow* window, float deltaTime);
    void process_mouse(GLFWwindow* window, float x_pos, float y_pos);

    void set_mouse_enabled(bool enabled);

private:
    Camera* camera;
    float lastX;
    float lastY;
    bool first_mouse;
    bool mouse_enabled;
};
