#include "TransformationComposite.h"

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
	this->idModelTransform = glGetUniformLocation(shader, "modelMatrix");
	if (this->idModelTransform == -1)
		std::cout << "Problém s Uniform Location modelMatrix\n";
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, &this->transformationMatrix[0][0]);

	for(Transformation* var : this->children) {
		var->useTransform(shader);
		if (var->isComposite())
			((TransformationComposite*)var)->clear();
		this->children.clear();
	}
}
void TransformationComposite::translate(float x, float y, float z)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->translate(x, y, z);
	this->children.push_back(leaf);
}

void TransformationComposite::scale(float scale)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->scale(scale);
	this->children.push_back(leaf);
}

void TransformationComposite::rotate(float degrees)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->rotate(degrees);
	this->children.push_back(leaf);
}
