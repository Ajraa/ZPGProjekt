#include "DrawableObject.h"

DrawableObject::DrawableObject(Shader* shader, Model* model)
{
	this->shader = shader;
	this->model = model;
	this->transformation = new TransformationComposite();
}

DrawableObject::DrawableObject(Shader* shader)
{
	this->shader = shader;
	this->model = new SkyCube();
	this->transformation = new TransformationComposite();
}

DrawableObject::DrawableObject(Shader* shader, const char* texture, const char* obj)
{
	this->shader = shader;
	this->model = new Model(obj, texture);
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

void DrawableObject::translate(glm::vec3 position)
{
	this->transformation->translate(position);
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

	if (Model* m = dynamic_cast<Model*>(this->model)) {
		this->shader->notifyCameraPosition();
		this->shader->notifyLight();
		this->shader->useAmbient(this->material->getAmbient());
		this->shader->useDiffuse(this->material->getDiffuse());
		this->shader->useShininess(this->material->getShininess());
		this->shader->useSpecular(this->material->getSpecular());
	}
	this->shader->useTransformationMatrix(this->transformation->getMatrix());
	
	
	this->shader->useTextureId(this->model->getTextureId());
	this->model->drawArrays();
}

void DrawableObject::addLight(LightSubject* light)
{
	this->shader->addLight(light);
}

void DrawableObject::setLight(std::vector<Light*> lights)
{
	for (LightSubject* light : lights)
		this->shader->addLight(light);
}

void DrawableObject::rotateAround(float angle, glm::vec3 point, glm::vec3 origin)
{
	this->transformation->rotateAround(angle, point, origin);
}

glm::vec3 DrawableObject::getXYZ()
{
	return ((TransformationComposite*)this->transformation)->getXYZ();
}

void DrawableObject::setTextureId(int id)
{
	if (Model* m = dynamic_cast<Model*>(this->model))
		m->setTextureID(id);
}

void DrawableObject::setTexture(const char* texture)
{
	if (Model* m = dynamic_cast<Model*>(this->model))
		m->setTexture(texture);
}

void DrawableObject::setObj(const char* obj)
{
	if (Model* m = dynamic_cast<Model*>(this->model))
		m->setObj(obj);
}
