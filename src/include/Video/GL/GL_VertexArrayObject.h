//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_GL_VERTEXARRAYOBJECT_H
#define TWIG_ENGINE_GL_VERTEXARRAYOBJECT_H

#include "Video/VertexArrayObject.h"

namespace TE {
    class GL_VertexArrayObject : public VertexArrayObject{
    private:
        unsigned long rendererID;
        std::vector<std::shared_ptr<VertexBufferObject>> VBOs;
        std::shared_ptr<IndexBufferObject> IBO;
    public:
        explicit GL_VertexArrayObject(unsigned long rendererID);

        ~GL_VertexArrayObject() override;

        unsigned long GetRendererID() override;

        void Bind() override;
        void Unbind() override;

        void LinkVertexBufferObject(const std::shared_ptr<VertexBufferObject> &vertexBufferObject) override;
        std::vector<std::shared_ptr<VertexBufferObject>>& GetLinkedVertexBufferObjects() override;

        void LinkIndexBufferObject(std::shared_ptr<IndexBufferObject> &indexBufferObject) override;
        bool HasIndexBufferObject() override;

        unsigned int GetIndexBufferObjectElementCount() override;

    private:
        uint32_t ID;
    };
}

#endif //TWIG_ENGINE_GL_VERTEXARRAYOBJECT_H
