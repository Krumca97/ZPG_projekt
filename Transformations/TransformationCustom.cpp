#include "TransformationCustom.h"
#include <glm/gtc/matrix_transform.hpp>

TransformationCustom::TransformationCustom()
{
    matrix = glm::mat4(1.0f);
    matrix[3][3] = 20.0f;
}

TransformationCustom::TransformationCustom(const glm::mat4& m): matrix(m){}

glm::mat4 TransformationCustom::getMatrix() const
{
    return matrix;
}