//
// Created by max on 19/07/19.
//

#include "Video/GL/GL_VertexBufferObject.h"
#include "Debug.h"

#include <GL/glew.h>

using namespace TE;

void GL_VertexBufferObject::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void GL_VertexBufferObject::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL_VertexBufferObject::SetLayout(VertexBufferLayout layout) {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glVertexAttribPointer(layout.index, layout.size, layout.type, layout.normalized, layout.stride, layout.pointer);
    glEnableVertexAttribArray(layout.index);
    this->layout = layout;
}

void GL_VertexBufferObject::SetData(uint32_t elements, float* data) {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, elements * sizeof(float), data, GL_STATIC_DRAW);
}

GL_VertexBufferObject::GL_VertexBufferObject() {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    Debug::Log("Generated OpenGL VBO with ID: " + std::to_string(ID));
}

GL_VertexBufferObject::~GL_VertexBufferObject() {
    glDeleteBuffers(1, &ID);
}

unsigned long GL_VertexBufferObject::GetID() {
    return ID;
}
