#version 330 core

const int maxLight = 8;
in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 lightPosition[maxLight];
uniform vec3 lightColor[maxLight];
uniform float lightIntensity[maxLight];
uniform vec3 objectColor;
uniform mat4 viewMatrix;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(-fragPos); // v view prostoru kamera = (0,0,0)
    vec3 ambient = 0.1 * objectColor;

    vec3 result = vec3(0.0);

    for(int i =0;i<maxLight;i++)
    {
        vec3 lightPosView = vec3(viewMatrix * vec4(lightPosition[i], 1.0));
        vec3 lightDir = normalize(lightPosView - fragPos);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor[i] * lightIntensity[i] * objectColor;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = spec * lightColor[i] * lightIntensity[i] * objectColor;

        result += diffuse + specular;
    }

    result += ambient;
    fragColor = vec4(result, 1.0);
}
