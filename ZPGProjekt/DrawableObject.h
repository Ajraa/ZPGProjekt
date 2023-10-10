#pragma once
#include "Model.h"
#include "Shader.h"
#include "Transformation.h"

class DrawableObject
{
public:
	DrawableObject(Shader* shader, Model* model);
	~DrawableObject();
	void rotate(float degrees);
	void translate(glm::mat4 view);
	void scale(float scale);
	void initializeModel();
	void render();
private:
	Transformation* transformation;
	Model* model;
	Shader* shader;
};

