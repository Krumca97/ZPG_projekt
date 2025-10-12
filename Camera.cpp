#include "Camera.h"
#include <glm/gtx/quaternion.hpp>
#include <algorithm>
#include "Shader_program.h"

Camera::Camera(glm::vec3 position,glm::quat orientation,glm::vec3 world_up, float field_of_view,float window_ratio, float near_plane, float far_plane,float move_speed, float mouse_sensitivity)
{
   this->position = {0.f,1.7f,3.f};
   this->orientation = glm::quat(1.f,0.f,0.f,0.f);
   this->world_up = {0.f,1.f,0.f};
   this->field_of_view = 60.f;
   this->window_ratio = 4.f/3.f;
   this->near_plane = 0.1f;
   this->far_plane = 100.f;
   this->move_speed = 2.5f;
   this->mouse_sensitivity = 0.1f;
}

glm::mat4 Camera:: getCamera()
{
    glm::mat4 rotation = glm::mat4_cast(orientation);   //z quartenionu na rotacni matici 
    glm::mat4 transaltion = glm::translate(glm::mat4(1.f), -position); 

    return glm::transpose(rotation) * transaltion;
}


glm::mat4 Camera::projectionMatrix()
{
    return glm::perspective(glm::radians(field_of_view),window_ratio,near_plane,far_plane);
}

void Camera::attach(ShaderProgram* shader_program)
{
    this->shaderProgramsObservers.push_back(shader_program);
}

void Camera::notify()
{
    glm::mat4 view = this->getCamera();
    glm::mat4 proj = this->projectionMatrix();

    for(ShaderProgram* shader : shaderProgramsObservers)
    {
        shader->update(view,proj);
    }
}

void Camera::move_forward(float forward)
{
    glm::vec3 forw = this->orientation * glm::vec3(0, 0, -1);
    position += forw * forward;
    notify();
}


void Camera::move_backward(float backward)
{
    glm::vec3 back = this->orientation * glm::vec3(0, 0, -1);
    position -= back * backward;
    notify();
}

void Camera::move_right(float right)
{
    glm::vec3 r = orientation * glm::vec3(1, 0, 0);
    position += r * right;
    notify();
}

void Camera::move_left(float left)
{
    glm::vec3 l = orientation * glm::vec3(1, 0, 0);
    position -= l * left;
    notify();
}

void Camera::mouse_delta_movement(float direction_y,float direction_x)
{
    float sensitivity = this->mouse_sensitivity;
    float dir_x   = glm::radians(direction_x * this->mouse_sensitivity);
    float dir_y = glm::radians(direction_y * this->mouse_sensitivity);

    glm::quat quat_dir_x = glm::angleAxis(dir_x, glm::vec3(this->world_up));

    glm::vec3 right = glm::normalize(this->orientation * glm::vec3(1.f, 0.f, 0.f));
    glm::quat quat_dir_y = glm::angleAxis(dir_y, right);

    glm::quat newOrientation = glm::normalize(quat_dir_x * quat_dir_y * this->orientation);

    glm::vec3 front = newOrientation * glm::vec3(0, 0, -1);
    float max_dir_y = std::cos(glm::radians(1.0f));
    float dot = glm::dot(glm::normalize(front), glm::normalize(this->world_up));

    if (std::abs(dot) < max_dir_y) 
    {
        orientation = newOrientation;
    }
    notify();
}

void Camera::set_field_of_view(float field_of_view)
{
    this->field_of_view = std::clamp(field_of_view,20.f,90.f);
}

void Camera::set_window_ratio(float window_ratio)
{
    this->window_ratio = window_ratio;
}

glm::vec3 Camera::get_position()
{
    return this->position;
}

void Camera::set_position(glm::vec3 position)
{
    this->position = position;
}

float Camera::get_camera_speed()
{
    return this->move_speed;
}