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
#include "LightObserver.h"

class LightSubject
{
public:
	virtual void attach(LightObserver* observer) = 0;
	virtual void detach(LightObserver* observer) = 0;
	virtual void useLightPosition(GLuint shaderProgram) = 0;
	virtual void useLightColor(GLuint shaderProgram) = 0;
	virtual void update(LightObserver* obs) = 0;
};

