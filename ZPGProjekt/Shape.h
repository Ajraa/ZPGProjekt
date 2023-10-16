#pragma once
class Shape
{
public:
	Shape(const float* vertices, int size, int points);
	const float* getVertices();
	int getSize();
	int getPoints();
private:
	const float* vertices;
	int size;
	int points;
};

