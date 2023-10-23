#include "Model.h"


Model::Model(const float* vertices, int size, int points)
{
    this->VAO = 0;
    this->shape = new Shape(vertices, size, points);
}

Model::Model(Shape* shape)
{
    this->VAO = 0;
    this->shape = shape;
}

Model::~Model()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
   
}

void Model::createVAO()
{
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
   /* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (GLvoid*) 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7*sizeof(float), (GLvoid*)(3*sizeof(float)));*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
   
}

void Model::createVBO()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->shape->getSize(), this->shape->getVertices(), GL_STATIC_DRAW);
}

void Model::drawArrays()
{
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->shape->getPoints());

    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        switch (error) {
        case GL_INVALID_ENUM:
            std::cout << this->VAO <<": Invalid enum" << std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cout << this->VAO << ": Ivalid value" << std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cout << this->VAO << ": Invalid operation" << std::endl;
            break;
        case GL_OUT_OF_MEMORY:
            std::cout << this->VAO << ": Out of memory" << std::endl;
            break;
            // Add more cases for other error codes if needed
        }
    }
}
