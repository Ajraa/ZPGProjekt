#pragma once
#include "Model.h"
#include "Transformation.h"
#include "Shader.h"
#include "TransformationComposite.h"
#include "TransformationLeaf.h"

class DrawableObject
{
public:
	DrawableObject(const char* vertexFilePath, const char* fragmentFilePath, float* points, int size);
	DrawableObject(Shader* shader, Shape* shape);
	DrawableObject(Shader* shader, Model* model);
	void setShader(Shader* shader);
	Shader* getShader();
	void setModel(Model* model);
	~DrawableObject();
	void rotate(float degrees);
	void translate(float x, float y, float z);
	void scale(float scale);
	void initialize();
	void render();
private:
	Transformation* transformation;
	Model* model;
	Shader* shader;
};

