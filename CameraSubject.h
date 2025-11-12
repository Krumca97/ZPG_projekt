#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include "IObserverCamera.h"

class ShaderProgram;

class CameraSubject
{
public:
    CameraSubject(glm::vec3 position,glm::quat orientation,glm::vec3 world_up, float field_of_view,float window_ratio, float near_plane, float far_plane,float move_speed, float mouse_sensitivity);

    glm::mat4 getCamera();
    glm::mat4 projectionMatrix();

    void attach(ShaderProgram* shaderProgram);
    void notify();

    void moveForward(float forward);
    void moveBackward(float backward);
    void moveRight(float right);
    void moveLeft(float left);
    
    void mouseDeltaMovement(float directionY,float directionX);

    void setFieldOfView(float fieldOfView);
    void setWindowRatio(float windowRatio);

    glm::vec3 getPosition();
    glm::vec3 getFront();
    void setPosition(glm::vec3 position);
    glm::mat4 getViewMatrix();
    glm::vec3 getForward();

    float getCameraSpeed();
private:

    glm::vec3 position;
    glm::quat orientation;
    glm::vec3 worldUp;

    float moveSpeed;
    float mouseSensitivity;
    float fieldOfView;
    float windowRatio;
    float nearPlane;
    float farPlane;

    std::vector<IObserverCamera*> shaderProgramsObservers;
};