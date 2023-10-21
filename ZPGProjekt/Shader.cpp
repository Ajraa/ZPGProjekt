#include "Shader.h"
#include "Camera.h"
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
    std::string vertexTmp = readShaderFile(vertexFilePath);
    std::string fragmentTmp = readShaderFile(fragmentFilePath);
    const char* vertex_shader = vertexTmp.c_str();
    const char* fragment_shader = fragmentTmp.c_str();

    int status;

    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
        std::cout << "Vertex shader se nezkompiloval\n";

    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
        std::cout << "Fragment shader se nezkompiloval\n";

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
