#include "Model.h"


Model::Model(const float* vertices, int size, int points)
{
    this->VAO = 0;
    this->VBO = 0;
    this->shape = new Shape(vertices, size, points);
    this->texture = NULL;
}

Model::Model(Shape* shape)
{
    this->VAO = 0;
    this->VBO = 0;
    this->shape = shape;
    this->texture = NULL;
}

Model::Model(const char* obj, const char* texture)
{
    this->VAO = 0;
    this->VBO = 0;
    this->obj = obj;
    this->texture = texture;
    this->count = 0;
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
        glEnableVertexAttribArray(0); //enable vertex attributes
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

        glActiveTexture(GL_TEXTURE0 + this->textureID);
        tID = SOIL_load_OGL_texture(texture, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (tID == NULL) {
            std::cout << "An error occurred while loading texture." << std::endl;
            exit(EXIT_FAILURE);
        }
        glBindTexture(GL_TEXTURE_2D, tID);
    } else {
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
    if (this->obj != NULL) {
        std::vector<float> data = loadModel(this->obj);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, this->shape->getSize(), this->shape->getVertices(), GL_STATIC_DRAW);
        this->count = shape->getPoints();
    }
}

void Model::drawArrays()
{
    glBindVertexArray(this->VAO);
    //if (this->texture != NULL)
        //glBindTexture(GL_TEXTURE_2D, tID);
    glDrawArrays(GL_TRIANGLES, 0, count);
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

void Model::setObj(const char* obj)
{
    this->obj = obj;
}

std::vector<float> Model::loadModel(const char* fileName)
{
    std::vector<float> data;
    count = 0;
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // reduce the number of draw calls
        | aiProcess_JoinIdenticalVertices       // identifies and joins identical vertex data sets within all imported meshes
        | aiProcess_Triangulate                 // triangulates all faces of all meshes 
        | aiProcess_CalcTangentSpace;           // calculates the tangents and bitangents for the imported meshes

    const aiScene* scene = importer.ReadFile(fileName, importOptions);

    if (scene) {
        aiMesh* mesh = scene->mMeshes[0];//Only first mesh 
        printf("Triangles:%d \n", mesh->mNumFaces);
        count = mesh->mNumFaces * 3;

        aiFace* f;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < 3; j++)
            {
                int id = face.mIndices[j];

                //Vertex position
                aiVector3D pos = mesh->mVertices[id];
                data.push_back(pos.x);
                data.push_back(pos.y);
                data.push_back(pos.z);

                //Vertex normal
                aiVector3D nor = mesh->mNormals[id];
                data.push_back(nor.x);
                data.push_back(nor.y);
                data.push_back(nor.z);

                //Vertex uv
                aiVector3D uv = mesh->mTextureCoords[0][id];
                data.push_back(uv.x);
                data.push_back(uv.y);

            }
        }
    }
    else {
        std::cout << "An error occurred while loading model." << std::endl;
        exit(EXIT_FAILURE);
    };

    return data;
}
