#version 450

layout(location = 0) in vec3 vp;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentLocalPosition;

void main () {
    mat4 viewNoTrans = mat4(mat3(viewMatrix));

    gl_Position = projectionMatrix * viewNoTrans* vec4(vp, 1.0);
    gl_Position = gl_Position.xyww;
    fragmentLocalPosition = vp;
}