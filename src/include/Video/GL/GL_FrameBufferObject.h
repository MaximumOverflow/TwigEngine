//
// Created by max on 24/07/19.
//

#ifndef TWIG_ENGINE_GL_FRAMEBUFFEROBJECT_H
#define TWIG_ENGINE_GL_FRAMEBUFFEROBJECT_H

#include "Video/FrameBufferObject.h"

class GL_FrameBufferObject : public TE::FrameBufferObject {
private:
    unsigned int ID;
public:
    GL_FrameBufferObject();

    void Bind() override;
    void Unbind() override;
};


#endif //TWIG_ENGINE_GL_FRAMEBUFFEROBJECT_H
