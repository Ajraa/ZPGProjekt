#pragma once
#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Renderable.h"


class Shader;
class SkyCube : public Renderable
{
public:
	SkyCube();
	void createVAO() override;
	void createVBO() override;
	void drawArrays() override;
	int getTextureId() override;
private:
	GLuint VAO;
	GLuint VBO;
	int textureId;
};

