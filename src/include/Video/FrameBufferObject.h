//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_FRAMEBUFFEROBJECT_H
#define TWIG_ENGINE_FRAMEBUFFEROBJECT_H

#include "Types/Types.h"
#include "Video/Texture.h"

#include <memory>

namespace TE {
    class FrameBufferObject {
    protected:
        int width = 0, height = 0;
    public:
        static FrameBufferObject* Create(int width = 0, int height = 0);
        virtual ~FrameBufferObject() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetResolution(int width, int height) = 0;
        virtual Vec2 GetResolution() = 0;

        virtual std::shared_ptr<Texture> GetRenderTexture() = 0;
    };
}



#endif //TWIG_ENGINE_FRAMEBUFFEROBJECT_H
