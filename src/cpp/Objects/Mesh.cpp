//
// Created by max on 22/07/19.
//
#include "Objects/Mesh.h"
#include "Debug.h"

#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <Objects/Mesh.h>


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

    VBO->SetData(verteces.size(), verteces.data());
    VBO->SetLayout(VertexBufferLayout(0, 3, TE_FLOAT, false, sizeof(float)*3, nullptr));
    IBO->SetData(indeces.size(), indeces.data());

    Debug::Log("Generated mesh containing " + std::to_string(verteces.size()) + " verteces");
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
    std::ifstream file;
    file.open(meshPath);
    if (!file.is_open())
    {
        Debug::Log("Could not read mesh file: " + meshPath, Debug::Severity::Error);
        return;
    }

    std::vector<std::string> input;
    std::string tmp;
    while (file >> tmp)
        input.push_back(tmp);

    file.close();

    std::vector<glm::vec3> _verteces;
    std::vector<glm::vec2> _texCoords;
    std::vector<glm::vec3> _normals;

    std::vector<unsigned int> _indeces;
    std::vector<glm::vec2> _texCoordsOrdered;
    std::vector<glm::vec3> _normalsOrdered;

    for (unsigned long i = 0; i < input.size(); i++)
    {
        std::string& current = input.at(i);

        if (current == "v")
        {
            glm::vec3 vertex;
            vertex.x = std::stof(input.at(++i));
            vertex.y = std::stof(input.at(++i));
            vertex.z = std::stof(input.at(++i));
            _verteces.push_back(vertex);
        }
        else if (current == "vt")
        {
            glm::vec2 texCoord;
            texCoord.x = std::stof(input.at(++i));
            texCoord.y = std::stof(input.at(++i));
            _texCoords.push_back(texCoord);
        }
        else if (current == "vn")
        {
            glm::vec3 normal;
            normal.x = std::stof(input.at(++i));
            normal.y = std::stof(input.at(++i));
            normal.z = std::stof(input.at(++i));
            _normals.push_back(normal);
        }
        else if (current == "f")
        {
            std::string v[3];
            for (short j = 0; j < 3; j++)
                v[j] = input.at(++i);

            std::string v1[3];
            std::string v2[3];
            std::string v3[3];

            short counter = 0;
            //Get v1
            std::string index;
            for (short j = 0; j < v[0].size(); j++)
            {
                char c = v[0].at(j);
                if (c != '/')
                    index.push_back(c);
                else
                {
                    v1[counter++] = index;
                    index = "";
                }
            }
            v1[counter++] = index;
            index = "";

            //Get v2
            counter = 0;
            for (short j = 0; j < v[1].size(); j++)
            {
                char c = v[1].at(j);
                if (c != '/')
                    index.push_back(c);
                else {
                    v2[counter++] = index;
                    index = "";
                }
            }
            v2[counter++] = index;
            index = "";

            //Get v3
            counter = 0;
            for (short j = 0; j < v[2].size(); j++)
            {
                char c = v[2].at(j);
                if (c != '/')
                    index.push_back(c);
                else {
                    v3[counter++] = index;
                    index = "";
                }
            }
            v3[counter++] = index;
            index = "";

            _indeces.push_back(std::stoul(v1[0]) -1);
            if (!_texCoords.empty())
                _texCoordsOrdered.push_back(_texCoords.at(std::stoul(v1[1]) -1));
            _normalsOrdered.push_back(_normals.at(std::stoul(v1[2]) -1));

            _indeces.push_back(std::stoul(v2[0]) -1);
            if (!_texCoords.empty())
                _texCoordsOrdered.push_back(_texCoords.at(std::stoul(v2[1]) -1));
            _normalsOrdered.push_back(_normals.at(std::stoul(v2[2]) -1));

            _indeces.push_back(std::stoul(v3[0]) -1);
            if (!_texCoords.empty())
                _texCoordsOrdered.push_back(_texCoords.at(std::stoul(v3[1]) -1));
            _normalsOrdered.push_back(_normals.at(std::stoul(v3[2]) -1));
        }
    }
    for (auto& vertex : _verteces)
    {
        verteces.push_back(vertex.x);
        verteces.push_back(vertex.y);
        verteces.push_back(vertex.z);
    }
    for (auto& texCoord : _texCoordsOrdered)
    {
        texCoords.push_back(texCoord.x);
        texCoords.push_back(texCoord.y);
    }
    for (auto& normal : _normalsOrdered)
    {
        normals.push_back(normal.x);
        normals.push_back(normal.y);
    }
    indeces = _indeces;
}

TE::VertexArrayObject *Mesh::GetVAO() {
    return VAO;
}
