#include "Transformation.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Transformation::Transformation()
{
	this->transformationMatrix = glm::mat4(1.0f);
}

void Transformation::rotate(float degrees)
{
	this->transformationMatrix = glm::rotate(glm::mat4(1.0f), (float)glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Transformation::translate(glm::mat4 view)
{
	this->transformationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

void Transformation::scale(float scale)
{
	this->transformationMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
}

void Transformation::useTransform(GLint shader)
{
	this->idModelTransform = glGetUniformLocation(shader, "modelMatrix");
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, &this->transformationMatrix[0][0]);
}