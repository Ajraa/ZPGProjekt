#include "DrawableObject.h"

DrawableObject::DrawableObject(Shader* shader, Model* model)
{
	this->model = model;
	this->shader = shader;
	this->transformation = new Transformation();
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

void DrawableObject::translate(glm::mat4 view)
{
	this->transformation->translate(view);
}

void DrawableObject::scale(float scale)
{
	this->transformation->scale(scale);
}

void DrawableObject::initializeModel()
{
	this->model->createVAO();
	this->model->createVBO();
}

void DrawableObject::render()
{
	this->shader->useShaderProgram();
	this->transformation->useTransform(this->shader->getShaderProgram());
	this->model->drawArrays();
}
