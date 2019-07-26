//
// Created by max on 24/07/19.
//

#include <GL/glew.h>
#include <Video/GL/GL_FrameBufferObject.h>


#include "Video/GL/GL_FrameBufferObject.h"

void GL_FrameBufferObject::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glViewport(0,0, width, height);
}

void GL_FrameBufferObject::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GL_FrameBufferObject::GL_FrameBufferObject() {
    glGenFramebuffers(1, &ID);
}

GL_FrameBufferObject::~GL_FrameBufferObject() {
    glDeleteFramebuffers(1, &ID);
}

void GL_FrameBufferObject::SetResolution(float width, float height) {
    this->width = width;
    this->height = height;
}
