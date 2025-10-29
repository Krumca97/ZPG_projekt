#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 normal;

void main()
{
    vec4 viewPos = viewMatrix * modelMatrix * vec4(aPos, 1.0);
    fragPos = viewPos.xyz;

    mat3 normalMatrix = mat3(transpose(inverse(viewMatrix * modelMatrix)));
    normal = normalize(normalMatrix * aNormal);

    gl_Position = projectionMatrix * viewPos;
}
