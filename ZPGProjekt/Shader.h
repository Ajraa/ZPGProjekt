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
#include "CameraObserver.h"
#include "Light.h"

class Camera;
class Shader : public CameraObserver, public LightObserver
{
public:
	Shader(const char* vertexFilePath, const char* fragmentFilePath, CameraSubject* subject);
	~Shader();
	GLuint getShaderProgram() { return this->shaderProgram; };
	void useShaderProgram();
	void useProjection(glm::mat4 projection) override;
	void useView(glm::mat4 view) override;
	void setSubject(CameraSubject* subject) override;
	void notifyCamera() override;
	void addLight(LightSubject* light);
	void setLight(std::vector<LightSubject*> lights);
	void notifyLight() override;
	void useLightPosition(glm::vec3 lightPosition, int index);
	void useLightColor(glm::vec3 lightColor, int index);
	void useLightDirection(glm::vec3 lightDirection, int index);
	void useAmbient(glm::vec3 ambient);
	void useDiffuse(glm::vec3 diffuse);
	void useShininess(GLfloat shininess);
	void useSpecular(glm::vec3 specular);
	void useTransformationMatrix(glm::mat4 transform);
	void useCameraPosition(glm::vec3 eye);
	void useCameraTarget(glm::vec3 target);
	void useLightType(int type, int index);
	void useLight(glm::vec4 lightColor, glm::vec3 lightPosition, LightType type, int index);
private:
	std::string readShaderFile(const char* filePath);
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	int idProjectionMatrix;
	int idViewMatrix;
	CameraSubject* subject;
	std::vector<LightSubject*> lights;
};

