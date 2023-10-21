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
#include "CameraSubject.h"

class CameraSubject;
class CameraObserver
{
public:
	virtual void useProjection(glm::mat4 projection) = 0;
	virtual void useView(glm::mat4 view) = 0;
	virtual void setSubject(CameraSubject* subject) = 0;
};

