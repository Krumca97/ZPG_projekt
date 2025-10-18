#pragma once
#include <GL/glew.h>
#include <iostream>

class Shader
{
public:
    Shader(const char* source, GLenum type);
    ~Shader();
    bool compileShader();
    void attachShader(GLuint shaderProgram);
private:
    GLuint shaderId;
    GLenum type;
    const char* source;
};   