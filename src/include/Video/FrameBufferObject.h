//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_FRAMEBUFFEROBJECT_H
#define TWIG_ENGINE_FRAMEBUFFEROBJECT_H

namespace TE {
    class FrameBufferObject {
    private:
        unsigned int ID;
    public:
        static FrameBufferObject* Create();
        virtual ~FrameBufferObject() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}



#endif //TWIG_ENGINE_FRAMEBUFFEROBJECT_H
