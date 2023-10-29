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
	virtual void rotate(float degrees, glm::vec3 point) override;
	virtual void translate(float x, float y, float z) override;
	virtual void scale(float scale) override;
	virtual glm::mat4 getMatrix() override;
private:
	std::vector<Transformation*> children;
};

