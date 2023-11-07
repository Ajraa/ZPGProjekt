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
#include <vector>
#include "LightSubject.h"
#include "LightType.h"

class Light : public LightSubject
{
public:
	Light(LightType type, glm::vec3 lightPosition, glm::vec4 lightColor, float intensity, float specularStrength);
	void setDirection(glm::vec3 direction);
	void attach(LightObserver* observer) override;
	void detach(LightObserver* observer) override;
	glm::vec3 getLightPosition();
	glm::uvec4 getLightColor();
	void useLightPosition(GLuint shaderProgram) override;
	void useLightColor(GLuint shaderProgram) override;
	void update(LightObserver* obs, int index) override;
	void setLightPosition(glm::vec3 position);
private:
	glm::vec3 lightPosition;
	glm::vec4 lightColor;
	glm::vec3 direction;
	float intensity;
	float specularStrength;
	std::vector<LightObserver*> observers;
	LightType type;
};

