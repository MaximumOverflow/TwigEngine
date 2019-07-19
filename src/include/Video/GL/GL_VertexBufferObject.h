//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_GL_VERTEXBUFFEROBJECT_H
#define TWIG_ENGINE_GL_VERTEXBUFFEROBJECT_H

#include "../VertexBufferObject.h"

namespace TE {
    class GL_VertexBufferObject : public VertexBufferObject{
    private:
        VertexBufferLayout layout;
        uint32_t ID;
    public:
        void Bind() override;

        void Unbind() override;

        void SetLayout(VertexBufferLayout layout) override;

        void SetData(TE::Types::Array<float> data) override;
    };
}


#endif //TWIG_ENGINE_GL_VERTEXBUFFEROBJECT_H
