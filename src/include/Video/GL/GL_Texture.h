//
// Created by max on 28/07/19.
//

#ifndef TWIG_ENGINE_GL_TEXTURE_H
#define TWIG_ENGINE_GL_TEXTURE_H

#include "Video/Texture.h"
#include <string>

namespace TE {
    class GL_Texture : public Texture {
    private:
        unsigned int ID, slot;
        int width, height, bpp;
        unsigned char* buffer;
    public:
        explicit GL_Texture(std::string path);
        ~GL_Texture() override;

        void Bind(unsigned int slot = 0) override;
        void Unbind() override;
        inline unsigned int GetSlot() { return slot; }
    };
}



#endif //TWIG_ENGINE_GL_TEXTURE_H
