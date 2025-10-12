#include "Controller.h"
#include <iostream>

Controller::Controller(Camera* camera)
{
    this->camera = camera;
    this->lastX= 0.f;
    this->lastY = 0.f;
    this->first_mouse = true;
    this->mouse_enabled = true;
}

void Controller::process_keyboard(GLFWwindow* window, float deltaTime)
{
    float velocity = camera->get_camera_speed() * deltaTime*2;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->move_forward(velocity);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->move_backward(velocity);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {    
        camera->move_left(velocity);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {    
        camera->move_right(velocity);
    }
}

void Controller::process_mouse(GLFWwindow* window, float x_pos, float y_pos)
{

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (!mouse_enabled) 
        {
            mouse_enabled = true;
            first_mouse = true;  
        }
    } 
    else 
    {
        mouse_enabled = false;
        return;
    }

    if (first_mouse) 
    {
        lastX = x_pos;
        lastY = y_pos;
        first_mouse = false;
    }

    float xoffset = x_pos - lastX;
    float yoffset = lastY - y_pos; 

    lastX = x_pos;
    lastY = y_pos;

    camera->mouse_delta_movement(yoffset, -xoffset);
}

void Controller::set_mouse_enabled(bool enabled)
{
    mouse_enabled = enabled;
    first_mouse = true; 
}
