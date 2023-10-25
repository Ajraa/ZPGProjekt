#include "Light.h"
#include "Shader.h"

Light::Light(glm::vec3 lightPosition, glm::vec4 lightColor, float intensity, float specularStrength)
{
	this->lightPosition = lightPosition;
	this->lightColor = lightColor;
	this->intensity = intensity;
	this->specularStrength = specularStrength;
}

void Light::attach(LightObserver* observer)
{
	this->observers.push_back(observer);
	((Shader*)observer)->setLight(this);
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

void Light::useLightPosition(GLuint shaderProgram)
{
	int idMatrix = glGetUniformLocation(shaderProgram, "lightPosition");
	if (idMatrix == -1)
		std::cout << "Problém s Uniform Location lightPosition\n";
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, glm::value_ptr(this->lightPosition));
}

void Light::useLightColor(GLuint shaderProgram)
{
	int idMatrix = glGetUniformLocation(shaderProgram, "lightColor");
	if (idMatrix == -1)
		std::cout << "Problém s Uniform Location lightColor\n";
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, glm::value_ptr(this->lightColor));
}

void Light::update(GLuint shaderProgram)
{
	this->useLightPosition(shaderProgram);
	this->useLightPosition(shaderProgram);
}
