#include "Shader.h"
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
    std::string vertexTmp = readShaderFile(vertexFilePath);
    std::string fragmentTmp = readShaderFile(fragmentFilePath);
    this->vertex_shader = vertexTmp.c_str();
    this->fragment_shader = fragmentTmp.c_str();

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
}

Shader::~Shader()
{
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    glDeleteProgram(this->shaderProgram);
}

void Shader::shade()
{

    this->shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    int status;
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
        std::cout << "Shader program se nezkompiloval\n";
}

void Shader::useShaderProgram()
{
    glUseProgram(this->shaderProgram);
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
