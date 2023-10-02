#include "Model.h"

Model::Model()
{
    this->VAO = 0;
}

Model::~Model()
{
    for (int i = 0; i < this->VBOs.size(); i++)
        glDeleteBuffers(1, &this->VBOs[i]);
    glDeleteVertexArrays(1, &VAO);
   
}

void Model::createVAO()
{
    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    std::cout << this->VBOs.size() << std::endl;
    for (int i = 0; i < this->VBOs.size(); i++)   
        glBindBuffer(GL_ARRAY_BUFFER, this->VBOs[i]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);   
}

void Model::createVBO(float* points, int size)
{
    GLuint VBO;
    //vertex buffer object (VBO)
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);
    this->VBOs.push_back(VBO);
}
