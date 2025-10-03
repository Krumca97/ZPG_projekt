#pragma once
#include <GL/glew.h>
#include <iostream>

// //Odpovídá za:

// vytvoření shaderu (glCreateShader),

// nahrání zdrojového kódu (glShaderSource),

// kompilaci (glCompileShader),

// kontrolu chyb kompilace,

// uvolnění při zániku objektu (glDeleteShader).
class Shader
{
public:
    Shader(const char* vertex_shader, const char* fragment_shader);
    void compile_shader();
    void use_shader();


private:
    GLuint shader_id;
    const char* vertex_shader;
    const char* fragment_shader;
};   