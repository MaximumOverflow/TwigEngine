//
// Created by max on 24/07/19.
//

#ifndef TWIG_ENGINE_GL_FRAMEBUFFEROBJECT_H
#define TWIG_ENGINE_GL_FRAMEBUFFEROBJECT_H

#include "Video/FrameBufferObject.h"
#include "Video/GL/GL_Texture.h"

namespace TE {
    class GL_FrameBufferObject : public TE::FrameBufferObject {
    private:
        unsigned int ID;
        unsigned int renderBufferID;
        GL_Texture renderTexture = GL_Texture();
    public:
        GL_FrameBufferObject(int width = 0, int height = 0);
        ~GL_FrameBufferObject() override;

        void Bind() override;
        void Unbind() override;

        void SetResolution(int width, int height) override;
        Vec2 GetResolution() override;

        Texture* GetRenderTexture() override;
    };
}



#endif //TWIG_ENGINE_GL_FRAMEBUFFEROBJECT_H
