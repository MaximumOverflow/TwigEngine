//
// Created by max on 19/07/19.
//

#include "Video/GL/GL_VertexArrayObject.h"
#include "Debug.h"

#include <GL/glew.h>

TE::GL_VertexArrayObject::GL_VertexArrayObject(unsigned long rendererID) {
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
    this->rendererID = rendererID;
    Debug::Log("Generated OpenGL VAO with ID: " + std::to_string(ID));
}

void TE::GL_VertexArrayObject::Bind() {
    glBindVertexArray(ID);
}

void TE::GL_VertexArrayObject::Unbind() {
    glBindVertexArray(0);
}

unsigned long TE::GL_VertexArrayObject::GetRendererID() {
    return rendererID;
}

void TE::GL_VertexArrayObject::LinkVertexBufferObject(const std::shared_ptr<TE::VertexBufferObject> &vertexBufferObject) {
    glBindVertexArray(ID);
    vertexBufferObject->Bind();
    VBOs.push_back(vertexBufferObject);
    Debug::Log("Linked VBO [" + std::to_string(vertexBufferObject->GetID()) + "] with VAO [" + std::to_string(ID) + "]");
}

std::vector<std::shared_ptr<TE::VertexBufferObject>>& TE::GL_VertexArrayObject::GetLinkedVertexBufferObjects() {
    return VBOs;
}

TE::GL_VertexArrayObject::~GL_VertexArrayObject() {
    glDeleteVertexArrays(1, &ID);
}

void TE::GL_VertexArrayObject::LinkIndexBufferObject(std::shared_ptr<IndexBufferObject> &indexBufferObject) {
    glBindVertexArray(ID);
    indexBufferObject->Bind();
    IBO = indexBufferObject;
}

bool TE::GL_VertexArrayObject::HasIndexBufferObject() {
    return IBO != nullptr;
}

unsigned int TE::GL_VertexArrayObject::GetIndexBufferObjectElementCount() {
    if (!HasIndexBufferObject()) return 0;
    return IBO->GetElementCount();
}
