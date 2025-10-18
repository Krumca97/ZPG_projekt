#version 330 core

in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 lightPosition;   // <- světlo v WORLD space (tak jak to máš v C++)
uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 objectColor;

uniform mat4 viewMatrix;      // <- přidáme view matici, kterou už stejně posíláš

void main() {
    // přepočítáme světlo z WORLD do VIEW space
    vec3 lightPosView = vec3(viewMatrix * vec4(lightPosition, 1.0));

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPosView - fragPos);

    // ambient
    vec3 ambient = 0.1 * lightColor * objectColor;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightIntensity * objectColor;

    vec3 result = ambient + diffuse;
    fragColor = vec4(result, 1.0);
}
