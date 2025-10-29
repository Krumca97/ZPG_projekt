#version 330 core

const int maxLight = 8;
in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 lightPosition[maxLight];
uniform vec3 lightColor[maxLight];
uniform float lightIntensity[maxLight];
uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 ambient  = 0.1 * objectColor;
    vec3 result = vec3(0.0);
    result += ambient;
    
    for(int i = 0;i<1;i++)
    {
        vec3 lightDir = normalize(lightPosition[i] - fragPos);
        vec3 halfWayDir = normalize(lightDir + viewDir);

        float diff = max(dot(norm, lightDir), 0.0);
        float spec = pow(max(dot(norm, halfWayDir), 0.0), 64.0);

        vec3 diffuse  = diff * lightColor[i] * lightIntensity[i] * objectColor;
        vec3 specular = spec * lightColor[i] * lightIntensity[i] * objectColor;
        
        result += diffuse + specular;
    }
    fragColor = vec4(result, 1.0);
}
