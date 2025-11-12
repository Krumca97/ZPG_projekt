#version 330 core

const int maxLight = 16;

in vec3 fragPosWorld;
in vec3 normalWorld;
in vec2 uv;
out vec4 fragColor;

struct Material {
    vec3 ra;
    vec3 rd;
    vec3 rs;
    float h;
};

uniform Material material;
uniform vec3 lightPosition[maxLight];
uniform vec3 lightColor[maxLight];
uniform float lightIntensity[maxLight];
uniform int lightType[maxLight];
uniform int lightCount;
uniform vec3 objectColor;
uniform mat4 viewMatrix;

uniform vec3 viewPos;

uniform sampler2D textureUnitID;
uniform bool useTexture;
uniform float uvScale;
uniform vec3 spotLightPosition;
uniform vec3 spotLightDirection;
uniform vec3 spotLightColor;
uniform float spotLightIntensity;

float attenuation(float distance, float constant, float linear, float quadratic)
{
    float att = 1.0 / (constant + linear * distance + quadratic * distance * distance);
    return clamp(att,0.0,1.0);
}

void main()
{
    vec3 norm = normalize(normalWorld);
    vec3 viewDir = normalize(viewPos - fragPosWorld);
    vec3 result = vec3(0.0); 
    vec3 baseColor = objectColor;
    
    if(useTexture)
    {
        baseColor = texture(textureUnitID, uv * uvScale).rgb;
    }

    vec3 ambient = material.ra * baseColor *0.2;
    result += ambient;

    for (int i = 0; i < lightCount; i++)
    {
        vec3 lightDir;
        float att = 1;
        vec3 diffuse = vec3(0.0); 
        vec3 specular = vec3(0.0); 

        if(lightType[i] == 1)
        {
            lightDir = normalize(lightPosition[i] - fragPosWorld);
            float distance = length(lightPosition[i] - fragPosWorld);
            att = attenuation(distance, 1.0, 0.22, 0.20);

            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.h);
            if (dot(norm, lightDir) < 0.0) spec = 0.0;

            diffuse = material.rd * diff * lightColor[i] * baseColor;
            specular = material.rs * spec * lightColor[i];
        }
        else if(lightType[i] == 0)
        {
            lightDir = normalize(-lightPosition[i]);

            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.h);
            if (dot(norm, lightDir) < 0.0) spec = 0.0;

            diffuse = material.rd * diff * lightColor[i] * baseColor;
            specular = material.rs *0.03* spec * lightColor[i];
        }
        else if(lightType[i] == 2)
        {
            result += material.ra * baseColor * lightColor[i] * lightIntensity[i];
            continue;
        }

        result += (diffuse + specular) * lightIntensity[i] * att;
    }

    if (spotLightIntensity > 0.001)
    {
        vec3 lightToFrag = normalize(fragPosWorld - spotLightPosition);
        float LF = dot(lightToFrag, spotLightDirection);

        float cutOff = cos(radians(40.0));
        float intens = (LF - cutOff) / (1.0 - cutOff);
        intens = clamp(intens, 0.0, 1.0);

        if (intens > 0.0)
        {
            float distance = length(spotLightPosition - fragPosWorld);
            float att = attenuation(distance, 1.0, 0.14, 0.07);

            vec3 lightDir = normalize(spotLightPosition - fragPosWorld);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.h);

            vec3 diffuse = material.rd * diff * spotLightColor * baseColor;
            vec3 specular = material.rs * spec * spotLightColor * baseColor;

            result += (diffuse + specular) * att * intens * spotLightIntensity;
        }
    }
    result = clamp(result, 0.0, 1.0);
    fragColor = vec4(result, 1.0);
}
