#include "Model.h"

Model::Model(Shader* shader)
{
    this->VAO = 0;
    this->shader = shader;
}

Model::~Model()
{
    glDeleteBuffers(1, &VBO);
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
    glGenBuffers(2, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->shapes[0].getSize(), this->shapes[0].getPoints(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->shapes[1].getSize(), this->shapes[1].getPoints(), GL_STATIC_DRAW);
}

void Model::addShape(float* points, int size)
{
    this->shapes.push_back(Shape(points, size));
}

void Model::drawArrays()
{
    shader->useShaderProgram();
    glBindVertexArray(VAO);
    glBindVertexBuffer(0, VBO, 0, 3 * sizeof(float));
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
