#include "Shape.h"

Shape::Shape(float* points, int size)
{
	this->points = points;
	this->size = size;
}

float* Shape::getPoints()
{
	return this->points;
}

int Shape::getSize()
{
	return this->size;
}
