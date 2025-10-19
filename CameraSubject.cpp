#include "CameraSubject.h"
#include <glm/gtx/quaternion.hpp>
#include <algorithm>
#include "Shader_program.h"
#include "IObserverCamera.h"

CameraSubject::CameraSubject(glm::vec3 position,glm::quat orientation,glm::vec3 worldUp, float fieldOfView,float windowRatio, float nearPlane, float farPlane,float moveSpeed, float mouseSensitivity)
{
   this->position = {0.f,1.7f,3.f};
   this->orientation = glm::quat(1.f,0.f,0.f,0.f);
   this->worldUp = {0.f,1.f,0.f};
   this->fieldOfView = 60.f;
   this->windowRatio = 4.f/3.f;
   this->nearPlane = 0.1f;
   this->farPlane = 100.f;
   this->moveSpeed = 2.5f;
   this->mouseSensitivity = 0.1f;
}

glm::mat4 CameraSubject:: getCamera()
{
    glm::mat4 rotation = glm::mat4_cast(orientation);   //z quartenionu na rotacni matici 
    glm::mat4 transaltion = glm::translate(glm::mat4(1.f), -position); 

    return glm::transpose(rotation) * transaltion;
}


glm::mat4 CameraSubject::projectionMatrix()
{
    return glm::perspective(glm::radians(fieldOfView),windowRatio,nearPlane,farPlane);
}

void CameraSubject::attach(ShaderProgram* shaderProgram)
{
    this->shaderProgramsObservers.push_back(shaderProgram);
}

void CameraSubject::notify()
{
    glm::mat4 view = this->getCamera();
    glm::mat4 proj = this->projectionMatrix();

    for(IObserverCamera* shader : shaderProgramsObservers)
    {
        shader->onCameraChange(view,proj,this->position);
    }
}

void CameraSubject::moveForward(float forward)
{
    glm::vec3 forw = this->orientation * glm::vec3(0, 0, -1);
    position += forw * forward;
    notify();
}


void CameraSubject::moveBackward(float backward)
{
    glm::vec3 back = this->orientation * glm::vec3(0, 0, -1);
    position -= back * backward;
    notify();
}

void CameraSubject::moveRight(float right)
{
    glm::vec3 r = orientation * glm::vec3(1, 0, 0);
    position += r * right;
    notify();
}

void CameraSubject::moveLeft(float left)
{
    glm::vec3 l = orientation * glm::vec3(1, 0, 0);
    position -= l * left;
    notify();
}

void CameraSubject::mouseDeltaMovement(float directionY,float directionX)
{
    float sensitivity = this->mouseSensitivity;
    float dirX   = glm::radians(directionX * this->mouseSensitivity);
    float dirY = glm::radians(directionY * this->mouseSensitivity);

    glm::quat quatDirX = glm::angleAxis(dirX, glm::vec3(this->worldUp));

    glm::vec3 right = glm::normalize(this->orientation * glm::vec3(1.f, 0.f, 0.f));
    glm::quat quatDirY = glm::angleAxis(dirY, right);

    glm::quat newOrientation = glm::normalize(quatDirX * quatDirY * this->orientation);

    glm::vec3 front = newOrientation * glm::vec3(0, 0, -1);
    float maxDirY = std::cos(glm::radians(1.0f));
    float dot = glm::dot(glm::normalize(front), glm::normalize(this->worldUp));

    if (std::abs(dot) < maxDirY) 
    {
        orientation = newOrientation;
    }
    notify();
}

void CameraSubject::setFieldOfView(float fieldOfView)
{
    this->fieldOfView = std::clamp(fieldOfView,20.f,90.f);
}

void CameraSubject::setWindowRatio(float windowRatio)
{
    this->windowRatio = windowRatio;
}

glm::vec3 CameraSubject::getPosition()
{
    return this->position;
}

void CameraSubject::setPosition(glm::vec3 position)
{
    this->position = position;
}

glm::vec3 CameraSubject::getForward(){
    return this->orientation * glm::vec3(0, 0, -1);
}

glm::mat4 CameraSubject::getViewMatrix(){
    return glm::lookAt(this->position,this->position + this->getForward(),this->worldUp);
}

float CameraSubject::getCameraSpeed()
{
    return this->moveSpeed;
}