#include "TransformationComposite.h"
#include "TransformationLeaf.h"

void TransformationComposite::add(Transformation* transformation)
{
	this->children.push_back(transformation);
}

void TransformationComposite::clear()
{
	this->children.clear();
}

bool TransformationComposite::isComposite()
{
	return true;
}

void TransformationComposite::useTransform(GLint shader)
{
	this->transformationMatrix = glm::mat4(1.0f);
	for(Transformation* var : this->children) {
		this->transformationMatrix *= ((TransformationLeaf*)var)->getMatrix();
		if (var->isComposite())
			((TransformationComposite*)var)->clear();
		this->children.clear();
	}
	
	this->idModelTransform = glGetUniformLocation(shader, "modelMatrix");
	if (this->idModelTransform == -1)
		std::cout << "Problém s Uniform Location modelMatrix\n";
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, glm::value_ptr(this->transformationMatrix));
}
void TransformationComposite::translate(float x, float y, float z)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->setParent(this);
	leaf->translate(x, y, z);
	this->children.push_back(leaf);
}

void TransformationComposite::scale(float scale)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->setParent(this);
	leaf->scale(scale);
	this->children.push_back(leaf);
}

glm::mat4 TransformationComposite::getMatrix()
{
	this->transformationMatrix = glm::mat4(1.0f);
	for (Transformation* var : this->children) {
		this->transformationMatrix *= ((TransformationLeaf*)var)->getMatrix();
		if (var->isComposite())
			((TransformationComposite*)var)->clear();
	}
	this->children.clear();
	this->origin = this->transformationMatrix;
	return this->transformationMatrix;
}

glm::vec3 TransformationComposite::getXYZ()
{
	return glm::vec3(this->transformationMatrix[3]);
}

glm::mat4 TransformationComposite::getOrigin()
{
	return this->origin;
}

void TransformationComposite::rotateAround(float angle, glm::vec3 point, glm::vec3 origin)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->setParent(this);
	leaf->rotateAround(angle, point, origin);
	this->children.push_back(leaf);
}

void TransformationComposite::rotate(float degrees)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->setParent(this);
	leaf->rotate(degrees);
	this->children.push_back(leaf);
}

void TransformationComposite::rotate(float degrees, glm::vec3 point)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->setParent(this);
	leaf->rotate(degrees, point);
	this->children.push_back(leaf);
}
