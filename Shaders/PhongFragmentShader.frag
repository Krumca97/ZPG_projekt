#version 330 core

in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 objectColor;
uniform mat4 viewMatrix;

void main()
{
    vec3 lightPosView = vec3(viewMatrix * vec4(lightPosition, 1.0));

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPosView - fragPos);

    vec3 ambient = 0.1 * lightColor * objectColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightIntensity * objectColor;

    vec3 viewDir = normalize(-fragPos); // v view prostoru kamera = (0,0,0)
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * lightColor * lightIntensity * objectColor;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}
