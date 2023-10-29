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
	std::cout << "Yup1" << std::endl;
	int idMatrix = glGetUniformLocation(shaderProgram, "lightPosition");
	if (idMatrix == -1)
		std::cout << "Probl�m s Uniform Location lightPosition\n";
	glUniform3fv(idMatrix, 1, glm::value_ptr(this->lightPosition));
}

void Light::useLightColor(GLuint shaderProgram)
{
	std::cout << "Yup2" << std::endl;
	int idMatrix = glGetUniformLocation(shaderProgram, "lightColor");
	if (idMatrix == -1)
		std::cout << "Probl�m s Uniform Location lightColor\n";
	glUniform4fv(idMatrix, 1, glm::value_ptr(this->lightColor));
}

void Light::update(GLuint shaderProgram)
{
	this->useLightPosition(shaderProgram);
	this->useLightColor(shaderProgram);
}
