//
// Created by max on 22/07/19.
//
#include "Objects/Mesh.h"
#include "Debug.h"

#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <Objects/Mesh.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <External/tiny_obj_loader.h>


using namespace TE;

Mesh::~Mesh() {
    delete VAO;
    delete VBO;
    delete IBO;
}

Mesh::Mesh(std::string meshPath, TE::FileType fileType) {
    LoadModel(meshPath, fileType);

    VAO = VertexArrayObject::Create();
    VBO = VertexBufferObject::Create();
    IBO = IndexBufferObject::Create();

    VAO->LinkVertexBufferObject(VBO);
    VAO->LinkIndexBufferObject(IBO);

    if (buffer.size() == 0) return;

    VBO->SetData(buffer.size(), buffer.data());
    VBO->SetLayout({
        {DataStructure::TE_VEC3, TE_FLOAT, "te_position"},
        {DataStructure::TE_VEC2, TE_FLOAT, "te_texture_position"},
        {DataStructure::TE_VEC3, TE_FLOAT, "te_normal"},
    });
    IBO->SetData(indeces.size(), indeces.data());

    Debug::Log("Generated mesh containing " + std::to_string(positions.size()) + " verteces, with a " + std::to_string(buffer.size() * sizeof(float) / 1000000.f) + " MB buffer, from file: " + meshPath);
}

void Mesh::LoadModel(std::string meshPath, TE::FileType fileType) {
    switch (fileType)
    {
        case FileType::OBJ:
            LoadOBJ(meshPath);
            break;

        default:
            Debug::Log("Unsupported mesh file format", Debug::Severity::Error);
            return;
    }
}

void Mesh::LoadOBJ(std::string meshPath) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err, warn;
    if(!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, meshPath.c_str()))
    {
        Debug::Log("Could not load mesh: " + err, Debug::Severity::Error);
        return;
    }
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            indeces.push_back(indeces.size());
            positions.push_back(attrib.vertices[3* index.vertex_index + 0]);
            positions.push_back(attrib.vertices[3* index.vertex_index + 1]);
            positions.push_back(attrib.vertices[3* index.vertex_index + 2]);
            buffer.push_back(attrib.vertices[3* index.vertex_index + 0]);
            buffer.push_back(attrib.vertices[3* index.vertex_index + 1]);
            buffer.push_back(attrib.vertices[3* index.vertex_index + 2]);

            texCoords.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
            texCoords.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            buffer.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
            buffer.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);

            normals.push_back(attrib.normals[3 * index.normal_index + 0]);
            normals.push_back(attrib.normals[3 * index.normal_index + 1]);
            normals.push_back(attrib.normals[3 * index.normal_index + 2]);
            buffer.push_back(attrib.normals[3 * index.normal_index + 0]);
            buffer.push_back(attrib.normals[3 * index.normal_index + 1]);
            buffer.push_back(attrib.normals[3 * index.normal_index + 2]);
        }
    }
}

TE::VertexArrayObject *Mesh::GetVAO() {
    return VAO;
}