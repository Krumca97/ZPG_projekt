#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPos;
out vec3 worldNorm;
out vec3 viewPos;

void main()
{
    vec4 worldPosition = modelMatrix* vec4(aPos, 1.0);
    worldPos = worldPosition.xyz;

    vec4 viewPosition = viewMatrix * worldPosition;
    viewPos = viewPosition.xyz;

    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    worldNorm = normalize(normalMatrix * aNormal);
    
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
