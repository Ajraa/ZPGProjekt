#include "DrawableObject.h"

DrawableObject::DrawableObject(const char* vertexFilePath, const char* fragmentFilePath, float* points, int size)
{
	this->shader = new Shader(vertexFilePath, fragmentFilePath);
	this->model = new Model(points, size);
	this->transformation = new Transformation();
}

DrawableObject::DrawableObject(Shader* shader, Shape* shape)
{
	this->shader = shader;
	this->model = new Model(shape);
	this->transformation = new Transformation();
}

DrawableObject::DrawableObject(Shader* shader, Model* model)
{
	this->shader = shader;
	this->model = model;
	this->transformation = new Transformation();
}

void DrawableObject::setShader(Shader* shader)
{
	this->shader = shader;
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
	this->shader->shade();
	this->model->createVAO();
	this->model->createVBO();
}

void DrawableObject::render()
{
	this->shader->useShaderProgram();
	this->transformation->useTransform(this->shader->getShaderProgram());
	this->model->drawArrays();
}
