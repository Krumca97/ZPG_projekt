#include "Controller.h"
#include <iostream>

Controller::Controller(CameraSubject* camera)
{
    this->camera = camera;
    this->lastX= 0.f;
    this->lastY = 0.f;
    this->firstMouse = true;
    this->mouseEnabled = true;
}

void Controller::processKeyboard(GLFWwindow* window, float deltaTime)
{
    float velocity =camera->getCameraSpeed()  * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->moveForward(velocity);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->moveBackward(velocity);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {    
        camera->moveLeft(velocity);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {    
        camera->moveRight(velocity);
    }
}

void Controller::processMouse(GLFWwindow* window, float xPos, float yPos)
{

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (!mouseEnabled) 
        {
            mouseEnabled = true;
            firstMouse = true;  
        }
    } 
    else 
    {
        mouseEnabled = false;
        return;
    }

    if (firstMouse) 
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; 

    lastX = xPos;
    lastY = yPos;

    camera->mouseDeltaMovement(yOffset, xOffset);
}

void Controller::setMouseEnabled(bool enabled)
{
    mouseEnabled = enabled;
    firstMouse = true; 
}

CameraSubject* Controller:: getCamera()
{
    return this->camera;
}
