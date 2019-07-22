//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_GL_VERTEXBUFFEROBJECT_H
#define TWIG_ENGINE_GL_VERTEXBUFFEROBJECT_H

#include "Video/VertexBufferObject.h"

namespace TE {
    class GL_VertexBufferObject : public VertexBufferObject{
    private:
        VertexBufferLayout layout = {0,0,DataType::TE_BYTE,0,0,0};
        uint32_t ID;
    public:
        GL_VertexBufferObject();

        ~GL_VertexBufferObject() override;

        void Bind() override;
        void Unbind() override;

        unsigned long GetID() override;

        void SetLayout(VertexBufferLayout layout) override;
        void SetData(uint32_t elements, float* data) override;
    };
}


#endif //TWIG_ENGINE_GL_VERTEXBUFFEROBJECT_H
