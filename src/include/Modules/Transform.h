//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_TRANSFORM_H
#define TWIG_ENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include "Module.h"

namespace TE {
    class Transform : public TE::Module {
    private:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::mat4 transformMatrix;

    public:
        Transform(GameObject *parent) : Module(parent) {}

        glm::mat4& GetTransformMatrix();

        const glm::vec3& GetPosition() const;
        void SetPosition(const glm::vec3 &position);

        const glm::vec3& GetRotation() const;
        void SetRotation(const glm::vec3 &rotation);

        const glm::vec3& GetScale() const;
        void SetScale(const glm::vec3 &scale);
    };
}

#endif //TWIG_ENGINE_TRANSFORM_H
