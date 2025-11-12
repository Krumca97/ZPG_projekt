#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 color;

void main() 
{
    mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;

    gl_Position = PVM * vec4(aPos, 1.0);

    color = normalize(aNormal) * 0.5 + 0.5;
}