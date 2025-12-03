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

struct Light {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float angle;
};

uniform Material material;
uniform Light lights[maxLight];
uniform int lightCount;
uniform vec3 objectColor;
uniform mat4 viewMatrix;

uniform vec3 viewPos;

uniform sampler2D textureUnitID;
uniform bool useTexture;
uniform float uvScale;

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
        if(lights[i].type == 2)
        {
            result += material.ra * baseColor * lights[i].color * lights[i].intensity;
            continue;
        }

        vec3 lightDir;
        float att = 1;
        vec3 diffuse = vec3(0.0); 
        vec3 specular = vec3(0.0); 

        if(lights[i].type == 1)
        {
            lightDir = normalize(lights[i].position - fragPosWorld);
            float distance = length(lights[i].position - fragPosWorld);
            att = attenuation(distance, 1.0, 0.22, 0.20);

            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.h);
            if (dot(norm, lightDir) < 0.0) spec = 0.0;

            diffuse = material.rd * diff * lights[i].color * baseColor;
            specular = material.rs * spec * lights[i].color;

            result += (diffuse + specular) * lights[i].intensity * att;
        }
        else if(lights[i].type == 0)
        {
            lightDir = normalize(-lights[i].direction);

            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.h);
            if (dot(norm, lightDir) < 0.0) spec = 0.0;

            diffuse = material.rd * diff * lights[i].color * baseColor;
            specular = material.rs *0.03* spec * lights[i].color;

            result += (diffuse + specular) * lights[i].intensity * att;
        }
        
        if (lights[i].type == 3)   // SPOT LIGHT
        {
            if (lights[i].intensity <= 0.001)
            {    
                continue;
            }
            vec3 lightToFrag = normalize(fragPosWorld - lights[i].position);
            float LF = dot(lightToFrag, lights[i].direction);

            float cutOff = cos(radians(40.0));
            float intens = (LF - cutOff) / (1.0 - cutOff);
            intens = clamp(intens, 0.0, 1.0);

            if (intens > 0.0)
            {
                float distance = length(lights[i].position - fragPosWorld);
                float att = attenuation(distance, 1.0, 0.14, 0.07);

                vec3 lightDir = normalize(lights[i].position - fragPosWorld);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 reflectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.h);

                vec3 diffuse = material.rd * diff * lights[i].color * baseColor;
                vec3 specular = material.rs * spec * lights[i].color * baseColor;

                result += (diffuse + specular) * att * intens * lights[i].intensity;
            }
        }
    }
    result = clamp(result, 0.0, 1.0);
    fragColor = vec4(result, 1.0);
}
