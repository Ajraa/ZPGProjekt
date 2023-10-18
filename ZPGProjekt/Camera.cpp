#include "Camera.h"
#include "Shader.h"

Camera::Camera()
{
	this->projection = glm::perspective(45.0f, 800.f / 600.f, 0.1f, 100.0f);
	this->eye = glm::vec3(5.0, 0, 0);
	this->target = glm::vec3(0, 0, 0);
	this->up = glm::vec3(0.f, 1.f, 0.f);
	this->model = glm::mat4(1.0f);
	this->view = glm::lookAt(eye, target, up);
}

void Camera::updateCamera()
{
	this->view = glm::lookAt(eye, target, up);
}

void Camera::addShader(Shader* shader)
{
	this->shaders.push_back(shader);
}

void Camera::useProjection()
{
	for (Shader* shader : this->shaders)
		shader->useProjection(this->projection);
}

void Camera::useView()
{
	for (Shader* shader : this->shaders)
		shader->useView(this->view);
}

void Camera::setTarget(float alpha, float fi)
{
	if (alpha >= 90) alpha = 89;
	if (fi >= 90) fi = 89;
	target.x = sin(alpha) * cos(fi);
	target.z = sin(alpha) * sin(fi);
	target.y = cos(alpha);
}

void Camera::moveForward()
{
	eye += glm::normalize(this->target);
}

void Camera::moveBackwards()
{
	eye -= glm::normalize(this->target);
}

void Camera::moveLeft()
{
	eye += (glm::normalize(glm::cross(target, up)));
	this->updateCamera();
}

void Camera::moveRight()
{
	eye -= (glm::normalize(glm::cross(target, up)));
	this->updateCamera();
}
