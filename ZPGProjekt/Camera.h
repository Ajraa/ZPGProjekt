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

class Shader;
class Camera
{
public:
	Camera();
	void updateCamera();
	void addShader(Shader* shader);
	void useProjection();
	void useView();
	void setTarget();
	void moveForward();
	void moveBackwards();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void moveCursor(double x, double y);
private:
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	std::vector<Shader*> shaders;
	double lastX;
	double lastY;
	double sensitivity;
	double alpha;
	double fi;
	glm::vec3 cameraSpeed;
};

