//
// Created by max on 24/07/19.
//

#include <GL/glew.h>

#include "Video/GL/GL_FrameBufferObject.h"
#include "Debug.h"
#include "Video/Renderer.h"

using namespace TE;

void GL_FrameBufferObject::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glViewport(0,0, width, height);
    renderTexture->Bind();
}

void GL_FrameBufferObject::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0, Renderer::GetActiveWindow()->width, Renderer::GetActiveWindow()->height);
    renderTexture->Unbind();
}

GL_FrameBufferObject::GL_FrameBufferObject(int width, int height) {
    glGenFramebuffers(1, &ID);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);

    renderTexture->Bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture->GetID(), 0);

    glGenRenderbuffers(1, &renderBufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferID);

    SetResolution(width, height);
    Unbind();
}

GL_FrameBufferObject::~GL_FrameBufferObject() {
    glDeleteFramebuffers(1, &ID);
    glDeleteRenderbuffers(1, &renderBufferID);
}

void GL_FrameBufferObject::SetResolution(int width, int height) {
    this->width = width;
    this->height = height;

    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

std::shared_ptr<Texture> GL_FrameBufferObject::GetRenderTexture() {
    return renderTexture;
}

Vec2 GL_FrameBufferObject::GetResolution() {
    return Vec2(width, height);
}
