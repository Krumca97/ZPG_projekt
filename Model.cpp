#define TINYOBJLOADER_IMPLEMENTATION
#include "Libraries/tiny_obj_loader.h"
#include "Model.h"
#include <iostream>

Model::Model(int jump, int positionSize, int normal)
{
    this->jump = jump;
    this->positionSize = positionSize;
    this->normal = normal;
    this->VAO = 0;
    this->VBO = 0;
}
Model::Model(const char *name)
{
    std::string inputfile = std::string("../../Assets/") + name;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), "../../Assets/");

    // if (!warn.empty()) std::cout << "Warn: " << warn << std::endl;
    // if (!err.empty()) std::cerr << "Err: " << err << std::endl;
    if (!ret)
        throw std::runtime_error("Failed to load OBJ file!");

    std::vector<float> vertices;
    jump = 8;
    positionSize = 3;
    normal = 3;

    for (const auto &shape : shapes)
    {
        for (const auto &index : shape.mesh.indices)
        {
            // Position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)
            if (index.normal_index >= 0)
            {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else
            {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            //  UV coordinates (if exist)
            if (index.texcoord_index >= 0)
            {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else
            {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }
    }

    loadData(vertices);
}

void Model::loadData(const std::vector<float> &points)
{
    this->points = points;
    setupModel();
}

void Model::setupModel()
{
    glGenVertexArrays(1, &VAO); // generate the VAO
    glBindVertexArray(VAO);     // bind the VAO

    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    // pozice
    // index, pocet, typ, normalized, velikost jednoho vrcholu, pocatek
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, positionSize, GL_FLOAT, GL_FALSE, jump * sizeof(float), NULL);

    // normala
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, normal, GL_FLOAT, GL_FALSE, jump * sizeof(float), (void *)(positionSize * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

    glBindVertexArray(0);
}

void Model::drawModel()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, points.size() / jump);
    glBindVertexArray(0);
}
