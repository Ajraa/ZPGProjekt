#include "Shape.h"

Shape::Shape(const float* vertices, int size, int points)
{
	this->vertices = vertices;
	this->size = size;
	this->points = points;
}

const float* Shape::getVertices()
{
	return this->vertices;
}

int Shape::getSize()
{
	return this->size;
}

int Shape::getPoints()
{
	return this->points;
}
