#pragma once
#include <GL/glew.h>
#include <iostream>

class Shader
{
public:
    Shader(const char* source, GLenum type);
    ~Shader();
    bool compile_shader();
    void attachShader(GLuint shaderProgram);
private:
    GLuint shader_id;
    GLenum type;
    const char* source;
};   