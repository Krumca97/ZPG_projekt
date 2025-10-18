#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;   // pozice ve view space
out vec3 normal;    // normála ve view space

void main()
{
    // přepočet vrcholu do view space
    vec4 viewPos = viewMatrix * modelMatrix * vec4(aPos, 1.0);
    fragPos = viewPos.xyz;

    // správná transformace normály do view space
    mat3 normalMatrix = mat3(transpose(inverse(viewMatrix * modelMatrix)));
    normal = aNormal;

    gl_Position = projectionMatrix * viewPos;
}
