//
// Created by max on 20/07/19.
//

#include "../../../include/Video/GL/GL_IndexBufferObject.h"
#include "../../../include/Debug.h"
#include <GL/glew.h>

using namespace TE;

GL_IndexBufferObject::GL_IndexBufferObject() {
    glGenBuffers(1, &ID);
    Debug::Log("Generated OpenGL IBO with ID: " + std::to_string(ID));
}

GL_IndexBufferObject::~GL_IndexBufferObject() {
    glDeleteBuffers(1, &ID);
}

void GL_IndexBufferObject::Bind() {
    Debug::Log("Binding IBO ID: " + std::to_string(ID));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void GL_IndexBufferObject::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned long GL_IndexBufferObject::GetRendererID() {
    //todo implement ibo caching
    return 0;
}

void GL_IndexBufferObject::SetData(uint32_t elements, unsigned int* data) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned int), data, GL_STATIC_DRAW);
    this->elements = elements;
}

unsigned int GL_IndexBufferObject::GetElementCount() {
    return elements;
}
