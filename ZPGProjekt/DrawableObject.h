#pragma once
#include "Model.h"
#include "Transformation.h"
#include "Shader.h"
#include "TransformationComposite.h"
#include "TransformationLeaf.h"
#include "Material.h"

class DrawableObject
{
public:
	DrawableObject(Shader* shader, Model* model);
	void setMaterial(Material* material);
	void setShader(Shader* shader);
	Shader* getShader();
	void setModel(Model* model);
	~DrawableObject();
	void rotate(float degrees);
	void rotate(float degrees, glm::vec3 point);
	void translate(float x, float y, float z);
	void scale(float scale);
	void initialize();
	void render();
	void addLight(Light* light);
	void rotateAround(float angle, glm::vec3 point, glm::vec3 origin);
	glm::vec3 getXYZ();
private:
	Transformation* transformation;
	Model* model;
	Shader* shader;
	Material* material;
};

