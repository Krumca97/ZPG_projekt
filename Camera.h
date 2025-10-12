#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

class ShaderProgram;

class Camera{
public:
    Camera(glm::vec3 position,glm::quat orientation,glm::vec3 world_up, float field_of_view,float window_ratio, float near_plane, float far_plane,float move_speed, float mouse_sensitivity);

    glm::mat4 getCamera();
    glm::mat4 projectionMatrix();

    void attach(ShaderProgram* shader_program);
    void notify();

    void move_forward(float forward);
    void move_backward(float backward);
    void move_right(float right);
    void move_left(float left);
    
    void mouse_delta_movement(float direction_y,float direction_x);

    void set_field_of_view(float field_of_view);
    void set_window_ratio(float window_ratio);

    glm::vec3 get_position();
    void set_position(glm::vec3 position);

    float get_camera_speed();
private:

    glm::vec3 position;
    glm::quat orientation;
    glm::vec3 world_up;

    float move_speed;
    float mouse_sensitivity;
    float field_of_view;
    float window_ratio;
    float near_plane;
    float far_plane;

    std::vector<ShaderProgram*> shaderProgramsObservers;
};