#include "LightSubject.h"

LightSubject::LightSubject(glm::vec3 position,glm::vec3 color,float intensity)
{
    this->position = position;
    this->color = color;
    this->intensity = intensity;
};

void LightSubject::attach(IObserverLight* observer)
{
    this->shaderProgramsObservers.push_back(observer);
};

void LightSubject::notify()
{
    glm::vec3 color = this->color;
    glm::vec3 position = this->position;
    float intensity = this->intensity;
    
    for(IObserverLight* observer: shaderProgramsObservers)
    {
        observer->onLightChange(position,color,intensity);
    }
    
};