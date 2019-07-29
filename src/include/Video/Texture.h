//
// Created by max on 28/07/19.
//

#ifndef TWIG_ENGINE_TEXTURE_H
#define TWIG_ENGINE_TEXTURE_H

#include <string>

namespace TE {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual void Bind(unsigned int slot = 0) = 0;
        virtual void Unbind() = 0;
        static Texture* Create(const std::string path);
        static Texture* Create(const unsigned char* buffer, int width, int height, int bpp);
    };
}

#endif //TWIG_ENGINE_TEXTURE_H
