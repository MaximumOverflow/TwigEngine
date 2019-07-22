//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_MESH_H
#define TWIG_ENGINE_MESH_H

#include <glm/glm.hpp>

#include "Video/VertexArrayObject.h"
#include "Video/VertexBufferObject.h"
#include "Video/IndexBufferObject.h"
#include "Types/Types.h"

class Mesh {
private:
    TE::VertexArrayObject* VAO;
    TE::VertexBufferObject* VBO;
    TE::IndexBufferObject* IBO;

    void LoadOBJ(std::string meshPath);

    std::vector<float> verteces;
    std::vector<float> texCoords;
    std::vector<float> normals;
    std::vector<unsigned int> indeces;

public:
    Mesh(std::string meshPath, TE::FileType fileType);
    void LoadModel(std::string meshPath, TE::FileType fileType);
    TE::VertexArrayObject* GetVAO();
    ~Mesh();

};


#endif //TWIG_ENGINE_MESH_H
