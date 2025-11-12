#include "Material.h"

Material::Material()
{
    ra = glm::vec3(0.1f);   
    rd = glm::vec3(0.8f);
    rs = glm::vec3(1.0f);
    h = 32.0f;
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
    this->ra = ambient;
    this->rd = diffuse;
    this->rs = specular;
    this->h = shininess;
}
