//
// Created by max on 20/07/19.
//

#ifndef TWIG_ENGINE_INDEXBUFFEROBJECT_H
#define TWIG_ENGINE_INDEXBUFFEROBJECT_H

#include <unitypes.h>

namespace TE {
    class IndexBufferObject {
    public:
        static IndexBufferObject* Create();
        virtual ~IndexBufferObject() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetData(uint32_t elements, unsigned int* data) = 0;
        virtual unsigned int GetElementCount() = 0;
    };
}



#endif //TWIG_ENGINE_INDEXBUFFEROBJECT_H
