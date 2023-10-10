#pragma once
#include "Model.h"
#include "Transformation.h"
#include "Shader.h"

class DrawableObject
{
public:
	DrawableObject(const char* vertexFilePath, const char* fragmentFilePath, float* points, int size);
	DrawableObject(Shader* shader, Shape* shape);
	DrawableObject(Shader* shader, Model* model);
	DrawableObject() {};
	void setShader(Shader* shader);
	void setModel(Model* model);
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

