#include "Light.h"
#include "Shader.h"




Light::Light(LightType type, glm::vec3 lightPosition, glm::vec4 lightColor, float intensity, float specularStrength)
{
	this->type = type;
	this->lightPosition = lightPosition;
	this->lightColor = lightColor;
	this->intensity = intensity;
	this->specularStrength = specularStrength;
}

void Light::attach(LightObserver* observer)
{
	this->observers.push_back(observer);
	((Shader*)observer)->addLight(this);
}

void Light::detach(LightObserver* observer)
{
	int i = 0;
	for (LightObserver* obs : this->observers)
	{
		if (observer == obs)
			break;
		i++;
	}
	if (i < this->observers.size())
		this->observers.erase(this->observers.begin() + i);
}

glm::vec3 Light::getLightPosition()
{
	return this->lightPosition;
}

glm::uvec4 Light::getLightColor()
{
	return this->lightColor;
}

void Light::useLightPosition(GLuint shaderProgram)
{
	std::cout << "Yup1" << std::endl;
	int idMatrix = glGetUniformLocation(shaderProgram, "lightPosition");
	if (idMatrix == -1)
		std::cout << "Problém s Uniform Location lightPosition\n";
	glUniform3fv(idMatrix, 1, glm::value_ptr(this->lightPosition));
}

void Light::useLightColor(GLuint shaderProgram)
{
	std::cout << "Yup2" << std::endl;
	int idMatrix = glGetUniformLocation(shaderProgram, "lightColor");
	if (idMatrix == -1)
		std::cout << "Problém s Uniform Location lightColor\n";
	glUniform4fv(idMatrix, 1, glm::value_ptr(this->lightColor));
}

void Light::update(LightObserver* obs, int index)
{
	if (Shader* s = dynamic_cast<Shader*>(obs)) {
		s->useLightPosition(this->lightPosition, index);
		s->useLightColor(this->lightColor, index);
		s->useLightType(this->type, index);
		
	}
}

void Light::setLightPosition(glm::vec3 position)
{
	this->lightPosition = position;
}
