#include "CameraSubject.h"
#include <algorithm>
#include "Shader_program.h"
#include "IObserverCamera.h"

CameraSubject::CameraSubject(glm::vec3 position,float yawDeg, float pitchDeg,float fieldOfView, float windowRatio,float nearPlane, float farPlane,float moveSpeed, float mouseSensitivity)
{
    this->position = position;
    this->yaw = glm::radians(yawDeg);
    this->pitch = glm::radians(pitchDeg);

    this->worldUp = glm::vec3(0.f, 1.f, 0.f);

    this->fieldOfView = fieldOfView;
    this->windowRatio = windowRatio;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;

    this->moveSpeed = moveSpeed;
    this->mouseSensitivity = mouseSensitivity;
    this->forward = glm::vec3(0.f, 0.f, -1.f);
    this->right = glm::vec3(1.f, 0.f, 0.f);
    this->up = glm::vec3(0.f, 1.f, 0.f);

    updateVectors();
}

glm::mat4 CameraSubject:: getViewMatrix()
{
    return glm::lookAt(position, position + forward, up);
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
    glm::mat4 view = this->getViewMatrix();
    glm::mat4 proj = this->projectionMatrix();

    for(IObserverCamera* shader : shaderProgramsObservers)
    {
        shader->onCameraChange(view,proj,this->position);
    }
}

void CameraSubject::moveForward(float dt)
{
    position += forward * dt * moveSpeed;
    notify();
}


void CameraSubject::moveBackward(float dt)
{
    position -= forward * dt * moveSpeed;
    notify();
}

void CameraSubject::moveRight(float dt)
{
    position += right * dt * moveSpeed;
    notify();
}

void CameraSubject::moveLeft(float dt)
{
    position -= right * dt * moveSpeed;
    notify();
}

void CameraSubject::mouseDeltaMovement(float directionY,float directionX)
{
    yaw   += directionX * mouseSensitivity;
    pitch += directionY * mouseSensitivity;

    pitch = glm::clamp(pitch, glm::radians(-89.0f), glm::radians(89.0f));

    if (yaw > glm::two_pi<float>()) yaw -= glm::two_pi<float>();
    if (yaw < 0) yaw += glm::two_pi<float>();

    updateVectors();
    notify();
}

void CameraSubject::updateVectors()
{
    forward.x = cos(pitch) * cos(yaw);
    forward.y = sin(pitch);
    forward.z = cos(pitch) * sin(yaw);
    forward = glm::normalize(forward);

    right = glm::normalize(glm::cross(forward, worldUp));
    up    = glm::normalize(glm::cross(right, forward));
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
    notify();
}

glm::vec3 CameraSubject::getForward()
{
    return forward;
}

float CameraSubject::getCameraSpeed()
{
    return this->moveSpeed;
}

glm::ivec2 CameraSubject::getResolution() const 
{
    return glm::ivec2(windowWidth, windowHeight);
}

void CameraSubject::setResolution(int w, int h) 
{
    windowWidth = w;
    windowHeight = h;
    windowRatio = w / (float)h;
}
