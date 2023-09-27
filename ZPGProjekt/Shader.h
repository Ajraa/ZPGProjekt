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

class Shader
{
public:
	Shader(const char* vertex_shader, const char* fragment_shader);
	void shade();
	GLuint getShaderProgram() { return this->shaderProgram; };
private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	const char* vertex_shader;
	const char* fragment_shader;
};

