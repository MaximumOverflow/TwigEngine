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
        unsigned int ID;
    public:
        GL_Texture();
        GL_Texture(const unsigned char* buffer, int width, int height, int bpp);
        explicit GL_Texture(std::string path, bool retainBuffer = false);
        ~GL_Texture() override;

        void Bind(unsigned int slot = 0) override;
        void Unbind() override;
        const unsigned int GetID() const;
    };
}



#endif //TWIG_ENGINE_GL_TEXTURE_H
