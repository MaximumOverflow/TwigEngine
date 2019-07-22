//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_VERTEXARRAYOBJECT_H
#define TWIG_ENGINE_VERTEXARRAYOBJECT_H

#include <memory>
#include <vector>

#include "VertexBufferObject.h"
#include "IndexBufferObject.h"

namespace TE {
    class VertexArrayObject {
    public:
        static VertexArrayObject* Create();
        virtual ~VertexArrayObject() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void LinkVertexBufferObject(VertexBufferObject* vertexBufferObject) = 0;
        virtual std::vector<VertexBufferObject*>& GetLinkedVertexBufferObjects() = 0;

        virtual void LinkIndexBufferObject(IndexBufferObject* indexBufferObject) = 0;
        virtual bool HasIndexBufferObject() = 0;
        virtual unsigned int GetIndexBufferObjectElementCount() = 0;
    };
}



#endif //TWIG_ENGINE_VERTEXARRAYOBJECT_H
