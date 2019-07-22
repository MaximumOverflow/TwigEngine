//
// Created by max on 22/07/19.
//

#include <Objects/GameObjects/Camera.h>

#include "Objects/GameObjects/Camera.h"
#include "Video/Renderer.h"

TE::Camera::Camera() {
    Renderer::AddCamera(this);
}

TE::Camera::~Camera() {
    Renderer::RemoveCamera(this);
}

void TE::Camera::Bind() {
    if (FBO != nullptr)
        FBO->Bind();
}

const glm::mat4& TE::Camera::GetProjectionMatrix() const {
    return projection;
}

const glm::mat4 &TE::Camera::GetTransformMatrix() const {
    return transform->GetTransformMatrix();
}

void TE::Camera::SetFrameBuffer(FrameBufferObject *frameBufferObject) {
    FBO = frameBufferObject;
}


