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
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
#include "Shape.h"
#include "Renderable.h"
#include <vector>

class Model : public Renderable
{
public:
	Model(const float* vertices, int size, int points);
	Model(Shape* shape);
	Model(const char* obj, const char* texture);
	~Model();
	void createVAO() override;
	void createVBO() override;
	void drawArrays() override;
	void setTextureID(int id);
	int getTextureId() override;
	void setTexture(const char* texture);
	void setObj(const char* obj);
private:
	std::vector<float> loadModel(const char* fileName);

	int textureID;
	GLuint VAO;
	GLuint VBO;
	Shape* shape;
	const char* texture;
	const char* obj;
	int count;
	GLuint tID;
};

