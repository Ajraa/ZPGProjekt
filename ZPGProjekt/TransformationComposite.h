#pragma once
#include "Transformation.h"
#include "TransformationLeaf.h"
#include <vector>

class TransformationComposite : public Transformation
{
public:
	void add(Transformation* transformation);
	void clear();
	bool isComposite() override;
	virtual void useTransform(GLint shader) override;
	virtual void rotate(float degrees) override;
	virtual void translate(float x, float y, float z) override;
	virtual void scale(float scale) override;
	virtual void initComposite();
private:
	std::vector<Transformation*> children;
};
