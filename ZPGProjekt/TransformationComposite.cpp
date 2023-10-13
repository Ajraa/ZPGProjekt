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
	for(Transformation* var : this->children) {
		var->useTransform(shader);
		if (var->isComposite())
			((TransformationComposite*)var)->clear();
	}
}
void TransformationComposite::translate(float x, float y, float z)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->translate(x, y, z);
	((TransformationComposite*)this->children[0])->add(leaf);
}

void TransformationComposite::scale(float scale)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->scale(scale);
	((TransformationComposite*)this->children[1])->add(leaf);
}

void TransformationComposite::rotate(float degrees)
{
	TransformationLeaf* leaf = new TransformationLeaf();
	leaf->rotate(degrees);
	((TransformationComposite*)this->children[2])->add(leaf);
}


void TransformationComposite::initComposite()
{
	this->add(new TransformationComposite()); // 0 translate
	this->add(new TransformationComposite()); // 1 scale
	this->add(new TransformationComposite()); // 2 rotate
}
