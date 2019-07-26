//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_TRANSFORM_H
#define TWIG_ENGINE_TRANSFORM_H

#include "Module.h"
#include "Types/Types.h"

namespace TE {
    class Transform : public TE::Module {
    protected:
        Vec3 position;
        Vec3 rotation;
        Vec3 scale;
        Mat4 transformMatrix;

        virtual void RecalculateMatrix();

    public:
        Transform(GameObject *parent) : Module(parent) {
            transformMatrix = Mat4(1.f);
            Reset();
        }

        glm::mat4& GetTransformMatrix();

        const Vec3& GetPosition() const;
        void SetPosition(const Vec3 &position);

        const Vec3& GetRotation() const;

        virtual void SetRotation(const Vec3 &rotation);

        const Vec3& GetScale() const;
        void SetScale(const Vec3 &scale);

        virtual void Translate(Vec3 translation);

        virtual void TranslateLocal(Vec3 translation);

        virtual void Rotate(Vec3 rotation);
        void Scale(Vec3 scale);

        void Reset();
    };
}

#endif //TWIG_ENGINE_TRANSFORM_H
