#include "Model.h"

Model::Model()
{
    this->VAO = 0;
}

Model::~Model()
{
    for (int i = 0; i < this->getSize(); i++)
        glDeleteBuffers(1, &this->VBO[i]);
    glDeleteVertexArrays(1, &VAO);
   
}

void Model::createVAO()
{
    //vertex setup
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Sets up the format, *without* a buffer object.
    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    //Sets up where the buffer object comes from
    glVertexAttribBinding(0, 0);
    //Enable VAO
    glEnableVertexAttribArray(0);
    //Done with VAO
    glBindVertexArray(0);
}

void Model::createVBO()
{
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, this->shapes[0].getSize(), this->shapes[0].getPoints(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, this->shapes[1].getSize(), this->shapes[1].getPoints(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::addShape(float* points, int size)
{
    this->shapes.push_back(Shape(points, size));
}
