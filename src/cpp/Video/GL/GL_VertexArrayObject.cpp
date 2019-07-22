//
// Created by max on 19/07/19.
//

#include "Video/GL/GL_VertexArrayObject.h"
#include "Debug.h"

#include <GL/glew.h>
#include <Video/GL/GL_VertexArrayObject.h>

TE::GL_VertexArrayObject::GL_VertexArrayObject() {
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
    Debug::Log("Generated OpenGL VAO with ID: " + std::to_string(ID));
}

void TE::GL_VertexArrayObject::Bind() {
    glBindVertexArray(ID);
}

void TE::GL_VertexArrayObject::Unbind() {
    glBindVertexArray(0);
}

void TE::GL_VertexArrayObject::LinkVertexBufferObject(VertexBufferObject* vertexBufferObject) {
    glBindVertexArray(ID);
    vertexBufferObject->Bind();
    VBOs.push_back(vertexBufferObject);
    Debug::Log("Linked VBO [" + std::to_string(vertexBufferObject->GetID()) + "] with VAO [" + std::to_string(ID) + "]");
}

std::vector<TE::VertexBufferObject*>& TE::GL_VertexArrayObject::GetLinkedVertexBufferObjects() {
    return VBOs;
}

TE::GL_VertexArrayObject::~GL_VertexArrayObject() {
    glDeleteVertexArrays(1, &ID);
}

void TE::GL_VertexArrayObject::LinkIndexBufferObject(IndexBufferObject* indexBufferObject) {
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
