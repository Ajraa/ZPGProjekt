#include "SkyCube.h"
#include "Models/skycube.h"
#include "Shader.h"

SkyCube::SkyCube() 
{
    this->textureId = 0;
}

void SkyCube::createVAO()
{
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

    glActiveTexture(GL_TEXTURE0);
    GLuint image = SOIL_load_OGL_cubemap("cubemap/posx.png", "cubemap/negx.png", "cubemap/posy.png", "cubemap/negy.png", "cubemap/posz.png", "cubemap/negz.png", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (image == NULL) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }

    glBindTexture(GL_TEXTURE_2D, image);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void SkyCube::createVBO()
{
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), skycube, GL_STATIC_DRAW);
}

void SkyCube::drawArrays()
{
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 108);
    glClear(GL_DEPTH_BUFFER_BIT);
}

int SkyCube::getTextureId()
{
    return this->textureId;
}
