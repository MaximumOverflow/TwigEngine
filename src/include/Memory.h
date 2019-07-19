//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_MEMORY_H
#define TWIG_ENGINE_MEMORY_H

#include <unordered_map>

#include "Video/VertexArrayObject.h"

namespace TE {
    namespace Cache
    {
        struct Graphics
        {
            static std::vector<std::shared_ptr<VertexArrayObject>> VAOs;
            static std::vector<std::shared_ptr<VertexBufferObject>> VBOs;
        };
    }
}


#endif //TWIG_ENGINE_MEMORY_H
