//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_VERTEXBUFFEROBJECT_H
#define TWIG_ENGINE_VERTEXBUFFEROBJECT_H

#include <cstdio>
#include <array>

#include "Types/Types.h"

namespace TE {

    struct VertexBufferLayout {
        unsigned int index;
        unsigned int size;
        unsigned int type;
        bool normalized;
        int stride;
        const void* pointer;
        VertexBufferLayout(unsigned int index, unsigned int size, Type type, bool normalized, int stride, const void* pointer) :
            index{index}, size{size}, type{LookupType(type)}, normalized{normalized}, stride{stride}, pointer{pointer} {};
    };

    class VertexBufferObject {
    public:
        virtual ~VertexBufferObject() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual unsigned long GetRendererID() = 0;
        virtual unsigned long GetID() = 0;

        virtual void SetLayout(VertexBufferLayout layout) = 0;
        virtual void SetData(uint32_t elements, float* data) = 0;
    };
}

#endif //TWIG_ENGINE_VERTEXBUFFEROBJECT_H
