#version 330 core

const int maxLight = 16;

in vec3 fragPos;
in vec3 normal;
out vec4 fragColor;

uniform vec3 lightPosition[maxLight];
uniform vec3 lightColor[maxLight];
uniform float lightIntensity[maxLight];
uniform int lightCount;         
uniform vec3 objectColor;
uniform mat4 viewMatrix;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(-fragPos); 

    vec3 ambient = 0.08 * objectColor;
    vec3 result = ambient;

    for (int i = 0; i < 1; i++)
    {
        vec3 lightPosView = vec3(viewMatrix * vec4(lightPosition[i], 1.0));
        vec3 lightDir = normalize(lightPosView - fragPos);
        float distance = length(lightPosView - fragPos);

        float attenuation = 1.0 / (1.0 + 0.15 * distance + 0.24 * distance * distance);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor[i] * lightIntensity[i] * objectColor;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 5.0);
        vec3 specular = spec * lightColor[i] * lightIntensity[i];

        result += attenuation * (diffuse + specular);
    }

    fragColor = vec4(result, 1.0);
}
