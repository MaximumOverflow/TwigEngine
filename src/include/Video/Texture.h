//
// Created by max on 28/07/19.
//

#ifndef TWIG_ENGINE_TEXTURE_H
#define TWIG_ENGINE_TEXTURE_H

#include <string>
#include <memory>

namespace TE {
    class Texture {
    protected:
        unsigned int slot = 0;
        int width = 0, height = 0, bpp = 0;
        unsigned char* buffer = nullptr;
    public:
        virtual ~Texture() = default;

        virtual void Bind(unsigned int slot = 0) = 0;
        virtual void Unbind() = 0;
        inline unsigned int GetSlot() { return slot; }

        static std::shared_ptr<Texture> Create(const std::string path, bool retainBuffer = false);
        static std::shared_ptr<Texture> Create(const unsigned char* buffer, int width, int height, int bpp);
    };
}

#endif //TWIG_ENGINE_TEXTURE_H
