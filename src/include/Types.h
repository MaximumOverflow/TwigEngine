//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_TYPES_H
#define TWIG_ENGINE_TYPES_H

#include <cstdint>
#include <algorithm>

#define BIT(x) (1<<x)

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

    enum class EventType {
        WindowClose, WindowResize, WindowMinimize, WindowMaximize,
        MouseButtonPress, MouseButtonRelease, MouseButtonHold, MouseMove, MouseScroll,
        KeyPress, KeyRelease, KeyHold,
    };

    enum EventCategory {
        WindowEvent = BIT(1),
        MouseEvent = BIT(2),
        KeyboardEvent = BIT(3)
    };
}

#endif //TWIG_ENGINE_TYPES_H
