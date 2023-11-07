#include "Shader.h"
#include "Camera.h"
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath, CameraSubject* subject)
{
    std::string vertexTmp = readShaderFile(vertexFilePath);
    std::string fragmentTmp = readShaderFile(fragmentFilePath);
    const char* vertex_shader = vertexTmp.c_str();
    const char* fragment_shader = fragmentTmp.c_str();
    this->subject = subject;
    this->subject->attach(this);

    int status;

    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
      std::cout << "Vertex shader se nezkompiloval\n";
      GLchar InfoLog[256];
      glGetShaderInfoLog(vertexShader, sizeof(InfoLog), NULL, InfoLog);
      std::cout << InfoLog << std::endl;
    }

    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
      std::cout << "Fragment shader se nezkompiloval\n";
      GLchar InfoLog[256];
      glGetShaderInfoLog(fragmentShader, sizeof(InfoLog), NULL, InfoLog);
      std::cout << InfoLog << std::endl;
    }

    this->shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
        std::cout << "Shader program se nezkompiloval\n";
}

Shader::~Shader()
{
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    glDeleteProgram(this->shaderProgram);
}

void Shader::useShaderProgram()
{
    glUseProgram(this->shaderProgram);
}

void Shader::useProjection(glm::mat4 projection)
{
    this->idProjectionMatrix = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
    if (this->idProjectionMatrix == -1)
        std::cout << "Problém s Uniform Location projectionMatrix\n";
    glUniformMatrix4fv(this->idProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projection));
    
}

void Shader::useView(glm::mat4 view)
{
    this->idViewMatrix = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    if (this->idViewMatrix == -1)
        std::cout << "Problém s Uniform Location viewMatrix\n";
    glUniformMatrix4fv(this->idViewMatrix, 1, GL_FALSE, glm::value_ptr(view));
}

void Shader::setSubject(CameraSubject* subject)
{
    this->subject = subject;
}

void Shader::notifyCamera()
{
    //this->subject->update(this->shaderProgram);
    ((Camera*)this->subject)->updateShader(this);
}

void Shader::notifyLight()
{
  this->light->update(this);
}

void Shader::useLightPosition(glm::vec3 lightPosition)
{
    int idMatrix = glGetUniformLocation(shaderProgram, "lightPosition");
    if (idMatrix == -1)
        std::cout << "Problém s Uniform Location lightPosition\n";
    glUniform3fv(idMatrix, 1, glm::value_ptr(lightPosition));
}

void Shader::useLightColor(glm::vec3 lightColor)
{
    int idMatrix = glGetUniformLocation(shaderProgram, "lightColor");
    if (idMatrix == -1)
        std::cout << "Problém s Uniform Location lightColor\n";
    glUniform4fv(idMatrix, 1, glm::value_ptr(lightColor));
}

void Shader::useAmbient(glm::vec3 ambient)
{
    int idMatrix = glGetUniformLocation(shaderProgram, "matAmbient");
    if (idMatrix == -1)
        std::cout << "Problém s Uniform Location matAmbient\n";
    glUniform3fv(idMatrix, 1, glm::value_ptr(ambient));
}

void Shader::useDiffuse(glm::vec3 diffuse)
{
    int idMatrix = glGetUniformLocation(shaderProgram, "matDiffuse");
    if (idMatrix == -1)
        std::cout << "Problém s Uniform Location matDiffuse\n";
    glUniform3fv(idMatrix, 1, glm::value_ptr(diffuse));
}

void Shader::useShininess(GLfloat shininess)
{
    int idMatrix = glGetUniformLocation(shaderProgram, "matShininess");
    if (idMatrix == -1)
        std::cout << "Problém s Uniform Location matShininess\n";
    glUniform1fv(idMatrix, 1, &shininess);
}

void Shader::useSpecular(glm::vec3 specular)
{
    int idMatrix = glGetUniformLocation(shaderProgram, "matSpecular");
    if (idMatrix == -1)
        std::cout << "Problém s Uniform Location matSpecular\n";
    glUniform3fv(idMatrix, 1, glm::value_ptr(specular));
}

void Shader::useTransformationMatrix(glm::mat4 transform)
{
    int idMatrix = glGetUniformLocation(this->shaderProgram, "modelMatrix");
    if (idMatrix == -1)
        std::cout << "Problém s Uniform Location modelMatrix\n";
    glUniformMatrix4fv(idMatrix, 1, GL_FALSE, glm::value_ptr(transform));
}

void Shader::useCameraPosition(glm::vec3 eye)
{
    int idMatrix = glGetUniformLocation(this->shaderProgram, "cameraPosition");
    if (idMatrix == -1)
        std::cout << "Problém s Uniform Location cameraPosition\n";
    glUniform3fv(idMatrix, 1, glm::value_ptr(eye));
}

void Shader::useCameraTarget(glm::vec3 front)
{
  int idMatrix = glGetUniformLocation(this->shaderProgram, "cameraFront");
  if (idMatrix == -1)
    std::cout << "Problém s Uniform Location cameraFront\n";
  glUniform3fv(idMatrix, 1, glm::value_ptr(front));
}

void Shader::useLightType(int type)
{
  int idMatrix = glGetUniformLocation(this->shaderProgram, "type");
  if (idMatrix == -1)
    std::cout << "Problém s Uniform Location cameraFront\n";
  glUniform1i(idMatrix, type);
}

void Shader::setLight(LightSubject* light)
{
  this->light = light;
}

std::string Shader::readShaderFile(const char* filePath)
{
    std::string shaderCode;
    std::ifstream shaderFile;

    // Ensure ifstream can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Error reading shader file: " << e.what() << std::endl;
    }

    return shaderCode;
}
