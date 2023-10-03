#pragma once
class Shape
{
public:
	Shape(float* points, int size);
	float* getPoints();
	int getSize();
private:
	float* points;
	int size;
};

