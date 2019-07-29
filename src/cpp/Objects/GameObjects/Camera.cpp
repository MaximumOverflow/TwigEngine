//
// Created by max on 22/07/19.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Objects/GameObjects/Camera.h>
#include <sstream>

#include "Objects/GameObjects/Camera.h"
#include "Video/Renderer.h"

TE::Camera::Camera() {
    Renderer::AddCamera(this);
    SetProjectionMode(ProjectionMode::Ortho);
}

TE::Camera::Camera(TE::ProjectionMode projectionMode) {
    Renderer::AddCamera(this);
    SetProjectionMode(projectionMode);
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

void TE::Camera::SetProjectionMode(TE::ProjectionMode projectionMode) {
    const Window* window = Renderer::GetWindow();
    int w = window->width, h = window->height;

    for(int i = w * h; i > 1; i--)
        if((w % i) == 0 && (h % i) == 0)
        {
            w = w / i;
            h = h / i;
        }

    float aspectRatio = (float) w/h;

    switch (projectionMode)
    {
        case ProjectionMode::Perspective:
                projection = glm::perspective(-75.f, aspectRatio, 1.f, -1.f);
            break;
        case ProjectionMode::Ortho:
            projection = glm::ortho( -w/2.f, w/2.f, -h/2.f, h/2.f, 1.f, -1.f);
            break;
    }

    this->projectionMode = projectionMode;

}

void TE::Camera::Unbind() {
    if (FBO != nullptr)
        FBO->Unbind();
}

void TE::Camera::SetProjectionMode(TE::ProjectionMode projectionMode, int width, int height) {
    for(int i = width * height; i > 1; i--)
        if((width % i) == 0 && (height % i) == 0)
        {
            width = width / i;
            height = height / i;
        }

    float aspectRatio = (float) width/height;

    switch (projectionMode)
    {
        case ProjectionMode::Perspective:
            projection = glm::perspective(-75.f, aspectRatio, 1.f, -1.f);
            break;
        case ProjectionMode::Ortho:
            projection = glm::ortho( -width/2.f, width/2.f, -height/2.f, height/2.f, 1.f, -1.f);
            break;
    }

    this->projectionMode = projectionMode;
}

void TE::Camera::SetFrameBuffer(TE::FrameBufferObject *frameBufferObject) {
    FBO = frameBufferObject;
    SetProjectionMode(this->projectionMode, 1, 1);
}

void TE::Camera::CameraTransform::Rotate(TE::Vec3 rotation) {
    this->rotation+=rotation;
    if (this->rotation.x > 360) this->rotation.x -= 360;
    else if (this->rotation.x < -360) this->rotation.x += 360;
    if (this->rotation.y > 360) this->rotation.y -= 360;
    else if (this->rotation.y < -360) this->rotation.y += 360;
    if (this->rotation.z > 360) this->rotation.y -= 360;
    else if (this->rotation.z < -360) this->rotation.z += 360;
    RecalculateMatrix();
}

void TE::Camera::CameraTransform::RecalculateMatrix() {
    glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), Vec3(1, 0, 0));
    glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), Vec3(0, 1, 0));
    glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z),Vec3(0,0,1));

    glm::quat orientation = qPitch * qYaw;
    orientation = glm::normalize(orientation);
    forward = Vec3(0,0,-1) * orientation;
    up = Vec3(0,1,0) * orientation;

    transformMatrix = glm::lookAt(position, forward+position, up);
}

void TE::Camera::CameraTransform::Translate(TE::Vec3 translation) {
    position+=translation;
    RecalculateMatrix();
}

void TE::Camera::CameraTransform::TranslateLocal(TE::Vec3 translation) {
    glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), Vec3(1, 0, 0));
    glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), Vec3(0, 1, 0));
    glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z),Vec3(0,0,1));
    glm::quat orientation = qPitch * qYaw;
    orientation = glm::normalize(orientation);

    position+=translation*orientation;
    RecalculateMatrix();
}
