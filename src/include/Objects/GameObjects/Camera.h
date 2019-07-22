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
        Transform* transform = AddModule<Transform>();
        glm::mat4 projection;
        FrameBufferObject* FBO = nullptr;

    public:
        Camera();
        ~Camera();
        void Bind();
        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetTransformMatrix() const;
        void SetFrameBuffer(FrameBufferObject* frameBufferObject);
    };

}

#endif //TWIG_ENGINE_CAMERA_H
