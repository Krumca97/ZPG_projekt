#include "TransformationComponent.h"
#include <glm/glm.hpp>

class TransformationCustom : public TransformationComponent
{
private:
    glm::mat4 matrix;

public:
    TransformationCustom();
    TransformationCustom(const glm::mat4& m);
    virtual glm::mat4 getMatrix() const override;
};