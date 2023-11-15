#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
#include <GL/glew.h>

class Transformation
{
public:
	Transformation();
	virtual void rotate(float degrees);
	virtual void rotate(float degrees, glm::vec3 point);
	virtual void translate(float x, float y, float z);
	virtual void translate(glm::vec3 position);
	virtual void scale(float scale);
	virtual void useTransform(GLint shader);
	virtual bool isComposite();
	virtual glm::mat4 getMatrix();
	virtual void rotateAround(float angle, glm::vec3 point, glm::vec3 origin) = 0;
protected:
	Transformation* parent;
	glm::mat4 transformationMatrix;
	int idModelTransform;
};

