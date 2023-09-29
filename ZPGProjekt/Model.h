#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Model
{
public:
	Model();
	void model(float *points, int size);
	GLuint getVBO() { return this->VBO; };
	GLuint getVAO() { return this->VAO; };
private:
	GLuint VBO;
	GLuint VAO;
};

