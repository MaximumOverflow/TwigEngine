//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_VERTEXBUFFEROBJECT_H
#define TWIG_ENGINE_VERTEXBUFFEROBJECT_H

#include <cstdio>
#include <array>
#include "../Types.h"

namespace TE {

    struct VertexBufferLayout {
        unsigned int index;
        unsigned int size;
        unsigned int type;
        bool normalized;
        int stride;
        const void* pointer;
    };

    class VertexBufferObject {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetLayout(VertexBufferLayout layout) = 0;
        virtual void SetData(TE::Types::Array<float> data) = 0;
    };
}

#endif //TWIG_ENGINE_VERTEXBUFFEROBJECT_H
