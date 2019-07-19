//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_VERTEXARRAYOBJECT_H
#define TWIG_ENGINE_VERTEXARRAYOBJECT_H

#include <memory>
#include <vector>

#include "VertexBufferObject.h"

namespace TE {
    class VertexArrayObject {
    public:
        virtual ~VertexArrayObject() = default;
        virtual unsigned long GetRendererID() = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void LinkVertexBufferObject(const std::shared_ptr<VertexBufferObject>& vertexBufferObject) = 0;
//        virtual void LinkIndexBufferObject(std::shared_ptr<IndexBufferObject>& vertexBufferObject) = 0;

        virtual std::vector<std::shared_ptr<VertexBufferObject>> GetLinkedVertexBufferObjects() = 0;
    };
}



#endif //TWIG_ENGINE_VERTEXARRAYOBJECT_H
