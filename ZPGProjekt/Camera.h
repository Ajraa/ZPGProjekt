#pragma once
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "CameraSubject.h"

class Shader;
class Camera : public CameraSubject
{
public:
	Camera();
	void updateCamera();
	void useProjection() override;
	void useView() override;
	void setTarget();
	void moveForward();
	void moveBackwards();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void moveCursor(double x, double y);
	void attach(CameraObserver* observer) override;
	void detach(CameraObserver* observer) override;
	void update() override;
	void setProjection(float height, float width);
	void useProjection(GLuint shaderProgram) override;
	void useView(GLuint shaderProgram) override;
	void useCameraPosition(GLuint shaderProgram);
	void update(GLuint shaderProgram) override;
	void updateShader(CameraObserver* shader);
	glm::vec3 getPosition();
private:
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	std::vector<CameraObserver*> observers;
	double lastX;
	double lastY;
	double sensitivity;
	double alpha;
	double fi;
	glm::vec3 cameraSpeed;
};

