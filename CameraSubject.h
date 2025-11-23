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
    CameraSubject(glm::vec3 position,float yawDeg, float pitchDeg,float field_of_view,float window_ratio,float near_plane, float far_plane,float move_speed,float mouse_sensitivity);

    glm::mat4 getViewMatrix();
    glm::mat4 projectionMatrix();

    void attach(ShaderProgram* shaderProgram);
    void notify();

    void moveForward(float dt);
    void moveBackward(float dt);
    void moveRight(float dt);
    void moveLeft(float dt);
    
    void mouseDeltaMovement(float directionY,float directionX);

    void setFieldOfView(float fieldOfView);
    void setWindowRatio(float windowRatio);

    glm::vec3 getPosition();
    glm::vec3 getForward();
    void setPosition(glm::vec3 position);

    float getCameraSpeed();
    glm::ivec2 getResolution() const;
    void setResolution(int w, int h);
private:

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;
    
    float yaw;
    float pitch;
    float moveSpeed;
    float mouseSensitivity;
    float fieldOfView;
    float windowRatio;
    float nearPlane;
    float farPlane;
    int windowWidth = 1280;
    int windowHeight = 720;

    void updateVectors();

    std::vector<IObserverCamera*> shaderProgramsObservers;
};