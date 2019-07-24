//
// Created by max on 22/07/19.
//

#include <Modules/Transform.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Modules/Transform.h"

glm::mat4& TE::Transform::GetTransformMatrix() {
    return transformMatrix;
}

const glm::vec3& TE::Transform::GetPosition() const {
    return position;
}

void TE::Transform::SetPosition(const glm::vec3 &position) {
    Transform::position = position;
    RecalculateMatrix();
}

const glm::vec3 &TE::Transform::GetRotation() const {
    return rotation;
}

void TE::Transform::SetRotation(const glm::vec3 &rotation) {
    Transform::rotation = rotation;
    RecalculateMatrix();
}

const glm::vec3 &TE::Transform::GetScale() const {
    return scale;
}

void TE::Transform::SetScale(const glm::vec3 &scale) {
    Transform::scale = scale;
    RecalculateMatrix();
}

void TE::Transform::Translate(TE::Vec3 translation) {
    position+=translation;
    transformMatrix = glm::translate(transformMatrix, translation);
}

void TE::Transform::Rotate(TE::Vec3 rotation) {
    this->rotation+=rotation;
    transformMatrix = glm::rotate(transformMatrix, rotation.x, Vec3(1,0,0));
    transformMatrix = glm::rotate(transformMatrix, rotation.y, Vec3(0,1,0));
    transformMatrix = glm::rotate(transformMatrix, rotation.z, Vec3(0,0,1));
}

void TE::Transform::Scale(TE::Vec3 scale) {
    this->scale += scale;
    RecalculateMatrix();
}

void TE::Transform::RecalculateMatrix() {
    transformMatrix = glm::mat4(1.f);

    transformMatrix = glm::translate(transformMatrix, position);

    transformMatrix = glm::rotate(transformMatrix, rotation.x, Vec3(1,0,0));
    transformMatrix = glm::rotate(transformMatrix, rotation.y, Vec3(0,1,0));
    transformMatrix = glm::rotate(transformMatrix, rotation.z, Vec3(0,0,1));

    transformMatrix = glm::scale(transformMatrix, scale);
}
