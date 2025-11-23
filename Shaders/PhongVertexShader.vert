#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPosWorld;
out vec3 normalWorld;
out vec2 uv;

void main()
{
    vec4 worldPos = modelMatrix * vec4(aPos* 500, 500.0f);
    fragPosWorld = worldPos.xyz / worldPos.w;

    normalWorld = normalize(mat3(transpose(inverse(modelMatrix))) * aNormal);
    uv = aTexCoord;

    gl_Position = projectionMatrix * viewMatrix* worldPos;
}
