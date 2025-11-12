#pragma once
#include <GL/glew.h>
#include <string>

class TextureLoader {
public:
    static GLuint LoadTexture(const std::string& path);
};
