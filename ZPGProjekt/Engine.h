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
#include "DrawableObject.h"
#include "Camera.h"
#include "Light.h"
#include "Reflector.h"

class Engine
{
public:
	~Engine();
	void start();
	void run();
	void createObjects();
	void initialization();
	void processUserInput();
	void processClick();
private:
	std::vector<Light*> lights;
	GLFWwindow* window;
	Camera* camera;
	GLint status;
	std::vector<DrawableObject*> objects;
};