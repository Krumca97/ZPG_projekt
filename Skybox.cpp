//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h> 

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Libraries/stb_image.h"

#include <iostream>
#include <fstream>
#include <iomanip>   // std::setprecision, std::setw
#include <vector>
#include "Skybox.h"
#include "Models/skycube.h"

using namespace std;

Skybox::Skybox(ShaderProgram* shaderProgram,vector<string> faces)
{
    this->shaderProgram = shaderProgram;
    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO); //generate the VAO
    glGenBuffers(1, &VBO); // generate the VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), &skycube[0], GL_STATIC_DRAW);

    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

    glBindVertexArray(0);

    glGenTextures(1,&cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);

    int text_width, text_height, channels;
    stbi_set_flip_vertically_on_load(false);
    
    for (GLuint i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &text_width, &text_height, &channels, 4);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    shaderProgram->useShaderProgram();
    shaderProgram->setUniform("UISky", 0);
}

Skybox::~Skybox()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Skybox::draw(glm::mat4 view, glm::mat4 proj)
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    shaderProgram->useShaderProgram();

    glm::mat4 viewNoTrans = glm::mat4(glm::mat3(view));
    shaderProgram->setUniform("viewMatrix", viewNoTrans);
    shaderProgram->setUniform("projectionMatrix", proj);

    glm::mat4 model = glm::mat4(1.0f);
    shaderProgram->setUniform("modelMatrix", model);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}
