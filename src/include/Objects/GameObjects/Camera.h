//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_CAMERA_H
#define TWIG_ENGINE_CAMERA_H

#include "GameObject.h"
#include "Modules/Transform.h"
#include "Video/FrameBufferObject.h"

#include <glm/glm.hpp>

namespace TE {
    class Camera : public GameObject {
    private:
        Transform* transform = AddModule<CameraTransform>();
        glm::mat4 projection;
        FrameBufferObject* FBO = nullptr;

        class CameraTransform : public Transform
        {
        private:
            Vec3 forward = Vec3(0,0,-1), up = Vec3(0,1,0);
        public:
            void Rotate(Vec3 rotation) override;
            CameraTransform(GameObject* gameObject) : Transform(gameObject) {};

        protected:
            void RecalculateMatrix() override;
        };

    public:
        Camera();
        Camera(TE::ProjectionMode projectionMode);
        ~Camera();
        void Bind();
        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetTransformMatrix() const;
        void SetProjectionMode(ProjectionMode projectionMode);
//        void SetFrameBuffer(FrameBufferObject* frameBufferObject);
    };

}

#endif //TWIG_ENGINE_CAMERA_H
