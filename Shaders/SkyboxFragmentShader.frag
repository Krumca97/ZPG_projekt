#version 450

out vec4 fragColor;

in vec3 fragmentLocalPosition;
uniform samplerCube UISky;
void main () {
     fragColor = texture(UISky, fragmentLocalPosition);
}