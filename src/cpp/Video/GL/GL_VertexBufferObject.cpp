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

void GL_VertexBufferObject::SetData(TE::Types::Array<float> data) {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, data.Size(), data.Get(), GL_STATIC_DRAW);
}