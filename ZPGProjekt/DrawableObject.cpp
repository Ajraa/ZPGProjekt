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
	this->transformation = new TransformationComposite();
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
	this->shader->shade();
	this->model->createVBO();
	this->model->createVAO();
}

void DrawableObject::render()
{
	this->shader->useShaderProgram();
	this->transformation->useTransform(this->shader->getShaderProgram());
	this->model->drawArrays();
}
