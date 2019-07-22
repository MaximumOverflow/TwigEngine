//
// Created by max on 22/07/19.
//

#include <Modules/Transform.h>

#include "Modules/Transform.h"

glm::mat4& TE::Transform::GetTransformMatrix() {
    return transformMatrix;
}

const glm::vec3& TE::Transform::GetPosition() const {
    return position;
}

void TE::Transform::SetPosition(const glm::vec3 &position) {
    Transform::position = position;
}

const glm::vec3 &TE::Transform::GetRotation() const {
    return rotation;
}

void TE::Transform::SetRotation(const glm::vec3 &rotation) {
    Transform::rotation = rotation;
}

const glm::vec3 &TE::Transform::GetScale() const {
    return scale;
}

void TE::Transform::SetScale(const glm::vec3 &scale) {
    Transform::scale = scale;
}
