//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_FRAMEBUFFEROBJECT_H
#define TWIG_ENGINE_FRAMEBUFFEROBJECT_H

namespace TE {
    class FrameBufferObject {
    protected:
        float width = 0, height = 0;
    public:
        static FrameBufferObject* Create(float width = 0, float height = 0);
        virtual ~FrameBufferObject() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetResolution(float width, float height) = 0;
    };
}



#endif //TWIG_ENGINE_FRAMEBUFFEROBJECT_H
