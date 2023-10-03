#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Shape.h"

class Model
{
public:
	Model();
	~Model();
	void createVAO();
	void createVBO();
	void addShape(float* points, int size);
	GLuint getVAO() { return this->VAO; };
	GLuint* getVBO() { return this->VBO; };
	int getSize() { return this->shapes.size(); };
private:
	GLuint VAO;
	GLuint* VBO;
	std::vector<Shape> shapes;
};

