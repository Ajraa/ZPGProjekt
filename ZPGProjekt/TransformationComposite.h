#pragma once
#include "Transformation.h"
#include <vector>

class TransformationLeaf;
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
	glm::vec3 getXYZ();
	glm::mat4 getOrigin();
	void rotateAround(float angle, glm::vec3 point, glm::vec3 origin) override;
private:
	std::vector<Transformation*> children;
	glm::mat4 origin;
};

