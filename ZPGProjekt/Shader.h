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

class Camera;
class Shader
{
public:
	Shader(const char* vertexFilePath, const char* fragmentFilePath);
	~Shader();
	void shade();
	GLuint getShaderProgram() { return this->shaderProgram; };
	void useShaderProgram();
	void useProjection(glm::mat4 projection);
	void useView(glm::mat4 view);
private:
	std::string readShaderFile(const char* filePath);

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	int idProjectionMatrix;
	int idViewMatrix;
};

