#version 330 core

in vec2 uv;
out vec4 fragColor;

uniform sampler2D textureUnitID;
uniform bool useTexture;

uniform vec3 objectColor;

void main()
{
    if (useTexture)
    {
        fragColor = texture(textureUnitID, uv);
    }
    else
    {
        fragColor = vec4(objectColor, 1.0);
    }
}
