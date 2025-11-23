#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 normal;

void main() {
    vec4 worldPos = modelMatrix * vec4(aPos,1.0);
    fragPos= worldPos.xyz / worldPos.w;

    normal = normalize(mat3(transpose(inverse(modelMatrix))) * aNormal);

    gl_Position = projectionMatrix * viewMatrix * worldPos;
}
