//
// Created by max on 19/07/19.
//

#include "../../../include/Video/GL/GL_VertexBufferObject.h"
#include <GL/glew.h>

using namespace TE;

void GL_VertexBufferObject::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void GL_VertexBufferObject::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL_VertexBufferObject::SetLayout(VertexBufferLayout layout) {
    this->layout = layout;
}

void GL_VertexBufferObject::SetData(uint32_t elements, float* data) {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, elements, data, GL_STATIC_DRAW);
}

unsigned long GL_VertexBufferObject::GetRendererID() {
    return rendererID;
}

GL_VertexBufferObject::GL_VertexBufferObject(unsigned long rendererID) {
    glCreateBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    this->rendererID = rendererID;
}

GL_VertexBufferObject::~GL_VertexBufferObject() {
    glDeleteBuffers(1, &ID);
}
