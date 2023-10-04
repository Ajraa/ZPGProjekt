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

    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);
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
