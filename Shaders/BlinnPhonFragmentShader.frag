#version 330 core

in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 objectColor;
uniform vec3 viewPos;  // world-space camera position

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPosition - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // světlo
    float diff = max(dot(norm, lightDir), 0.0);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 64.0);

    // složky osvětlení
    vec3 ambient  = 0.1 * lightColor * objectColor;
    vec3 diffuse  = diff * lightColor * lightIntensity * objectColor;
    vec3 specular = spec * lightColor * lightIntensity * objectColor;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}
