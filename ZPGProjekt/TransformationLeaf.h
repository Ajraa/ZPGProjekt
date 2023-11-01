#pragma once
#include "Transformation.h"


class TransformationComposite;
class TransformationLeaf : public Transformation
{
public:
	TransformationLeaf();
	bool isComposite() override;
	virtual void rotate(float degrees) override;
	virtual void rotate(float degrees, glm::vec3 point);
	virtual void translate(float x, float y, float z) override;
	virtual void scale(float scale) override;
	void useTransform(GLint shader) override;
	void rotateAround(float angle, glm::vec3 point, glm::vec3 origin) override;
	glm::mat4 getMatrix();
	void setParent(Transformation* t);

private:
	Transformation* parent;
};

