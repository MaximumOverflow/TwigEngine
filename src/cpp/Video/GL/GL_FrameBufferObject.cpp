//
// Created by max on 24/07/19.
//

#include <GL/glew.h>

#include "Video/GL/GL_FrameBufferObject.h"

void GL_FrameBufferObject::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void GL_FrameBufferObject::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GL_FrameBufferObject::GL_FrameBufferObject() {
    glGenFramebuffers(1, &ID);
}
