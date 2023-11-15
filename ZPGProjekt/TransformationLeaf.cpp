#include "TransformationLeaf.h"
#include "Transformation.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TransformationComposite.h"

bool TransformationLeaf::isComposite()
{
    return false;
}

TransformationLeaf::TransformationLeaf()
{
	this->transformationMatrix = glm::mat4(1.0f);
	this->idModelTransform = -1;
}

void TransformationLeaf::rotate(float degrees)
{
	this->transformationMatrix = glm::rotate(glm::mat4(1.0f), (float)glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
}

void TransformationLeaf::rotate(float degrees, glm::vec3 point)
{
	this->transformationMatrix = glm::rotate(glm::mat4(1.0f), (float)glm::radians(degrees), point);
}

void TransformationLeaf::translate(float x, float y, float z)
{
	this->transformationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void TransformationLeaf::translate(glm::vec3 position)
{
	this->transformationMatrix = glm::translate(glm::mat4(1.0f), position);
}

void TransformationLeaf::scale(float scale)
{
	this->transformationMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
}

void TransformationLeaf::useTransform(GLint shader)
{
	this->idModelTransform = glGetUniformLocation(shader, "modelMatrix");
	if (this->idModelTransform == -1)
		std::cout << "Problém s Uniform Location modelMatrix\n";
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, glm::value_ptr(this->transformationMatrix));
}

void TransformationLeaf::rotateAround(float angle, glm::vec3 point, glm::vec3 origin)
{
	glm::mat4 t1 = glm::translate(glm::mat4(1.0f), point);
	glm::mat4 t2 = glm::rotate(glm::mat4(1.0f), (float)glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 t3 = glm::translate(glm::mat4(1.0f), origin);
	this->transformationMatrix = t1* t2 * t3;
}

glm::mat4 TransformationLeaf::getMatrix()
{
	return this->transformationMatrix;
}

void TransformationLeaf::setParent(Transformation* t)
{
	this->parent = t;
}

