#pragma once
#include <iostream>
#include "IObserverLight.h"
#include "TransformationComposite.h"
#include <glm/glm.hpp>
#include <vector>

class ShaderProgram;

class LightSubject
{
  public:
    LightSubject(glm::vec3 position,glm::vec3 color,float intensity);

    void attach(IObserverLight* observer);
    void notify();
    void addTransformation(TransformationComponent* transform);
    void clearTransformation();
    glm::vec3 getPosition();
    void setParentSpace(LightSubject* newParentSpace);
    
private:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
    std::vector<IObserverLight*> shaderProgramsObservers;
    TransformationComposite* transformations;
    glm::mat4 combiMatrix();
      LightSubject* parentSpace = nullptr;           
    std::vector<LightSubject*> childrenSpace;      

};