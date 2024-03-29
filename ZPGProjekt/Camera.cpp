﻿#include "Camera.h"
#include "Shader.h"

Camera::Camera()
{
	this->lastX = 400;
	this->lastY = 300;
	this->sensitivity = 0.5;
	this->alpha = 0;
	this->fi = 0;

	this->projection = glm::perspective(45.0f, 800.f / 600.f, 0.1f, 100.0f);
	this->width = 800.f;
	this->height = 600.f;
	this->eye = glm::vec3(5.0, 1.0, 0.f);
	this->target = glm::vec3(0, 0, 0);
	this->up = glm::vec3(0.f, 1.f, 0.f);
	this->model = glm::mat4(1.0f);
	
	this->setTarget();
	this->cameraSpeed = glm::vec3(0.1, 0.1, 0.1);
}

void Camera::updateCamera()
{
	this->view = glm::lookAt(eye, eye + target, up);
}

void Camera::useProjection()
{
	for (CameraObserver* observer : this->observers)
		observer->useProjection(this->projection);
}

void Camera::useView()
{
	for (CameraObserver* observer : this->observers)
		observer->useView(this->view);
}

void Camera::setTarget()
{
	//if (alpha > -5.f) alpha = -5.f;
	//if (alpha < -179.f) alpha = -179.f;
	if (alpha > 89.f) alpha = 89.f;
	if (alpha < -89.f) alpha = -89.f;

	glm::vec3 dir = glm::vec3();

	//dir.x = sin(glm::radians(alpha)) * cos(glm::radians(fi));
	//dir.z = sin(glm::radians(alpha)) * sin(glm::radians(fi));
	//dir.y = cos(glm::radians(alpha));
	//target = glm::vec3(glm::normalize(dir));
	target.x = (cos(glm::radians(fi)));
	target.z = (sin(glm::radians(fi)));
	target.y = sin(glm::radians(alpha));
	this->updateCamera();
}

void Camera::moveForward()
{
	eye += cameraSpeed * glm::normalize(this->target);
	this->updateCamera();
}

void Camera::moveBackwards()
{
	eye -= cameraSpeed * glm::normalize(this->target);
	this->updateCamera();
}

void Camera::moveLeft()
{
	eye -= cameraSpeed * (glm::normalize(glm::cross(target, up)));
	this->updateCamera();
}

void Camera::moveRight()
{
	eye += cameraSpeed * (glm::normalize(glm::cross(target, up)));
	this->updateCamera();
}

void Camera::moveUp()
{
	eye += cameraSpeed * glm::normalize(this->up);
	this->updateCamera();
}

void Camera::moveDown()
{
	eye -= cameraSpeed * glm::normalize(this->up);
	this->updateCamera();
}

void Camera::moveCursor(double x, double y)
{
	float xOffset = (x - lastX) * sensitivity;
	float yOffset = (lastY - y) * sensitivity;

	lastX = x;
	lastY = y;


	fi += xOffset;
	alpha += yOffset;

	this->setTarget();
	
}

void Camera::attach(CameraObserver* observer)
{
	this->observers.push_back(observer);
}

void Camera::detach(CameraObserver* observer)
{
	int i = 0;
	for (CameraObserver* obs : this->observers)
	{
		if (observer == obs)
			break;
		i++;
	}
	if (i < this->observers.size())
		this->observers.erase(this->observers.begin() + i);
}

void Camera::update()
{
	this->useProjection();
	this->useView();
}

void Camera::setProjection(float height, float width)
{
	this->projection = glm::perspective(45.0f, width/height, 0.1f, 100.0f);
	this->height = height;
	this->width = width;
}

void Camera::useProjection(GLuint shaderProgram)
{
	int idMatrix = glGetUniformLocation(shaderProgram, "projectionMatrix");
	if (idMatrix == -1)
		std::cout << "Problém s Uniform Location projectionMatrix\n";
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, glm::value_ptr(this->projection));
}

void Camera::useView(GLuint shaderProgram)
{
	int idMatrix = glGetUniformLocation(shaderProgram, "viewMatrix");
	if (idMatrix == -1)
		std::cout << "Problém s Uniform Location viewMatrix\n";
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, glm::value_ptr(this->view));
}

void Camera::useCameraPosition(GLuint shaderProgram)
{
	int idMatrix = glGetUniformLocation(shaderProgram, "cameraPosition");
	if (idMatrix == -1)
		std::cout << "Problém s Uniform Location cameraPosition\n";
	glUniform3fv(idMatrix, 1, glm::value_ptr(this->eye));
}

void Camera::update(GLuint shaderProgram)
{
	this->useProjection(shaderProgram);
	this->useView(shaderProgram);
	this->useCameraPosition(shaderProgram);
}

void Camera::updateShader(CameraObserver* shader)
{
	((Shader*)shader)->useProjection(this->projection);
	((Shader*)shader)->useView(this->view);
	
}

void Camera::updateShaderPosition(CameraObserver* shader)
{
	((Shader*)shader)->useCameraPosition(this->eye);
	((Shader*)shader)->useCameraTarget(this->target);
}

glm::vec3 Camera::getPosition()
{
	return this->eye;
}

glm::vec3 Camera::getResolution()
{
	return glm::vec3();
}

glm::mat4 Camera::getProjection()
{
	return this->projection;
}

glm::mat4 Camera::getView()
{
	return this->view;
}

glm::mat4 Camera::getModel()
{
	return this->model;
}

void Camera::swapProjection()
{
	if (ort) {
		this->projection = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
		this->ort = false;
		std::cout << "Perspective" << std::endl;
	}
	else {
		this->projection = glm::ortho(0, 400, 0, 400, -1, 400);
		this->ort = true;
		std::cout << "Ortho" << std::endl;
	}
}
