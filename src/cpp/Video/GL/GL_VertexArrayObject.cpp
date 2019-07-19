//
// Created by max on 19/07/19.
//

#include "../../../include/Video/GL/GL_VertexArrayObject.h"
#include <GL/glew.h>

TE::GL_VertexArrayObject::GL_VertexArrayObject(unsigned long rendererID) {
    glCreateVertexArrays(1, &ID);
    glBindVertexArray(ID);
    this->rendererID = rendererID;
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
    VBOs.push_back(vertexBufferObject);
}

std::vector<std::shared_ptr<TE::VertexBufferObject>> TE::GL_VertexArrayObject::GetLinkedVertexBufferObjects() {
    return VBOs;
}

TE::GL_VertexArrayObject::~GL_VertexArrayObject() {
    glDeleteVertexArrays(1, &ID);
}
