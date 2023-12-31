#pragma once
#include "Model.h"
#include "Transformation.h"
#include "Shader.h"
#include "TransformationComposite.h"
#include "TransformationLeaf.h"
#include "Material.h"
#include "SkyCube.h"

class DrawableObject
{
public:
	DrawableObject(Shader* shader, Model* model);
	DrawableObject(Shader* shader);
	DrawableObject(Shader* shader, const char* texture, const char* obj);
	void setMaterial(Material* material);
	void setShader(Shader* shader);
	Shader* getShader();
	void setModel(Model* model);
	~DrawableObject();
	void rotate(float degrees);
	void rotate(float degrees, glm::vec3 point);
	void translate(float x, float y, float z);
	void translate(glm::vec3 position);
	void scale(float scale);
	void initialize();
	void render();
	void addLight(LightSubject* light);
	void setLight(std::vector<Light*> lights);
	void rotateAround(float angle, glm::vec3 point, glm::vec3 origin);
	glm::vec3 getXYZ();
	void setTextureId(int id);
	void setTexture(const char* texture);
	void setObj(const char* obj);
	int getTextureId();
private:
	Transformation* transformation;
	Renderable* model;
	Shader* shader;
	Material* material;
};

