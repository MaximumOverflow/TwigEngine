//
// Created by max on 22/07/19.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Objects/GameObjects/Camera.h>

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

//void TE::Camera::SetFrameBuffer(FrameBufferObject *frameBufferObject) {
//    FBO = frameBufferObject;
//}

void TE::Camera::SetProjectionMode(TE::ProjectionMode projectionMode) {
    switch (projectionMode)
    {
        case ProjectionMode::Perspective:
            Debug::Log("Perspective projection not yet supported, switching to ortho", Debug::Severity::Warning);
            projection = glm::perspective(-75.f, 16/9.f, -1.f, 1.f);
            break;
        case ProjectionMode::Ortho:
            projection = glm::ortho( -8.f, 8.f, -4.5f, 4.5f, -1.f, 1000.f);
            break;
    }
}

void TE::Camera::CameraTransform::Rotate(TE::Vec3 rotation) {
    this->rotation+=rotation;
    RecalculateMatrix();
}

void TE::Camera::CameraTransform::RecalculateMatrix() {
    glm::quat qPitch = glm::angleAxis(rotation.x, glm::vec3(1, 0, 0));
    glm::quat qYaw = glm::angleAxis(rotation.y, glm::vec3(0, 1, 0));
    glm::quat qRoll = glm::angleAxis(rotation.z,glm::vec3(0,0,1));

    glm::quat orientation = qPitch * qYaw;
    orientation = glm::normalize(orientation);
    glm::mat4 rotate = glm::mat4_cast(orientation);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, position);

    transformMatrix = rotate * translate;
}
