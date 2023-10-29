#include "DrawableObject.h"

DrawableObject::DrawableObject(Shader* shader, Model* model)
{
	this->shader = shader;
	this->model = model;
	this->transformation = new TransformationComposite();
}

void DrawableObject::setMaterial(Material* material)
{
	this->material = material;
}

void DrawableObject::setShader(Shader* shader)
{
	this->shader = shader;
}

Shader* DrawableObject::getShader()
{
	return this->shader;
}

void DrawableObject::setModel(Model* model)
{
	this->model = model;
}

DrawableObject::~DrawableObject()
{
	delete this->shader;
	delete this->model;
}

void DrawableObject::rotate(float degrees)
{
	this->transformation->rotate(degrees);
}

void DrawableObject::rotate(float degrees, glm::vec3 point)
{
	this->transformation->rotate(degrees, point);
}

void DrawableObject::translate(float x, float y, float z)
{
	this->transformation->translate(x, y, z);
}

void DrawableObject::scale(float scale)
{
	this->transformation->scale(scale);
}

void DrawableObject::initialize()
{
	this->model->createVBO();
	this->model->createVAO();
}

void DrawableObject::render()
{
	this->shader->useShaderProgram();
	this->shader->notifyCamera();
	//this->shader->notifyLight();
	this->shader->updateLight();
	this->shader->useAmbient(this->material->getAmbient());
	this->shader->useDiffuse(this->material->getDiffuse());
	this->shader->useShininess(this->material->getShininess());
	this->shader->useSpecular(this->material->getSpecular());
	//this->transformation->useTransform(this->shader->getShaderProgram());
	this->shader->useTransformationMatrix(this->transformation->getMatrix());
	this->model->drawArrays();
}

void DrawableObject::addLight(Light* light)
{
	this->shader->setLight(light);
}
