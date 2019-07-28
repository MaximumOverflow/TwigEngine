//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_VERTEXBUFFEROBJECT_H
#define TWIG_ENGINE_VERTEXBUFFEROBJECT_H

#include <cstdio>
#include <vector>
#include <string>

#include "Types/Types.h"

namespace TE {

    struct VertexBufferLayoutElement {
        DataType type;
        DataStructure structure;
        std::string name;
        unsigned int size;
        unsigned int elements;
        unsigned int offset;

        VertexBufferLayoutElement(DataStructure dataStructure, DataType type, std::string name) :
            structure{dataStructure}, type{type} {
                size = StructureSize(dataStructure, type);
                switch (dataStructure)
                {
                    case DataStructure::TE_VEC1:    elements = 1; break;
                    case DataStructure::TE_VEC2:    elements = 2; break;
                    case DataStructure::TE_VEC3:    elements = 3; break;
                    case DataStructure::TE_VEC4:    elements = 4; break;
                    case DataStructure::TE_MAT4:    elements = 16; break;
                }
        }
    };

    class VertexBufferLayout {
    private:
        std::vector<VertexBufferLayoutElement> layoutElements;
    public:
        unsigned int stride;
        std::string name;

        VertexBufferLayout(std::initializer_list<VertexBufferLayoutElement> elements);
        const auto& GetElements() const { return layoutElements; }
        void AddElement(VertexBufferLayoutElement element);
    };

    class VertexBufferObject {
    public:
        static VertexBufferObject* Create();
        virtual ~VertexBufferObject() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual unsigned long GetID() = 0;

        virtual void SetLayout(VertexBufferLayout layout) = 0;
        virtual void AddLayoutElement(VertexBufferLayoutElement element) = 0;
        virtual void SetData(uint32_t elements, float* data) = 0;
    };
}

#endif //TWIG_ENGINE_VERTEXBUFFEROBJECT_H
