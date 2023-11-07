#pragma once
#include "Light.h"
class Reflector : public Light
{
	public:
		Reflector(glm::vec3 lightPosition, glm::vec4 lightColor, float intensity, float specularStrength);
		void updatePosition(glm::vec3 position);
};

