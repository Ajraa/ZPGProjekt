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

class Material
{
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess);
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	float getShininess();
private:
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;
	GLfloat shininess;
};

