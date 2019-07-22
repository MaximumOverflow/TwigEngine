//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_GL_VERTEXARRAYOBJECT_H
#define TWIG_ENGINE_GL_VERTEXARRAYOBJECT_H

#include "Video/VertexArrayObject.h"

namespace TE {
    class GL_VertexArrayObject : public VertexArrayObject{
    private:
        std::vector<VertexBufferObject*> VBOs;
        IndexBufferObject* IBO;
    public:
        GL_VertexArrayObject();
        ~GL_VertexArrayObject() override;

        void Bind() override;
        void Unbind() override;

        void LinkVertexBufferObject(VertexBufferObject* vertexBufferObject) override;
        std::vector<VertexBufferObject*>& GetLinkedVertexBufferObjects() override;

        void LinkIndexBufferObject(IndexBufferObject* indexBufferObject) override;
        bool HasIndexBufferObject() override;

        unsigned int GetIndexBufferObjectElementCount() override;

    private:
        uint32_t ID;
    };
}

#endif //TWIG_ENGINE_GL_VERTEXARRAYOBJECT_H
