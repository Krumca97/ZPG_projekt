#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Shader_program.h"

class Skybox {
public:
    Skybox(ShaderProgram* shaderProgram, std::vector<std::string> faces);
    ~Skybox();

    void draw(glm::mat4 view, glm::mat4 proj);


private:
    GLuint VAO; 
    GLuint VBO;
    GLuint cubemapTexture;
    ShaderProgram* shaderProgram;
};
