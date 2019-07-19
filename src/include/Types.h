//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_TYPES_H
#define TWIG_ENGINE_TYPES_H

#include <cstdint>
#include <algorithm>

namespace TE {
    enum class GraphicsAPI {
#ifndef TE_PLATFORM_MACOS
        OpenGL, Vulkan,
#endif

#ifdef TE_PLATFORM_WINDOWS
        DirectX,
#endif

#ifdef TE_PLATFORM_MACOS
        Metal
#endif
    };
}

#endif //TWIG_ENGINE_TYPES_H
