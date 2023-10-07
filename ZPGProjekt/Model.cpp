#include "Model.h"


Model::Model(Shader* shader, float* points, int size)
{
    this->VAO = 0;
    this->shader = shader;
    this->shape = new Shape(points, size);
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
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->shape->getSize(), this->shape->getPoints(), GL_STATIC_DRAW);
}

void Model::drawArrays()
{
    shader->useShaderProgram();
    glBindVertexArray(VAO);
    glBindVertexBuffer(0, VBO, 0, 3 * sizeof(float));
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
