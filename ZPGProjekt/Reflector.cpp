#include "Reflector.h"

Reflector::Reflector(glm::vec3 lightPosition, glm::vec4 lightColor, float intensity, float specularStrength) : 
	Light(LightType::Spotlight, lightPosition, lightColor,  intensity, specularStrength) {}

void Reflector::updatePosition(glm::vec3 position)
{
	this->setLightPosition(position);
}
