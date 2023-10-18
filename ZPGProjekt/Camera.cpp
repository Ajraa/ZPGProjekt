#include "Camera.h"
#include "Shader.h"

Camera::Camera()
{
	this->lastX = 400;
	this->lastY = 300;
	this->sensitivity = 0.01;
	this->alpha = -89;
	this->fi = 0;
	this->projection = glm::perspective(45.0f, 800.f / 600.f, 0.1f, 100.0f);
	this->eye = glm::vec3(5.0, 0, 0);
	this->target = glm::vec3(0, 0, 0);
	this->up = glm::vec3(0.f, 1.f, 0.f);
	this->model = glm::mat4(1.0f);
	//this->view = glm::lookAt(eye, target, up);
	this->setTarget();
	this->cameraSpeed = glm::vec3(0.1, 0.1, 0.1);
}

void Camera::updateCamera()
{
	this->view = glm::lookAt(eye, eye + target, up);
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

void Camera::setTarget()
{
	if (alpha > 89 ) alpha = 89;
	if (fi > 89) fi = 89;
	if (alpha < 0) alpha = 1;
	if (fi < 0) fi = 1;
	target.x = sin(alpha) * cos(fi);
	target.z = sin(alpha) * sin(fi);
	target.y = cos(alpha);
	this->updateCamera();
}

void Camera::moveForward()
{
	eye += glm::normalize(cameraSpeed * this->target);
	this->updateCamera();
}

void Camera::moveBackwards()
{
	eye -= glm::normalize(cameraSpeed * this->target);
	this->updateCamera();
}

void Camera::moveLeft()
{
	eye -= (glm::normalize(cameraSpeed * glm::cross(target, up)));
	this->updateCamera();
}

void Camera::moveRight()
{
	eye += (glm::normalize(cameraSpeed * glm::cross(target, up)));
	this->updateCamera();
}

void Camera::moveUp()
{
	eye += glm::normalize(cameraSpeed * this->up);
	this->updateCamera();
}

void Camera::moveDown()
{
	eye -= glm::normalize(cameraSpeed * this->up);
	this->updateCamera();
}

void Camera::moveCursor(double x, double y)
{
	float xOffset = (x - lastX) * sensitivity;
	float yOffset = (lastY - y) * sensitivity;  // Reversed Y-coordinates

	lastX = x;
	lastY = y;

	// Apply the offset to the camera's orientation
	fi += xOffset;
	alpha += -1*yOffset;

	this->setTarget();
	
}
