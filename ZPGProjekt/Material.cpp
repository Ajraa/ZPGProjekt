#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess)
{
	this->ambient = ambient;
	this->specular = specular;
	this->diffuse = diffuse;
	this->shininess = shininess;
}

glm::vec3 Material::getAmbient()
{
	return this->ambient;
}

glm::vec3 Material::getDiffuse()
{
	return this->diffuse;
}

glm::vec3 Material::getSpecular()
{
	return this->specular;
}

float Material::getShininess()
{
	return this->shininess;
}
