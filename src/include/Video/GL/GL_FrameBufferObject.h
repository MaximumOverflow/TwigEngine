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
        std::shared_ptr<GL_Texture> renderTexture = std::make_shared<GL_Texture>();
    public:
        GL_FrameBufferObject(int width = 0, int height = 0);
        ~GL_FrameBufferObject() override;

        void Bind() override;
        void Unbind() override;

        void SetResolution(int width, int height) override;
        Vec2 GetResolution() override;

        std::shared_ptr<Texture> GetRenderTexture() override;
    };
}



#endif //TWIG_ENGINE_GL_FRAMEBUFFEROBJECT_H
