#include "Model.h"


Model::Model(const float* vertices, int size, int points)
{
    this->VAO = 0;
    this->shape = new Shape(vertices, size, points);
    this->texture = NULL;
}

Model::Model(Shape* shape)
{
    this->VAO = 0;
    this->shape = shape;
    this->texture = NULL;
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
    
    if (this->texture != NULL) {
        std::cout << "yup" << std::endl;
        glEnableVertexAttribArray(0); //enable vertex attributes
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

        glActiveTexture(GL_TEXTURE1);
        GLuint textureID = SOIL_load_OGL_texture(texture, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (textureID == NULL) {
            std::cout << "An error occurred while loading texture." << std::endl;
            exit(EXIT_FAILURE);
        }
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    else {
        glEnableVertexAttribArray(0); //enable vertex attributes
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    }

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
}

void Model::setTextureID(int id)
{
  this->textureID = id;
}

int Model::getTextureId()
{
  return this->textureID;
}

void Model::setTexture(const char* texture)
{
    this->texture = texture;
}
