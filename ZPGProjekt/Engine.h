#pragma once
#include <stdlib.h>
#include <iostream>
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Model.h"
#include "Callback.h"

class Engine
{
public:
	~Engine();
	void start();
	void run();
	void createShaders();
	void createModels();
	void initialization();
private:
	GLFWwindow* window;
	glm::mat4 Projection;
	glm::mat4 ViewModel;
	glm::mat4 View;
	GLint status;
	Shader* shader;
	Model* model;
};