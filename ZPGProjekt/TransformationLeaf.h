#pragma once
#include "Transformation.h"


class TransformationLeaf : public Transformation
{
public:
	TransformationLeaf();
	bool isComposite() override;
	virtual void rotate(float degrees) override;
	virtual void translate(float x, float y, float z) override;
	virtual void scale(float scale) override;
	void useTransform(GLint shader) override;
	glm::mat4 getMatrix();
};

